Public Class LineView

Private m_gameScore As Score4Wrapper.Document.ScoreDocument

Private m_currentLeague As Integer
Private m_currentDate As System.DateTime

''========================================================================
''    表示用のデータを指定して、ビューを初期化する。
''========================================================================
Public Sub initializeView(
        ByVal objSource As Score4Wrapper.Document.ScoreDocument,
        ByVal startupDate As System.DateTime)

    If (Me.m_gameScore Is Nothing) Then
        Me.m_gameScore = objSource
    End If

    ScoreView.updateLeagueTab(Me.m_gameScore, Me.tabLeague)

End Sub

End Class
