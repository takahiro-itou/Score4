Module ScoreView

Public Enum ExtraViewMode As Integer
    EXTRA_VIEW_REST_GAMES = 0
    EXTRA_VIEW_MAGIC_NUMBERS = 1
    EXTRA_VIEW_WIN_FOR_MATCH = 2
End Enum

Public Enum MagicMode As Integer
    MAGIC_MODE_VICTORY = 0      ' 優勝マジック
    MAGIC_MODE_PLAYOFF = 1      ' プレーオフ進出マジック
End Enum

''========================================================================
''    指定されたグリッドビューに残り試合のテーブルを表示する
''========================================================================
Public Sub displayRestGameTableToGrid(
        ByVal leagueIndex As Integer,
        ByVal scheduleFilter As Score4Wrapper.GameFilter,
        ByVal gameType As Score4Wrapper.GameFilter,
        ByRef scoreData As Score4Wrapper.Document.ScoreDocument,
        ByRef objView As System.Windows.Forms.DataGridView)

    Dim i As Integer
    Dim bufShowIndex() As Integer
    Dim numShowCount As Integer
    Dim numTeams As Integer

    ' 引数をマスクする
    Dim gameFilter As Score4Wrapper.GameFilter
    gameFilter = (scheduleFilter And Score4Wrapper.GameFilter.FILTER_SCHEDULE)
    gameFilter = (gameType Or gameFilter)

    numTeams = scoreData.getNumTeams()
    ReDim bufShowIndex(0 To numTeams - 1)
    numShowCount = scoreData.computeRankOrder(leagueIndex, bufShowIndex)

    makeTeamListOnGridViewHeader(
        numShowCount, bufShowIndex, numTeams, True, 48,
        scoreData, objView)

    With objView
        .Rows.Clear()
        For i = 0 To numShowCount - 1
            Dim idxTeam As Integer = bufShowIndex(i)
            Dim teamInfo As Score4Wrapper.Common.TeamInfo
            Dim scoreInfo As Score4Wrapper.Common.CountedScores

            teamInfo = scoreData.teamInfo(idxTeam)
            scoreInfo = scoreData.scoreInfo(idxTeam)

            .Rows.Add(
                teamInfo.teamName
            )

            writeTeamRestGamesToGridRow(
                gameFilter, numTeams, numShowCount,
                bufShowIndex, .Rows(i), scoreInfo
            )
        Next i
    End With
End Sub

''========================================================================
''    データの内容をグリッドビューに表示する。
''========================================================================
Public Sub displayScoreTableToGrid(
        ByVal leagueIndex As Integer,
        ByVal magicMode As MagicMode,
        ByRef scoreData As Score4Wrapper.Document.ScoreDocument,
        ByRef objView As System.Windows.Forms.DataGridView)

    Dim i As Integer
    Dim bufShowIndex() As Integer
    Dim numShowCount As Integer
    Dim topDiff As Integer

    ReDim bufShowIndex(0 To scoreData.getNumTeams() - 1)
    numShowCount = scoreData.computeRankOrder(leagueIndex, bufShowIndex)

    With objView
        .Rows.Clear()
        For i = 0 To numShowCount - 1
            Dim idxTeam As Integer = bufShowIndex(i)
            Dim teamInfo As Score4Wrapper.Common.TeamInfo
            Dim scoreInfo As Score4Wrapper.Common.CountedScores

            teamInfo = scoreData.teamInfo(idxTeam)
            scoreInfo = scoreData.scoreInfo(idxTeam)

            Dim numWons As Integer = scoreInfo.numWons(2)
            Dim numLost As Integer = scoreInfo.numLost(2)
            Dim numDraw As Integer = scoreInfo.numDraw(2)
            Dim strDiff As String
            Dim strPerc As String

            ' ゲーム差
            Dim curDiff As Integer = numWons - numLost
            If (i = 0) Then
                topDiff = curDiff
                strDiff = "---"
            ElseIf (curDiff = topDiff) Then
                strDiff = "---"
            Else
                strDiff = Format((topDiff - curDiff) / 2, "#0.0")
            End If

            ' 勝率
            Dim numGame As Integer = scoreInfo.numGames(2)
            Dim wpDenom As Integer = numGame - numDraw
            If (wpDenom = 0) Then
                strPerc = "---"
            Else
                strPerc = Format(numWons / wpDenom, "#.000")
            End If

            .Rows.Add(
                teamInfo.teamName,
                numGame,
                numWons,
                numLost,
                numDraw,
                strDiff,
                strPerc
            )
        Next
    End With

End Sub

