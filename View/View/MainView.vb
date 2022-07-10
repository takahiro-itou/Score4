Public Class MainView

Private Const INI_SEC_FONTS As String = "Fonts"
Private Const INI_SEC_MAINWINDOW As String = "MainWindow"

Private m_appPath As String
Private m_iniFileName As String

Private m_currentFontName As String
Private m_currentFontSize As Integer

Private m_flagModified As Boolean
Private m_lastFileName As String

Private m_scoreData As Score4Wrapper.Document.ScoreDocument

Private m_currentLeague As Integer
Private m_currentDate As System.DateTime
Private m_flagMagicMode As Integer
Private m_flagExtraView As Integer
Private m_flagSchedule As Integer

''========================================================================
''    変更点があれば保存するか確認する。
''========================================================================
Private Function isModificationClean() As Boolean

    If (m_flagModified = False) Then
        Return True
    End If

    Dim msgAns As System.Windows.Forms.DialogResult
    msgAns = MessageBox.Show("このデータには変更が加えられています。保存しますか？", "Save",
                                MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question)
    If (msgAns = Windows.Forms.DialogResult.Cancel) Then
        Return False
    End If

    If (msgAns = Windows.Forms.DialogResult.Yes) Then

    End If

    Return True
End Function

''========================================================================
''    ウィンドウを初期位置に移動する。
''========================================================================
Private Sub moveWindowToStartPosition()

    Dim fx As Integer
    Dim fy As Integer
    Dim fw As Integer = Me.Width
    Dim fh As Integer = Me.Height

    Dim sc As System.Windows.Forms.Screen = System.Windows.Forms.Screen.FromControl(Me)
    Dim sx As Integer = sc.Bounds.Left
    Dim sy As Integer = sc.Bounds.Top

    fx = GetSettingINI(m_iniFileName, INI_SEC_MAINWINDOW, "Left", -1)
    fy = GetSettingINI(m_iniFileName, INI_SEC_MAINWINDOW, "Top", -1)
    If (fx < sx) Or (fx + fw > sc.Bounds.Right) Then
        ' ウィンドウが画面からはみ出す場合は、画面中央に移動させる。 '
        fx = sx + (sc.Bounds.Width - fw) \ 2
    End If
    If (fy < sy) Or (fy + fh > sc.Bounds.Bottom) Then
        ' ウィンドウが画面からはみ出す場合は、画面中央に移動させる。 '
        fy = sy + (sc.Bounds.Height - fh) \ 2
    End If

    Me.Bounds = New Rectangle(fx, fy, fw, fh)
End Sub

''========================================================================
''    ファイルを開いてデータを読み込む。
''========================================================================
Private Function openScoreData(ByVal fileName As String) As Boolean

    Dim retVal As Score4Wrapper.ErrCode
    Dim msgAns As System.Windows.Forms.DialogResult

    Do
        retVal = Score4Wrapper.Document.DocumentFile.readFromBinaryFile(fileName, Me.m_scoreData)
        If retVal = Score4Wrapper.ErrCode.ERR_SUCCESS Then
            Exit Do
        End If

        msgAns = MessageBox.Show("データの読み込みに失敗しました。再試行しますか？", "Error",
                                    MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation)
        If (msgAns = vbNo) Then
            Return False
        End If
    Loop Until (retVal = Score4Wrapper.ErrCode.ERR_SUCCESS)

    ' 表示内容を最新の情報に更新する。
    m_flagModified = False
    updateScoreView()

    MessageBox.Show("ロードは正常に完了しました", "Load",
                    MessageBoxButtons.OK, MessageBoxIcon.Information)
    m_lastFileName = fileName

    Dim flagAutoImport As Boolean = False

    If (flagAutoImport) Then
        msgAns = MessageBox.Show("データが２日以上前のデータです。今すぐ更新してください。", "Old Data File",
                                    MessageBoxButtons.OKCancel, MessageBoxIcon.Information)
        If (msgAns = vbOK) Then
            processImportData(True)
        End If
    End If

    mnvDate.SelectionStart = m_scoreData.lastActiveDate
    Return True
End Function

''========================================================================
''    データをインポートする。
''========================================================================
Private Function processImportData(ByVal importAutoStart As Boolean) As Boolean
    Return False
End Function

