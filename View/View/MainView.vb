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
Private m_flagMagicMode As Score4Wrapper.MagicNumberMode
Private m_flagExtraView As ExtraViewMode
Private m_flagSchedule As Score4Wrapper.GameFilter

''========================================================================
''    変更点があれば保存するか確認する。
''========================================================================
Private Function isModificationClean() As Boolean

    If (m_flagModified = False) Then
        Return True
    End If

    Dim msgAns As System.Windows.Forms.DialogResult
    msgAns = MessageBox.Show(
        "このデータには変更が加えられています。保存しますか？", "Save",
        MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question)
    If (msgAns = Windows.Forms.DialogResult.Cancel) Then
        Return False
    End If

    If (msgAns = Windows.Forms.DialogResult.Yes) Then

    End If

    Return True
End Function

''========================================================================
''    ファイルを開いてデータを読み込む。
''========================================================================
Private Function openScoreDataFile(
        ByVal fileName As String,
        ByVal flagBinary As Boolean) As Boolean

    Dim retVal As Score4Wrapper.ErrCode
    Dim msgAns As System.Windows.Forms.DialogResult

    Do
        If (flagBinary = False) Then
            retVal = Score4Wrapper.Document.DocumentFile.readFromTextFile(
                fileName, Me.m_scoreData)
        Else
            retVal = Score4Wrapper.Document.DocumentFile.readFromBinaryFile(
                fileName, Me.m_scoreData)
        End If
        If retVal = Score4Wrapper.ErrCode.ERR_SUCCESS Then
            Exit Do
        End If

        msgAns = MessageBox.Show(
            "データの読み込みに失敗しました。再試行しますか？", "Error",
             MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation)
        If (msgAns = vbNo) Then
            openScoreDataFile = False
            Exit Function
        End If
    Loop Until (retVal = Score4Wrapper.ErrCode.ERR_SUCCESS)

    openScoreDataFile = True

End Function

''========================================================================
''    ファイルを開いてデータを読み込む。
''========================================================================
Private Function openScoreDataFromBinary(ByVal fileName As String) As Boolean

    Dim retVal As Boolean

    retVal = openScoreDataFile(fileName, True)
    openScoreDataFromBinary = retVal
    If (retVal = False) Then
        Exit Function
    End If
    openScoreDataFromBinary = postprocessReadScoreData(fileName)

End Function

''========================================================================
''    ファイルを開いてデータを読み込む。
''========================================================================
Private Function openScoreDataFromText(ByVal fileName As String) As Boolean

    Dim retVal As Boolean

    retVal = openScoreDataFile(fileName, False)
    openScoreDataFromText = retVal
    If (retVal = False) Then
        Exit Function
    End If
    openScoreDataFromText = postprocessReadScoreData("")

End Function

''========================================================================
''    データを読み込んだ後の処理を行う。
'========================================================================
Private Function postprocessReadScoreData(ByVal fileName As String) As Boolean

    Dim msgAns As System.Windows.Forms.DialogResult
    Dim flagAutoImport As Boolean = False

    ' 表示内容を最新の情報に更新する。
    m_flagModified = False
    m_scoreData.checkLastDate()
    updateScoreView()

    MessageBox.Show("ロードは正常に完了しました", "Load",
                    MessageBoxButtons.OK, MessageBoxIcon.Information)
    m_lastFileName = fileName

    If (flagAutoImport) Then
        msgAns = MessageBox.Show(
            "データが２日以上前のデータです。今すぐ更新してください。",
            "Old Data File",
            MessageBoxButtons.OKCancel, MessageBoxIcon.Information)
        If (msgAns = vbOK) Then
            processImportData(True)
        End If
    End If

    mnvDate.SelectionStart = m_scoreData.lastActiveDate
    postprocessReadScoreData = True

End Function

''========================================================================
''    データを保存した後の処理を行う。
'========================================================================
Private Function postprocessSaveScoreData(ByVal fileName As String) As Boolean

    ' 表示内容を最新の情報に更新する。
    m_flagModified = False
    updateScoreView()

    MessageBox.Show(
        "保存は正常に完了しました。", "Save",
        MessageBoxButtons.OK, MessageBoxIcon.Information)
    m_lastFileName = fileName

    postprocessSaveScoreData = True

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
            processSaveAs = saveScoreDataToBinary(.FileName)
            Exit Function
        End If
    End With

    processSaveAs = False

End Function

