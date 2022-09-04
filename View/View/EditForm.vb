Public Class EditForm

Private m_gameRecord As Score4Wrapper.Document.ScoreDocument

Private m_currentDate As System.DateTime
Private m_selectedRecord As Integer
Private m_showIndex() As Integer

''========================================================================
''    設定の初期値を用意する。
''========================================================================
Public Sub setupSettings(
        ByVal objSource As Score4Wrapper.Document.ScoreDocument,
        ByVal startupDate As System.DateTime)

    Dim i As Integer, numTeams As Integer
    Dim strName As String

    If (Me.m_gameRecord Is Nothing) Then
        Me.m_gameRecord = objSource
    End If

    ' チーム一覧を表示する
    With Me.m_gameRecord
        numTeams = .getNumTeams()
        cmbTeamHome.Items.Clear()
        cmbTeamVisitor.Items.Clear()
        For i = 0 To numTeams - 1
            strName = .teamInfo(i).teamName
            cmbTeamHome.Items.Add(strName)
            cmbTeamVisitor.Items.Add(strName)
        Next i
    End With

    ' ゲームフラグ一覧を用意する
    With cmbFlags.Items
        .Clear()
        .Add("0:Empty")
        .Add("1:Schedule")
        .Add("2:Cancel")
        .Add("3:Result")
    End With

    ' 指定した日付を選択する
    mnvEdit.SelectionStart = startupDate
End Sub

''========================================================================
''    レコードテーブルの表示を更新する。
''========================================================================
Private Sub updateRecordTable(ByVal targetDate As System.DateTime)

    m_currentDate = targetDate
    lblDate.Text = targetDate

    displayRecordsToGrid(targetDate, m_gameRecord, Me.Font, dgvRecord)

End Sub

''========================================================================
''    選択した行のデータを変更フレームに表示する。
''========================================================================

Private Sub dgvRecord_CellClick( _
        sender As Object, e As DataGridViewCellEventArgs) _
        Handles dgvRecord.CellClick

    m_selectedRecord = dgvRecord.RowIndex - 2

End Sub

Private Sub mnvEdit_DateChanged(sender As Object, e As DateRangeEventArgs) _
        Handles mnvEdit.DateChanged

    updateRecordTable(mnvEdit.SelectionStart)

End Sub

End Class