''========================================================================
''    指定されたグリッドビューに対チームごとのマジックを表示する。
''========================================================================
Public Sub displayTeamMagicTableToGrid(
        ByVal leagueIndex As Integer,
        ByVal magicMode As MagicMode,
        ByRef scoreData As Score4Wrapper.Document.ScoreDocument,
        ByRef objView As System.Windows.Forms.DataGridView)

    Dim i As Integer
    Dim bufShowIndex() As Integer
    Dim numTeams As Integer
    Dim numShowCount As Integer

    With objView
         .Columns.Clear()
         .Rows.Clear()
    End With

    numTeams = scoreData.getNumTeams()
    ReDim bufShowIndex(0 To numTeams - 1)
    numShowCount = scoreData.computeRankOrder(leagueIndex, bufShowIndex)
    If (numShowCount = 0) Then
        objView.Visible = False
        Exit Sub
    End If

    makeTeamListOnGridViewHeader(
        numShowCount, bufShowIndex, numShowCount, False, 64,
        scoreData, objView)

    With objView
        For i = 0 To numShowCount - 1
            Dim idxTeam As Integer = bufShowIndex(i)
            Dim teamInfo As Score4Wrapper.Common.TeamInfo
            Dim scoreInfo As Score4Wrapper.Common.CountedScores

            teamInfo = scoreData.teamInfo(idxTeam)
            scoreInfo = scoreData.scoreInfo(idxTeam)

            .Rows.Add(teamInfo.teamName)
            writeTeamMagicToGridRow(
                numTeams, numShowCount, idxTeam,
                bufShowIndex, .Rows(i), scoreInfo)
        Next i
    End With

End Sub

''========================================================================
''    指定されたグリッドビューに下記テーブルの内容を表示する。
''
''    各対戦相手毎に、その相手より (確実に) 上位になるために、
''  最低限勝利しなければならない試合数。
''========================================================================
Public Sub displayWinsForBeatTableToGrid(
        ByVal leagueIndex As Integer,
        ByRef scoreData As Score4Wrapper.Document.ScoreDocument,
        ByRef objView As System.Windows.Forms.DataGridView)

    Dim bufShowIndex() As Integer
    Dim numTeams As Integer
    Dim numShowCount As Integer

    numTeams = scoreData.getNumTeams()
    ReDim bufShowIndex(0 To numTeams - 1)
    numShowCount = scoreData.computeRankOrder(leagueIndex, bufShowIndex)
    If (numShowCount = 0) Then
        objView.Visible = False
        Exit Sub
    End If

    makeTeamListOnGridViewHeader(
        numShowCount, bufShowIndex, numShowCount, False, 96,
        scoreData, objView)

    With objView
        .Columns(0).Width = 112

        For i = 0 To numShowCount - 1
            Dim idxTeam As Integer = bufShowIndex(i)
            Dim teamInfo As Score4Wrapper.Common.TeamInfo
            Dim scoreInfo As Score4Wrapper.Common.CountedScores

            teamInfo = scoreData.teamInfo(idxTeam)
            scoreInfo = scoreData.scoreInfo(idxTeam)

            .Rows.Add(teamInfo.teamName)
            writeWinsForBeatToGridRow(
                numTeams, numShowCount, idxTeam,
                bufShowIndex, .Rows(i), scoreInfo)
        Next i
    End With

End Sub

''========================================================================
''    指定されたグリッドビューに残り試合のテーブルを表示する
''========================================================================
Private Function makeGridViewColumn(
        ByVal colName As String,
        ByVal colText As String) As System.Windows.Forms.DataGridViewColumn

    Dim textColumn As DataGridViewTextBoxColumn = New DataGridViewTextBoxColumn()
    With textColumn
        .AutoSizeMode = False
        .HeaderText = colText
        .Name = colName
        .ReadOnly = True
        .Resizable = DataGridViewTriState.False
        .SortMode = DataGridViewColumnSortMode.NotSortable
        .Visible = True
        .Width = 64
    End With

    makeGridViewColumn = textColumn

End Function

