Public Class LineView

Private m_gameScore As Score4Wrapper.Document.ScoreDocument

Private m_currentLeague As Integer
Private m_currentDate As System.DateTime

''========================================================================
''    表示用のデータを指定して、ビューを初期化する。
''========================================================================
Public Sub initializeView(
        ByVal objSource As Score4Wrapper.Document.ScoreDocument,
        ByVal startDate As System.DateTime)

    If (Me.m_gameScore Is Nothing) Then
        Me.m_gameScore = objSource
    End If

    ScoreView.updateLeagueTab(Me.m_gameScore, Me.tabLeague)
    updateMagicLine(0, startDate)

    ' 指定した日付を選択する。
    mncDate.SelectionStart = startDate

End Sub

''========================================================================
''    優勝／プレーオフ進出ラインを表示する。
''========================================================================
Private Sub updateMagicLine(
        ByVal idxLeague As Integer,
        Byval targetDate As System.DateTime)

    With Me
        .m_currentLeague = idxLeague
        .m_currentDate = targetDate
        .m_gameScore.countScores(targetDate)
    End With
    lblDate.Text = targetDate

    ScoreView.displayVictoryLineToGrid(
        idxLeague, Me.m_gameScore, Me.dgvLine)

End Sub

''========================================================================
''    カレンダーをクリックしたら、その日付までのデータに切り替える。
''========================================================================
Private Sub mncDate_DateChanged(sender As Object, e As DateRangeEventArgs) _
        Handles mncDate.DateChanged

    updateMagicLine(Me.m_currentLeague, mncDate.SelectionStart)

End Sub

''========================================================================
''    タブを選択したら、そのリーグの情報に切り替える。
''========================================================================
Private Sub tabLeague_SelectedIndexChanged(sender As Object, e As EventArgs) _
        Handles tabLeague.SelectedIndexChanged

    Dim idxLeague As Integer = tabLeague.SelectedIndex
    If (idxLeague < 0) Then
        Exit Sub
    End If
    updateMagicLine(idxLeague, Me.m_currentDate)

End Sub

End Class