''========================================================================
''    データをファイルに保存する。
''========================================================================
Private Function saveScoreDataFile(
        ByVal fileName As String,
        ByVal flagBinary As Boolean) As Boolean

    Dim retVal As Score4Wrapper.ErrCode
    Dim msgAns As System.Windows.Forms.DialogResult

    ' 保存する前に最終日付をチェック
    Me.m_scoreData.checkLastDate()

    Do
        If (flagBinary = False) Then
            retVal = Score4Wrapper.Document.DocumentFile.saveToTextFile(
                Me.m_scoreData, fileName)
        Else
            retVal = Score4Wrapper.Document.DocumentFile.saveToBinaryFile(
                Me.m_scoreData, fileName)
        End If
        If retVal = Score4Wrapper.ErrCode.ERR_SUCCESS Then
            Exit Do
        End If

        msgAns = MessageBox.Show(
            "データの保存に失敗しました。再試行しますか？",
            "Error",
            MessageBoxButtons.YesNo)
        If (msgAns = vbNo) Then
            saveScoreDataFile = False
            Exit Function
        End If
    Loop Until (retVal = Score4Wrapper.ErrCode.ERR_SUCCESS)

    saveScoreDataFile = True

End Function

''========================================================================
''    データをファイルに保存する。
''========================================================================
Private Function saveScoreDataToBinary(ByVal fileName As String) As Boolean

    Dim retVal As Boolean

    retVal = saveScoreDataFile(fileName, True)
    saveScoreDataToBinary = retVal
    If (retVal = False) Then
        Exit Function
    End If
    saveScoreDataToBinary = postprocessSaveScoreData(fileName)

End Function

''========================================================================
''    データをファイルに保存する。
''========================================================================
Private Function saveScoreDataToText(ByVal fileName As String) As Boolean

    Dim retVal As Boolean

    retVal = saveScoreDataFile(fileName, False)
    saveScoreDataToText = retVal
    If (retVal = False) Then
        Exit Function
    End If
    saveScoreDataToText = postprocessSaveScoreData("")

End Function

''========================================================================
''    ビューの内容を、最新の情報に更新する。
''========================================================================
Private Sub updateScoreView()

    Dim strCaption As String
    Dim lastActiveDate As System.DateTime
    Dim lastRecordDate As System.DateTime

    ScoreView.updateLeagueTab(Me.m_scoreData, Me.tabLeague)

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
            ByVal idxLeague As Integer,
            ByVal trgLastDate As System.DateTime,
            ByVal modeMagic As Score4Wrapper.MagicNumberMode,
            ByVal modeExtra As ExtraViewMode,
            ByVal modeSchedule As Score4Wrapper.GameFilter)

    m_currentLeague = idxLeague
    m_currentDate = trgLastDate
    m_flagMagicMode = modeMagic
    m_flagExtraView = modeExtra
    m_flagSchedule = modeSchedule

    mnuMagicVictory.Checked = False
    mnuMagicPlayoff.Checked = False
    Select Case modeMagic
    Case Score4Wrapper.MagicNumberMode.MAGIC_VICTORY
        mnuMagicVictory.Checked = True
    Case Score4Wrapper.MagicNumberMode.MAGIC_PLAYOFF
        mnuMagicPlayoff.Checked = True
    End Select

    Me.m_scoreData.countScores(trgLastDate)
    ScoreView.displayScoreTableToGrid(
            idxLeague, modeMagic, Me.m_scoreData, Me.dgvScore)

    Select Case modeExtra
    Case ExtraViewMode.EXTRA_VIEW_MAGIC_NUMBERS
        ScoreView.displayTeamMagicTableToGrid(
                idxLeague, modeMagic,
                Me.m_scoreData, Me.dgvExtra
        )
    Case ExtraViewMode.EXTRA_VIEW_WIN_FOR_MATCH
        ScoreView.displayWinsForBeatTableToGrid(
                idxLeague,
                Me.m_scoreData, Me.dgvExtra
        )
    Case Else
        ScoreView.displayRestGameTableToGrid(
                idxLeague, modeSchedule,
                Score4Wrapper.GameFilter.FILTER_ALL_GAMES,
                Me.m_scoreData, Me.dgvExtra
        )
    End Select

    lblDate.Text = trgLastDate
End Sub

''========================================================================
''    チェックボックスの状態によって、残り試合数の表示に
''  日程上の「予定」試合を集計するか決定する
''========================================================================
Private Sub chkSchedule_CheckedChanged(sender As Object, e As EventArgs) _
        Handles chkSchedule.CheckedChanged