''========================================================================
''    グリッドビューのヘッダ列にチーム名のリストをセットする。
''========================================================================
Private Sub makeTeamListOnGridViewHeader(
        ByVal numShowCount As Integer,
        ByRef bufShowIndex() As Integer,
        ByVal numTeams As Integer,
        ByVal flagShowTotal As Boolean,
        ByVal columnWidth As Integer,
        ByRef scoreData As Score4Wrapper.Document.ScoreDocument,
        ByRef objView As System.Windows.Forms.DataGridView)

    Dim i As Integer
    Dim idxTeam As Integer
    Dim colName As String
    Dim colText As String
    Dim cellAlign As DataGridViewContentAlignment
    Dim textColumn As DataGridViewTextBoxColumn

    cellAlign = DataGridViewContentAlignment.MiddleRight

    If (numTeams = -1) Then
        numTeams = scoreData.getNumTeams()
    End If

    With objView.Columns
        .Clear()

        textColumn = makeGridViewColumn("team", "Team")
        textColumn.Width = columnWidth
        .Add(textColumn)

        If (flagShowTotal) Then
            textColumn = makeGridViewColumn("total", "Total")
            With textColumn
                With .DefaultCellStyle
                    .Alignment = cellAlign
                    .BackColor = Color.FromArgb(0, 255, 0)
                End With
                .HeaderCell.Style.BackColor = Color.FromArgb(0, 255, 0)
                .Width = columnWidth
            End With
            .Add(textColumn)
        End If

        For i = 0 To numShowCount - 1
            idxTeam = bufShowIndex(i)
            colName = "team" & idxTeam
            colText = scoreData.teamInfo(idxTeam).teamName
            textColumn = makeGridViewColumn(colName, colText)
            With textColumn
                .DefaultCellStyle.Alignment = cellAlign
                .Width = columnWidth
            End With
            .Add(textColumn)
        Next i

        If (flagShowTotal) Then
            textColumn = makeGridViewColumn("league", "League")
            With textColumn
                With .DefaultCellStyle
                    .Alignment = cellAlign
                    .BackColor = Color.FromArgb(0, 255, 0)
                End With
                .HeaderCell.Style.BackColor = Color.FromArgb(0, 255, 0)
                .Width = columnWidth
            End With
            .Add(textColumn)
        End If

        For i = numShowCount To numTeams - 1
            idxTeam = bufShowIndex(i)
            colName = "team" & idxTeam
            colText = scoreData.teamInfo(idxTeam).teamName
            textColumn = makeGridViewColumn(colName, colText)
            With textColumn
                .DefaultCellStyle.Alignment = cellAlign
                .Width = columnWidth
            End With
            .Add(textColumn)
        Next i

        If (flagShowTotal) Then
            textColumn = makeGridViewColumn("inter", "Inter.")
            With textColumn
                With .DefaultCellStyle
                    .Alignment = cellAlign
                    .BackColor = Color.FromArgb(0, 255, 0)
                End With
                .HeaderCell.Style.BackColor = Color.FromArgb(0, 255, 0)
                .Width = columnWidth
            End With
            .Add(textColumn)
        End If
    End With

End Sub

''========================================================================
''    指定されたグリッドの行に、チームのマジック等を書き込む。
''========================================================================
Private Sub writeTeamMagicToGridRow(
        ByVal numTeams As Integer,
        ByVal numShowCount As Integer,
        ByVal idxTeam As Integer,
        ByRef showIndex() As Integer,
        ByRef destRow As System.Windows.Forms.DataGridViewRow,
        ByRef scoreInfo As Score4Wrapper.Common.CountedScores)

    Dim j As Integer
    Dim cellText as String
    Dim backColor as Color
    Dim foreColor as Color = Color.FromArgb(0, 0, 0)

    With destRow
        For j = 0 To numShowCount - 1
            Dim idxEnemy As Integer = showIndex(j)
            If (idxTeam = idxEnemy) Then
                .Cells(j + 1).Value = "--------"
                Continue For
            End If

            Dim beatProb As Integer = scoreInfo.beatProbability(idxEnemy)
            If (beatProb <= -9999) Then
                cellText = "-----"
                backColor = Color.FromArgb(255, 0, 0)
                foreColor = Color.FromArgb(255, 255, 255)
            Else
                cellText = Right("     " & beatProb, 5)
                backColor = Color.FromArgb(255, 255, 255)
                If (beatProb < 0) Then
                    backColor = Color.FromArgb(255, 255, 0)
                Else
                    backColor = Color.FromArgb(0, 255, 0)
                End If
            End If

            Dim vsMagic As Integer = scoreInfo.vsMagic(idxEnemy)
            If (vsMagic = 0) Then
                cellText = "M 0 :  ---"
                backColor = Color.FromArgb(0, 0, 255)
                foreColor = Color.FromArgb(255, 255, 255)
            ElseIf (vsMagic >= 0) Then
                cellText = "M " & vsMagic & " : " & cellText
                backColor = Color.FromArgb(0, 255, 255)
            End If

            With .Cells(j + 1)
                .Style.BackColor = backColor
                .Style.ForeColor = foreColor
                .Value = cellText
            End With
        Next j
    End With

End Sub

