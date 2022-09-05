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
        cmbTeamAway.Items.Clear()
        For i = 0 To numTeams - 1
            strName = .teamInfo(i).teamName
            cmbTeamHome.Items.Add(strName)
            cmbTeamAway.Items.Add(strName)
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

    displayRecordsToGrid(
        targetDate, m_gameRecord, Me.Font, dgvRecord, m_showIndex)

End Sub

''========================================================================
''    「編集」ボタンのクリックイベントハンドラ。
''========================================================================
Private Sub btnEdit_Click(sender As Object, e As EventArgs) Handles _
            btnEdit.Click

End Sub

''========================================================================
''    「削除」ボタンのクリックイベントハンドラ。
''========================================================================
Private Sub btnDelete_Click(sender As Object, e As EventArgs) Handles _
            btnDelete.Click

    Dim selectedRecord As Integer
    Dim gameRecord As Score4Wrapper.Common.GameResult
    Dim msgAns As System.Windows.Forms.DialogResult

    If (m_selectedRecord < 0) Then
        MessageBox.Show(
            "削除したいレコードを選択してから実行してください。")
        Exit Sub
    End If

    selectedRecord = m_showIndex(m_selectedRecord)
    msgAns = MessageBox.Show(
        "選択したレコードを削除します。よろしいですか？",
        "Delete",
        MessageBoxButtons.YesNo, MessageBoxIcon.Question,
        MessageBoxDefaultButton.Button2)
    If (msgAns <> vbYes) Then
        Exit Sub
    End If

    gameRecord = new Score4Wrapper.Common.GameResult
    With gameRecord
        .eGameFlags   = Score4Wrapper.RecordFlag.GAME_EMPTY
        .homeTeam     = 0
        .awayTeam     = 0
        .homeScore    = 0
        .awayScore    = 0
    End With

    m_gameRecord.setGameRecord(selectedRecord, gameRecord)

End Sub

''========================================================================
''    選択した行のデータを変更フレームに表示する。
''========================================================================
Private Sub dgvRecord_CellClick( _
        sender As Object, e As DataGridViewCellEventArgs) _
        Handles dgvRecord.CellClick

    Dim idxRec As Integer
    Dim gameRecord As Score4Wrapper.Common.GameResult

    For Each r As DataGridViewRow In dgvRecord.SelectedRows
        m_selectedRecord = r.Index - 1
    Next r
    If (m_selectedRecord < 0) Then
        ' 新規データの追加
        btnEdit.Text= "Add"
        If (cmbFlags.SelectedIndex < 0) Then
            cmbFlags.SelectedIndex = Score4Wrapper.RecordFlag.GAME_RESULT
        End If
        cmbTeamHome.SelectedIndex = 0
        cmbTeamAway.SelectedIndex = 1
        updScoreHome.Value = 0
        updScoreAway.Value = 0
    Else
        idxRec = m_showIndex(m_selectedRecord)
        btnEdit.Text = "Edit"
        gameRecord = m_gameRecord.getGameRecord(idxRec)

        With gameRecord
            cmbFlags.SelectedIndex = .eGameFlags
            cmbTeamHome.SelectedIndex = .homeTeam
            cmbTeamAway.SelectedIndex = .awayTeam
            updScoreHome.Value = .homeScore
            updScoreAway.Value = .awayScore
        End With
    End If

End Sub

Private Sub mnvEdit_DateChanged(sender As Object, e As DateRangeEventArgs) _
        Handles mnvEdit.DateChanged

    updateRecordTable(mnvEdit.SelectionStart)

End Sub

End Class