Dim flagSchedule As Score4Wrapper.GameFilter

    If (chkSchedule.CheckState = CheckState.Checked) Then
        flagSchedule = Score4Wrapper.GameFilter.FILTER_SCHEDULE
    Else
        flagSchedule = 0
    End If

    updateTables(
        m_currentLeague, m_currentDate, m_flagMagicMode,
        m_flagExtraView, flagSchedule)
End Sub

''========================================================================
''    メニュー「ファイル」－「テキストとしてエクスポート」
''========================================================================
Private Sub mnuFileExportText_Click(sender As Object, e As EventArgs) Handles _
            mnuFileExportText.Click

    With dlgSave
        .DefaultExt = ".csv"
        .FileName = m_lastFileName
        .Filter = "Text files(*.csv;*.txt)|*.csv;*.txt|All files(*.*)|*.*"
        .FilterIndex = 1
        .InitialDirectory = m_appPath
        .OverwritePrompt = True

        If .ShowDialog() = DialogResult.OK Then
            saveScoreDataToText(.FileName)
        End If
    End With

End Sub

''========================================================================
''    メニュー「ファイル」－「終了」
''========================================================================
Private Sub mnuFileExit_Click(sender As Object, e As EventArgs) Handles _
            mnuFileExit.Click
    Application.Exit()
End Sub

''========================================================================
''    メニュー「ファイル」－「新規作成」
''========================================================================
Private Sub mnuFileNew_Click(sender As Object, e As EventArgs) Handles _
            mnuFileNew.Click

End Sub

''========================================================================
''    メニュー「ファイル」－「開く」
''========================================================================
Private Sub mnuFileOpen_Click(sender As Object, e As EventArgs) Handles _
            mnuFileOpen.Click

    If isModificationClean() = False Then Exit Sub

    With dlgOpen
        .DefaultExt = ".gsr"
        .FileName = m_lastFileName
        .Filter = "Game Score Record(*.gsr)|*.gsr|All files(*.*)|*.*"
        .FilterIndex = 1
        .InitialDirectory = m_appPath

        If .ShowDialog() = DialogResult.OK Then
            openScoreDataFromBinary(.FileName)
        End If
    End With

End Sub

''========================================================================
''    メニュー「ファイル」－「テキストを開く」
''========================================================================
Private Sub mnuFileOpenText_Click(sender As Object, e As EventArgs) Handles _
            mnuFileOpenText.Click

    If isModificationClean() = False Then Exit Sub

    With dlgOpen
        .DefaultExt = ".csv"
        .FileName = m_lastFileName
        .Filter = "Text files(*.csv;*.txt)|*.csv;*.txt|All files(*.*)|*.*"
        .FilterIndex = 1
        .InitialDirectory = m_appPath

        If .ShowDialog() = DialogResult.OK Then
            openScoreDataFromText(.FileName)
        End If
    End With

End Sub

''========================================================================
''    メニュー「ファイル」－「上書き保存」
''========================================================================
Private Sub mnuFileSave_Click(sender As Object, e As EventArgs) Handles _
            mnuFileSave.Click

    If (m_lastFileName = "") Then
        processSaveAs()
    Else
        saveScoreDataToBinary(m_lastFileName)
    End If

End Sub

''========================================================================
''    メニュー「ファイル」－「名前をつけて保存」
''========================================================================
Private Sub mnuFileSaveAs_Click(sender As Object, e As EventArgs) Handles _
            mnuFileSaveAs.Click

    processSaveAs()

End Sub

''========================================================================
''    メニュー「マジック」－「簡易計算で行う」
''========================================================================
Private Sub mnuMagicEasy_Click(sender As Object, e As EventArgs) Handles _
            mnuMagicEasy.Click

End Sub

''========================================================================
''    メニュー「マジック」－「詳細表示」
''========================================================================
Private Sub mnuMagicLine_Click(sender As Object, e As EventArgs) Handles _
            mnuMagicLine.Click

    Dim frmLine As LineView = New LineView()

    With frmLine
         .initializeView(Me.m_scoreData, Me.m_currentDate)
        .ShowDialog(Me)

        .Dispose()
    End With

End Sub

''========================================================================
''    メニュー「マジック」－「プレーオフマジック」
''========================================================================
Private Sub mnuMagicPlayoff_Click(sender As Object, e As EventArgs) Handles _
            mnuMagicPlayoff.Click

    updateTables(
        m_currentLeague, m_currentDate,
        Score4Wrapper.MagicNumberMode.MAGIC_PLAYOFF,
        m_flagExtraView, m_flagSchedule)

