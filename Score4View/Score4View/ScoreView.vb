Module ScoreView

    ''================================================================================
    ''    データの内容をグリッドビューに表示する。
    ''================================================================================
    Public Sub displayScoreTableToGrid(
                ByVal leagueIndex As Integer,
                ByVal magicMode As Integer,
                ByRef scoreData As Score4Wrapper.Common.ScoreDocument,
                ByRef objTable As System.Windows.Forms.DataGridView)

        Dim i As Integer
        Dim bufShowIndex() As Integer

        ReDim bufShowIndex(0 To scoreData.getNumTeams() - 1)
        Dim numShowCount As Integer = scoreData.computeRankOrder(leagueIndex, bufShowIndex)

        With objTable
            .Rows.Clear()
            For i = 0 To numShowCount - 1
                Dim idxTeam As Integer = bufShowIndex(i)
                Dim teamInfo As Score4Wrapper.Common.TeamInfo = scoreData.teamInfo(idxTeam)
                .Rows.Add(teamInfo.teamName, 0, 0, 0)
            Next
        End With
    End Sub
End Module
