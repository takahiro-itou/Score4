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

    makeTeamListOnGridViewHeader(numShowCount, bufShowIndex, numTeams, True, scoreData, objView)

    Const colTotalAll As Integer = 1
    Dim colLeagueTotal As Integer = numShowCount + 2
    Dim colInterTotal As Integer = numTeams + 3

    With objView
        .Rows.Clear()
        For i = 0 To numShowCount - 1
            Dim idxTeam As Integer = bufShowIndex(i)
            Dim teamInfo As Score4Wrapper.Common.TeamInfo
            Dim scoreInfo As Score4Wrapper.Common.CountedScores

            teamInfo = scoreData.teamInfo(idxTeam)
            scoreInfo = scoreData.scoreInfo(idxTeam)

            Dim restTotal As Integer
            Dim restLeague As Integer
            Dim restInter As Integer
            Dim targetTeam As Integer

            With scoreInfo
                restTotal = .numTotalRestGames(gameFilter)
                restLeague = .numLeagueRestGames(gameFilter)
                restInter = .numInterRestGames(gameFilter)
            End With

            .Rows.Add(
                teamInfo.teamName,
                restTotal
            )

            With .Rows(i)
                .Cells(colTotalAll).Style.BackColor = Color.FromArgb(0, 255, 0)

                ' 所属リーグ内の残り試合。対戦相手毎の試合数
                For j = 0 To numShowCount - 1
                    targetTeam = bufShowIndex(j)
                    .Cells(j + 2).Value = scoreInfo.restGames(targetTeam, gameFilter)
                Next j

                ' 所属リーグ内の残り試合の合計
                .Cells(colLeagueTotal).Value = restLeague
                .Cells(colLeagueTotal).Style.BackColor = Color.FromArgb(0, 255, 0)

                ' 交流戦の残り試合。対戦相手毎の試合数
                For j = numShowCount To numTeams - 1
                    targetTeam = bufShowIndex(j)
                    .Cells(j + 3).Value = scoreInfo.restGames(targetTeam, gameFilter)
                Next j

                ' 交流戦の残り試合の合計
                .Cells(colInterTotal).Value = restInter
                .Cells(colInterTotal).Style.BackColor = Color.FromArgb(0, 255, 0)
            End With

        Next
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

    makeTeamListOnGridViewHeader(numShowCount, bufShowIndex, numShowCount, False, scoreData, objView)

    With objView

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

    Dim i As Integer
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

    makeTeamListOnGridViewHeader(numShowCount, bufShowIndex, numShowCount, False, scoreData, objView)

    With objView

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
        ByRef scoreData As Score4Wrapper.Document.ScoreDocument,
        ByRef objView As System.Windows.Forms.DataGridView)

    Dim i As Integer
    Dim idxTeam As Integer
    Dim colName As String
    Dim colText As String
    Dim textColumn As DataGridViewTextBoxColumn

    If (numTeams = -1) Then
        numTeams = scoreData.getNumTeams()
    End If

    With objView
        With .Columns
            .Clear()

            textColumn = makeGridViewColumn("team", "Team")
            .Add(textColumn)

            If (flagShowTotal) Then
                textColumn = makeGridViewColumn("total", "Total")
                textColumn.DefaultCellStyle.BackColor = Color.FromArgb(0, 255, 0)
                textColumn.HeaderCell.Style.BackColor = Color.FromArgb(0, 255, 0)
                .Add(textColumn)
            End If

            For i = 0 To numShowCount - 1
                idxTeam = bufShowIndex(i)
                colName = "team" & idxTeam
                colText = scoreData.teamInfo(idxTeam).teamName
                textColumn = makeGridViewColumn(colName, colText)
                .Add(textColumn)
            Next i

            If (flagShowTotal) Then
                textColumn = makeGridViewColumn("league", "League")
                textColumn.DefaultCellStyle.BackColor = Color.FromArgb(0, 255, 0)
                textColumn.HeaderCell.Style.BackColor = Color.FromArgb(0, 255, 0)
                .Add(textColumn)
            End If

            For i = numShowCount To numTeams - 1
                idxTeam = bufShowIndex(i)
                colName = "team" & idxTeam
                colText = scoreData.teamInfo(idxTeam).teamName
                textColumn = makeGridViewColumn(colName, colText)
                .Add(textColumn)
            Next i

            If (flagShowTotal) Then
                textColumn = makeGridViewColumn("inter", "Inter.")
                textColumn.DefaultCellStyle.BackColor = Color.FromArgb(0, 255, 0)
                textColumn.HeaderCell.Style.BackColor = Color.FromArgb(0, 255, 0)
                .Add(textColumn)
            End If

        End With
    End With

End Sub

End Module