End Sub

''========================================================================
''    メニュー「マジック」－「優勝マジック」
''========================================================================
Private Sub mnuMagicVictory_Click(sender As Object, e As EventArgs) Handles _
            mnuMagicVictory.Click

    updateTables(
        m_currentLeague, m_currentDate,
        Score4Wrapper.MagicNumberMode.MAGIC_VICTORY,
        m_flagExtraView, m_flagSchedule)

End Sub

''========================================================================
''    メニュー「オプション」－「フォント」
''========================================================================
Private Sub mnuOptionsFont_Click(sender As Object, e As EventArgs) Handles _
            mnuOptionsFont.Click

End Sub

''========================================================================
''    メニュー「スコア」－「詳細」
''========================================================================
Private Sub mnuScoreDetail_Click(sender As Object, e As EventArgs) Handles _
            mnuScoreDetail.Click

End Sub

''========================================================================
''    メニュー「スコア」－「編集」
''========================================================================
Private Sub mnuScoreEdit_Click(sender As Object, e As EventArgs) Handles _
            mnuScoreEdit.Click

    Dim frmEdit As EditForm = New EditForm()

    With frmEdit
        .setupSettings(m_scoreData, m_currentDate)
        .ShowDialog(Me)

        If .isModified() Then
            ' 変更内容を受け取る
            .applyEditData(m_scoreData)
        End If

        .Dispose()
    End With

End Sub

''========================================================================
''    メニュー「スコア」－「インポート」
''========================================================================
Private Sub mnuScoreImport_Click(sender As Object, e As EventArgs) Handles _
            mnuScoreImport.Click

    processImportData(False)

End Sub

''========================================================================
''    メニュー「スコア」－「最新の情報に更新」
''========================================================================
Private Sub mnuScoreRefresh_Click(sender As Object, e As EventArgs) Handles _
            mnuScoreRefresh.Click

End Sub

''========================================================================
''    メニュー「スコア」－「設定の変更」
''========================================================================
Private Sub mnuScoreSettings_Click(sender As Object, e As EventArgs) Handles _
            mnuScoreSettings.Click

End Sub

Private Sub MainView_FormClosing(sender As Object, e As FormClosingEventArgs) _
        Handles Me.FormClosing

    saveWindowPrefs(m_iniFileName, INI_SEC_MAINWINDOW, Me)

End Sub

Private Sub MainView_Load(sender As Object, e As EventArgs) Handles MyBase.Load

    m_scoreData = New Score4Wrapper.Document.ScoreDocument
    m_appPath = GetAppPath()
    m_iniFileName = m_appPath & "\Score.ini"

    moveWindowToStartPosition(m_iniFileName, INI_SEC_MAINWINDOW, Me, Nothing)

    optShowRest.Checked = True

End Sub

''========================================================================
''    カレンダーをクリックしたら、その日付までのデータに切り替える。
''========================================================================
Private Sub mnvDate_DateChanged(sender As Object, e As DateRangeEventArgs) _
        Handles mnvDate.DateChanged

    updateTables(
        m_currentLeague, mnvDate.SelectionStart, m_flagMagicMode,
        m_flagExtraView, m_flagSchedule)

End Sub

''========================================================================
''    ラジオボタンを選択したら、表示する情報を切り替える。
''========================================================================
Private Sub optShowExtra_CheckedChanged(sender As Object, e As EventArgs) _
        Handles optShowRest.CheckedChanged, optShowMagic.CheckedChanged, _
                optShowWins.CheckedChanged

    Dim modeExtra As ExtraViewMode

    If optShowRest.Checked Then
        modeExtra = ExtraViewMode.EXTRA_VIEW_REST_GAMES
    ElseIf optShowMagic.Checked Then
        modeExtra = ExtraViewMode.EXTRA_VIEW_MAGIC_NUMBERS
    ElseIf optShowWins.Checked Then
        modeExtra = ExtraViewMode.EXTRA_VIEW_WIN_FOR_MATCH
    Else
        modeExtra = ExtraViewMode.EXTRA_VIEW_REST_GAMES
    End If

    updateTables(
        m_currentLeague, m_currentDate, m_flagMagicMode,
        modeExtra, m_flagSchedule)

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
    updateTables(
        idxLeague, m_currentDate, m_flagMagicMode,
        m_flagExtraView, m_flagSchedule)

End Sub

End Class
