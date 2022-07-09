Module ScoreView

''========================================================================
''    指定されたグリッドビューに残り試合のテーブルを表示する
''========================================================================
Public Sub displayRestGameTableToGrid(
        ByVal leagueIndex As Integer,
        ByRef scoreData As Score4Wrapper.Document.ScoreDocument,
        ByRef objTable As System.Windows.Forms.DataGridView)

    Dim i As Integer
    Dim bufShowIndex() As Integer
    Dim numShowCount As Integer

    ReDim bufShowIndex(0 To scoreData.getNumTeams() - 1)
    numShowCount = scoreData.computeRankOrder(leagueIndex, bufShowIndex)

    makeTeamListOnGridViewHeader(numShowCount, bufShowIndex, scoreData, objTable)
End Sub

''========================================================================
''    データの内容をグリッドビューに表示する。
''========================================================================
Public Sub displayScoreTableToGrid(
        ByVal leagueIndex As Integer,
        ByVal magicMode As Integer,
        ByRef scoreData As Score4Wrapper.Document.ScoreDocument,
        ByRef objTable As System.Windows.Forms.DataGridView)

    Dim i As Integer
    Dim bufShowIndex() As Integer
    Dim numShowCount As Integer
    Dim topDiff As Integer

    ReDim bufShowIndex(0 To scoreData.getNumTeams() - 1)
    numShowCount = scoreData.computeRankOrder(leagueIndex, bufShowIndex)

    With objTable
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
''    指定されたグリッドビューに残り試合のテーブルを表示する
''========================================================================

Private Function makeGridViewColumn(
        ByVal colName As String,
        ByVal colText As String) As System.Windows.Forms.DataGridViewColumn


    Dim textColumn As DataGridViewTextBoxColumn = New DataGridViewTextBoxColumn()
    With textColumn
        .AutoSizeMode = False
        .Name = colName
        .HeaderText = colText
        .Visible = True
        .Width = 64
        .ReadOnly = True
        .Resizable = DataGridViewTriState.False
    End With
    makeGridViewColumn = textColumn

End Function

''========================================================================
''    グリッドビューのヘッダ列にチーム名のリストをセットする。
''========================================================================
Private Sub makeTeamListOnGridViewHeader(
        ByVal numShowCount As Integer,
        ByRef bufShowIndex() As Integer,
        ByRef scoreData As Score4Wrapper.Document.ScoreDocument,
        ByRef objTable As System.Windows.Forms.DataGridView)

    Dim i As Integer
    Dim idxTeam As Integer
    Dim colName As String
    Dim colText As String
    Dim textColumn As DataGridViewTextBoxColumn

    Dim numTeams As Integer = scoreData.getNumTeams()

    With objTable
        With .Columns
            .Clear()

            textColumn = makeGridViewColumn("total", "Total")
            .Add(textColumn)

            For i = 0 To numShowCount - 1
                idxTeam = bufShowIndex(i)
                colName = "team" & idxTeam
                colText = scoreData.teamInfo(idxTeam).teamName
                textColumn = makeGridViewColumn(colName, colText)
                .Add(textColumn)
            Next i

            textColumn = makeGridViewColumn("league", "League")
            .Add(textColumn)

            For i = numShowCount To numTeams - 1
                idxTeam = bufShowIndex(i)
                colName = "team" & idxTeam
                colText = scoreData.teamInfo(idxTeam).teamName
                textColumn = makeGridViewColumn(colName, colText)
                .Add(textColumn)
            Next i

            textColumn = makeGridViewColumn("inter", "Inter.")
            .Add(textColumn)
        End With
    End With

End Sub

End Module