''========================================================================
''    ファイル名を指定して保存する。
''========================================================================
Private Function processSaveAs() As Boolean
    With dlgSave
        .DefaultExt = ".gsr"
        .FileName = m_lastFileName
        .Filter = "Game Score Record(*.gsr)|*.gsr|All files(*.*)|*.*"
        .FilterIndex = 1
        .InitialDirectory = m_appPath
        .OverwritePrompt = True

        If .ShowDialog() = DialogResult.OK Then
            Return saveScoreData(.FileName)
        End If
    End With

    Return False
End Function

''========================================================================
''    データをファイルに保存する。
''========================================================================
Private Function saveScoreData(ByVal fileName As String) As Boolean
    Dim retVal As Score4Wrapper.ErrCode
    Dim msgAns As System.Windows.Forms.DialogResult

    Do
        retVal = Score4Wrapper.Document.DocumentFile.saveToBinaryFile(Me.m_scoreData, fileName)
        If retVal = Score4Wrapper.ErrCode.ERR_SUCCESS Then
            Exit Do
        End If

        msgAns = MessageBox.Show("データの保存に失敗しました。再試行しますか？",
                                    "Error", MessageBoxButtons.YesNo)
        If (msgAns = vbNo) Then
            Return False
        End If
    Loop Until (retVal = Score4Wrapper.ErrCode.ERR_SUCCESS)

    m_flagModified = False
    updateScoreView()

    MessageBox.Show("保存は正常に完了しました。", "Save",
                    MessageBoxButtons.OK, MessageBoxIcon.Information)
    m_lastFileName = fileName

    Return True
End Function

''========================================================================
''    ウィンドウの現在位置を保存する。
''========================================================================
Private Sub saveWindowPrefs()
    With Me
        SaveSettingINI(m_iniFileName, INI_SEC_MAINWINDOW, "Left", .Left)
        SaveSettingINI(m_iniFileName, INI_SEC_MAINWINDOW, "Top", .Top)
    End With
End Sub

Private Sub updateLeagueTab()
    Dim numLeagues As Integer = m_scoreData.getNumLeagues()

    With Me.tabLeague
        .TabPages.Clear()
        For i = 0 To numLeagues - 1
            Dim leagueInfo As Score4Wrapper.Common.LeagueInfo = m_scoreData.leagueInfo(i)
            Dim leagueTab As System.Windows.Forms.TabPage = New System.Windows.Forms.TabPage(leagueInfo.leagueName)
            .TabPages.Add(leagueTab)
        Next
    End With
End Sub

''========================================================================
''    ビューの内容を、最新の情報に更新する。
''========================================================================
Private Sub updateScoreView()

    Dim strCaption As String
    Dim lastActiveDate As System.DateTime
    Dim lastRecordDate As System.DateTime
    updateLeagueTab()

    ' ウィンドウのキャプション。
    strCaption = "成績／順位　: "
    With Me.m_scoreData
        lastActiveDate = .lastActiveDate
        lastRecordDate = .lastRecordDate
    End With
    strCaption = strCaption &
            Format(lastActiveDate, "yyyy/MM/dd") &
            "まで (日程は" &
            Format(lastRecordDate, "yyyy/MM/dd") & "まで)"
    If (m_flagModified) Then
        strCaption = strCaption & " *変更あり"
    End If
    Me.Text = strCaption
End Sub

Private Sub updateTables(
            ByVal idxLeague As Integer, ByVal trgLastDate As System.DateTime,
            ByVal modeMagic As Integer, ByVal modeExtra As Integer, ByVal modeSchedule As Integer)
    m_currentLeague = idxLeague
    m_currentDate = trgLastDate
    m_flagMagicMode = modeMagic
    m_flagExtraView = modeExtra
    m_flagSchedule = modeSchedule

    Me.m_scoreData.countScores(trgLastDate)
    ScoreView.displayScoreTableToGrid(
            idxLeague, modeMagic, Me.m_scoreData, Me.grdScore)
    ScoreView.displayRestGameTableToGrid(
            idxLeague,
            Score4Wrapper.GameFilter.FILTER_SCHEDULE,
            Score4Wrapper.GameFilter.FILTER_ALL_GAMES,
            Me.m_scoreData, Me.grdExtra
    )

    lblDate.Text = trgLastDate
End Sub

''========================================================================
''    メニュー「ファイル」－「終了」
''========================================================================
Private Sub mnuFileExit_Click(sender As Object, e As EventArgs) Handles mnuFileExit.Click
    Application.Exit()
End Sub

''========================================================================
''    メニュー「ファイル」－「新規作成」
''========================================================================
Private Sub mnuFileNew_Click(sender As Object, e As EventArgs) Handles mnuFileNew.Click

End Sub

