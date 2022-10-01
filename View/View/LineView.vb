Public Class LineView

Private Const INI_SEC_LINE_VIEW As String = "LineView"

Private m_gameScore As Score4Wrapper.Document.ScoreDocument

Private m_currentLeague As Integer
Private m_currentDate As System.DateTime

Private m_iniFileName As String

''========================================================================
''    フォームの初期位置を設定する。
''========================================================================
Public Sub initializeFormPosition(
        ByVal iniFileName As String,
        ByRef ownerForm As System.Windows.Forms.Form)

    Me.m_iniFileName = iniFileName
    moveWindowToStartPosition(m_iniFileName, INI_SEC_LINE_VIEW, Me, ownerForm)

End Sub

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

    ' ラジオボタンを選択する。
    optShowRestWin.Checked = True

    ' 指定した日付を選択する。
    mncDate.SelectionStart = startDate

End Sub

''========================================================================
''    優勝／プレーオフ進出ラインを表示する。
''========================================================================
Private Sub updateMagicLine(
        ByVal idxLeague As Integer,
        Byval targetDate As System.DateTime)

    Dim flagViewMode As LineViewMode

    With Me
        .m_currentLeague = idxLeague
        .m_currentDate = targetDate
        .m_gameScore.countScores(targetDate)
    End With
    lblDate.Text = targetDate

    If optShowRestWin.Checked Then
        flagViewMode = LineViewMode.LINE_VIEW_REST_WINS
    Else If optShowLastWin.Checked Then
        flagViewMode = LineViewMode.LINE_VIEW_LAST_WINS
    Else
        flagViewMode = LineViewMode.LINE_VIEW_LAST_WINS
    End If

    ScoreView.displayVictoryLineToGrid(
        idxLeague, Me.m_gameScore, flagViewMode, Me.dgvLine)

End Sub

''========================================================================
''    フォームを閉じるときに現在位置等を保存する。
''========================================================================
Private Sub LineView_FormClosing(sender As Object, e As FormClosingEventArgs) _
        Handles Me.FormClosing

    saveWindowPrefs(m_iniFileName, INI_SEC_LINE_VIEW, Me)

End Sub

''========================================================================
''    カレンダーをクリックしたら、その日付までのデータに切り替える。
''========================================================================
Private Sub mncDate_DateChanged(sender As Object, e As DateRangeEventArgs) _
        Handles mncDate.DateChanged

    updateMagicLine(Me.m_currentLeague, mncDate.SelectionStart)

End Sub

''========================================================================
''    ラジオボタンを選択したら、表示する情報を切り替える。
''========================================================================
Private Sub optShowMode_CheckedChanged(sender As Object, e As EventArgs) _
        Handles optShowRestWin.CheckedChanged, _
                optShowLastWin.CheckedChanged

    updateMagicLine(Me.m_currentLeague, Me.m_currentDate)

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