''========================================================================
''    指定されたグリッドの行に、チームの残り試合数を書き込む。
''========================================================================
Private Sub writeTeamRestGamesToGridRow(
        ByVal gameFilter As Score4Wrapper.GameFilter,
        ByVal numTeams As Integer,
        ByVal numShowCount As Integer,
        ByRef showIndex() As Integer,
        ByRef destRow As System.Windows.Forms.DataGridViewRow,
        ByRef scoreInfo As Score4Wrapper.Common.CountedScores)

    Dim j As Integer
    Dim restTotal As Integer
    Dim restLeague As Integer
    Dim restInter As Integer
    Dim targetTeam As Integer

    Const colTotalAll As Integer = 1
    Dim colLeagueTotal As Integer = numShowCount + 2
    Dim colInterTotal As Integer = numTeams + 3

    With scoreInfo
        restTotal = .numTotalRestGames(gameFilter)
        restLeague = .numLeagueRestGames(gameFilter)
        restInter = .numInterRestGames(gameFilter)
    End With

    With destRow
        ' 残り試合の合計
        With .Cells(colTotalAll)
            .Style.BackColor = Color.FromArgb(0, 255, 0)
            .Value = restTotal
        End With

        ' 所属リーグ内の残り試合。対戦相手毎の試合数
        For j = 0 To numShowCount - 1
            targetTeam = showIndex(j)
            .Cells(j + 2).Value = scoreInfo.restGames(targetTeam, gameFilter)
        Next j

        ' 所属リーグ内の残り試合の合計
        With .Cells(colLeagueTotal)
            .Style.BackColor = Color.FromArgb(0, 255, 0)
            .Value = restLeague
        End With

        ' 交流戦の残り試合。対戦相手毎の試合数
        For j = numShowCount To numTeams - 1
            targetTeam = showIndex(j)
            .Cells(j + 3).Value = scoreInfo.restGames(targetTeam, gameFilter)
        Next j

        ' 交流戦の残り試合の合計
        With .Cells(colInterTotal)
            .Style.BackColor = Color.FromArgb(0, 255, 0)
            .Value = restInter
        End With
    End With

End Sub

''========================================================================
''    指定されたグリッドの行に、チームの必要勝利数を書き込む。
''========================================================================
Private Sub writeWinsForBeatToGridRow(
        ByVal numTeams As Integer,
        ByVal numShowCount As Integer,
        ByVal idxTeam As Integer,
        ByRef showIndex() As Integer,
        ByRef destRow As System.Windows.Forms.DataGridViewRow,
        ByRef scoreInfo As Score4Wrapper.Common.CountedScores)

    Dim j As Integer
    Dim beatInfo As Score4Wrapper.Common.NumWinsForBeat
    Dim beatFlag As Score4Wrapper.MagicFilter
    Dim numWins As Integer, numRest As Integer
    Dim cellText as String
    Dim backColor as Color
    Dim foreColor as Color = Color.FromArgb(0, 0, 0)

    With destRow
        For j = 0 To numShowCount - 1
            Dim idxEnemy As Integer = showIndex(j)
            If (idxTeam = idxEnemy) Then
                .Cells(j + 1).Value = "--------"
                Continue For
            End If

            backColor = Color.FromArgb(255, 255, 255)
            foreColor = Color.FromArgb(0, 0, 0)
            beatInfo = scoreInfo.numWinsForBeat(idxEnemy)
            beatFlag = beatInfo.filterType
            numWins = beatInfo.numNeedWins
            numRest = beatInfo.numRestGame

            cellText = numWins & " 勝 / " & numRest & " 試合"
            Select Case beatFlag
            Case Score4Wrapper.MagicFilter.MF_DIFFERENT_LEAGUE
                 cellText = "--------"
            Case Score4Wrapper.MagicFilter.MF_ON_MAGIC
                If (numWins <= 0) Then
                    backColor = Color.FromArgb(0, 0, 255)
                    foreColor = Color.FromArgb(255, 255, 255)
                Else
                    backColor = Color.FromArgb(0, 255, 255)
                End If
            Case Score4Wrapper.MagicFilter.MF_MAGIC_IF_RIVAL_LOSE
                backColor = Color.FromArgb(0, 255, 0)
            Case Score4Wrapper.MagicFilter.MF_BEAT_IF_WIN_DIRECT
                backColor = Color.FromArgb(255, 255, 255)
            Case Score4Wrapper.MagicFilter.MF_CANNOT_BEAT_BY_SELF
                backColor = Color.FromArgb(255, 255, 0)
            Case Score4Wrapper.MagicFilter.MF_NEVER_BEAT
                cellText = "不可"
                backColor = Color.FromArgb(255, 0, 0)
                foreColor = Color.FromArgb(255, 255, 255)
            End Select

            With .Cells(j + 1)
                .Style.BackColor = backColor
                .Style.ForeColor = foreColor
                .Value = cellText
            End With

        Next j
    End With

End Sub

End Module