''========================================================================
''    メニュー「ファイル」－「開く」
''========================================================================
Private Sub mnuFileOpen_Click(sender As Object, e As EventArgs) Handles mnuFileOpen.Click

    If isModificationClean() = False Then Exit Sub

    With dlgOpen
        .DefaultExt = ".gsr"
        .FileName = m_lastFileName
        .Filter = "Game Score Record(*.gsr)|*.gsr|All files(*.*)|*.*"
        .FilterIndex = 1
        .InitialDirectory = m_appPath

        If .ShowDialog() = DialogResult.OK Then
            openScoreData(.FileName)
        End If
    End With

End Sub

''========================================================================
''    メニュー「ファイル」－「上書き保存」
''========================================================================
Private Sub mnuFileSave_Click(sender As Object, e As EventArgs) Handles mnuFileSave.Click
    If (m_lastFileName = "") Then
        processSaveAs()
    Else
        saveScoreData(m_lastFileName)
    End If
End Sub

''========================================================================
''    メニュー「ファイル」－「名前をつけて保存」
''========================================================================
Private Sub mnuFileSaveAs_Click(sender As Object, e As EventArgs) Handles mnuFileSaveAs.Click
    processSaveAs()
End Sub

''========================================================================
''    メニュー「マジック」－「簡易計算で行う」
''========================================================================
Private Sub mnuMagicEasy_Click(sender As Object, e As EventArgs) Handles mnuMagicEasy.Click

End Sub

''========================================================================
''    メニュー「マジック」－「詳細表示」
''========================================================================
Private Sub mnuMagicLine_Click(sender As Object, e As EventArgs) Handles mnuMagicLine.Click

End Sub

''========================================================================
''    メニュー「マジック」－「プレーオフマジック」
''========================================================================
Private Sub mnuMagicPlayoff_Click(sender As Object, e As EventArgs) Handles mnuMagicPlayoff.Click

End Sub

''========================================================================
''    メニュー「マジック」－「優勝マジック」
''========================================================================
Private Sub mnuMagicVictory_Click(sender As Object, e As EventArgs) Handles mnuMagicVictory.Click

End Sub

''========================================================================
''    メニュー「オプション」－「フォント」
''========================================================================
Private Sub mnuOptionsFont_Click(sender As Object, e As EventArgs) Handles mnuOptionsFont.Click

End Sub

''========================================================================
''    メニュー「スコア」－「詳細」
''========================================================================
Private Sub mnuScoreDetail_Click(sender As Object, e As EventArgs) Handles mnuScoreDetail.Click

End Sub

''========================================================================
''    メニュー「スコア」－「編集」
''========================================================================
Private Sub mnuScoreEdit_Click(sender As Object, e As EventArgs) Handles mnuScoreEdit.Click

End Sub

''========================================================================
''    メニュー「スコア」－「インポート」
''========================================================================
Private Sub mnuScoreImport_Click(sender As Object, e As EventArgs) Handles mnuScoreImport.Click
    processImportData(False)
End Sub

''========================================================================
''    メニュー「スコア」－「最新の情報に更新」
''========================================================================
Private Sub mnuScoreRefresh_Click(sender As Object, e As EventArgs) Handles mnuScoreRefresh.Click

End Sub

''========================================================================
''    メニュー「スコア」－「設定の変更」
''========================================================================
Private Sub mnuScoreSettings_Click(sender As Object, e As EventArgs) Handles mnuScoreSettings.Click

End Sub

Private Sub MainView_FormClosing(sender As Object, e As FormClosingEventArgs) Handles Me.FormClosing
    saveWindowPrefs()
End Sub

Private Sub MainView_Load(sender As Object, e As EventArgs) Handles MyBase.Load
    m_scoreData = New Score4Wrapper.Document.ScoreDocument
    m_appPath = GetAppPath()
    m_iniFileName = m_appPath & "\Score.ini"
    moveWindowToStartPosition()
End Sub

Private Sub tabLeague_SelectedIndexChanged(sender As Object, e As EventArgs) Handles tabLeague.SelectedIndexChanged
    Dim idxLeague As Integer = tabLeague.SelectedIndex
    updateTables(idxLeague, m_currentDate, m_flagMagicMode, m_flagExtraView, m_flagSchedule)
End Sub

Private Sub mnvDate_DateChanged(sender As Object, e As DateRangeEventArgs) Handles mnvDate.DateChanged
    updateTables(m_currentLeague, mnvDate.SelectionStart, m_flagMagicMode, m_flagExtraView, m_flagSchedule)
End Sub

End Class
