Public Class EditForm

Private m_workBuffer As Score4Wrapper.Document.ScoreDocument
Private m_editResult As Score4Wrapper.Document.ScoreDocument

Private m_currentDate As System.DateTime
Private m_selectedRecord As Integer
Private m_showIndex() As Integer
Private m_flagModified As Boolean

''========================================================================
''    変更内容を適用する準備。
''========================================================================
Public Sub applyEditData()
    m_editResult.copyFrom(m_workBuffer)
    m_flagModified = True
End Sub

''========================================================================
''    フォームでデータを変更していれば True を返す。
''========================================================================
Public Function isModified() As Boolean
    isModified = m_flagModified
End Function

''========================================================================
''    設定の初期値を用意する。
''========================================================================
Public Sub setupSettings(
        ByVal objSource As Score4Wrapper.Document.ScoreDocument,
        ByVal startupDate As System.DateTime)

    Dim i As Integer, numTeams As Integer
    Dim strName As String

    m_workBuffer = Nothing
    m_editResult = Nothing

    m_workBuffer = Score4Wrapper.Document.ScoreDocument.createCopy(objSource)
    m_editResult = Score4Wrapper.Document.ScoreDocument.createCopy(objSource)

    ' チーム一覧を表示する
    With Me.m_workBuffer
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
        targetDate, m_workBuffer, Me.Font, dgvRecord, m_showIndex)

End Sub

''========================================================================
''    「Apply」 ボタンのクリックイベントハンドラ。
''
''    編集フォームを閉じずに、変更を適用する
''========================================================================
Private Sub btnApply_Click(sender As Object, e As EventArgs) Handles _
            btnApply.Click

    applyEditData()
    updateRecordTable(m_currentDate)

End Sub

''========================================================================
''    「Cancel」ボタンのクリックイベントハンドラ。
''
''    変更を破棄して、編集フォームを閉じる。
''========================================================================
Private Sub btnCancel_Click(sender As Object, e As EventArgs) Handles _
            btnCancel.Click

    Dim msgAns As System.Windows.Forms.DialogResult

    If (m_flagModified = True) Then
        msgAns = MessageBox.Show(
            "Apply ボタンによって既に適用されている変更も取り消しますか？",
            "Cancel",
            MessageBoxButtons.YesNo, MessageBoxIcon.Question)
        If (msgAns = Windows.Forms.DialogResult.Yes) Then
            m_flagModified = False
        Else
            m_flagModified = True
        End If
    Else
        m_flagModified = False
    End If
    Me.Close()

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
    If (msgAns <> DialogResult.Yes) Then
        Exit Sub
    End If

    gameRecord = new Score4Wrapper.Common.GameResult
    With gameRecord
        .eGameFlags = Score4Wrapper.RecordFlag.GAME_EMPTY
        .homeTeam   = 0
        .awayTeam   = 0
        .homeScore  = 0
        .awayScore  = 0
    End With

    m_workBuffer.setGameRecord(selectedRecord, gameRecord)
    updateRecordTable(m_currentDate)

End Sub

''========================================================================
''    「編集」ボタンのクリックイベントハンドラ。
''========================================================================
Private Sub btnEdit_Click(sender As Object, e As EventArgs) Handles _
            btnEdit.Click

    Dim selectedRecord As Integer
    Dim gameRecord As Score4Wrapper.Common.GameResult
    ' Dim msgAns As System.Windows.Forms.DialogResult

    ' 入力されたデータを集計する。
    gameRecord = new Score4Wrapper.Common.GameResult
    With gameRecord
        .eGameFlags = cmbFlags.SelectedIndex
        .recordDate = m_currentDate
        .homeTeam   = cmbTeamHome.SelectedIndex
        .awayTeam   = cmbTeamAway.SelectedIndex
        .homeScore  = updScoreHome.Value
        .awayScore  = updScoreAway.Value
    End With

    If (m_selectedRecord < 0) Then
        ' 新規データの追加
    Else
        ' 既存データの変更
        selectedRecord = m_showIndex(m_selectedRecord)
        m_workBuffer.setGameRecord(selectedRecord, gameRecord)
    End If

    updateRecordTable(m_currentDate)

End Sub

''========================================================================
''    「OK」ボタンのクリックイベントハンドラ。
''
''    編集フォームを閉じずに、変更を適用する
''========================================================================
Private Sub btnOK_Click(sender As Object, e As EventArgs) Handles _
            btnOK.Click

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
        gameRecord = m_workBuffer.getGameRecord(idxRec)

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
