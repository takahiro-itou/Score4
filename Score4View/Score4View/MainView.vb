Public Class MainView


    Private Const INI_SEC_FONTS As String = "Fonts"
    Private Const INI_SEC_MAINWINDOW As String = "MainWindow"

    Private m_appPath As String
    Private m_iniFileName As String

    Private m_currentFontName As String
    Private m_currentFontSize As Integer

    Private m_flagModified As Boolean
    Private m_lastFileName As String

    ''================================================================================
    ''    変更点があれば保存するか確認する。
    ''================================================================================
    Private Function isModificationClean() As Boolean
        If (m_flagModified = False) Then
            Return True
        End If

        Dim msgAns As System.Windows.Forms.DialogResult
        msgAns = MessageBox.Show("このデータには変更が加えられています。保存しますか？", "Save", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question)
        If (msgAns = Windows.Forms.DialogResult.Cancel) Then
            Return False
        End If

        If (msgAns = Windows.Forms.DialogResult.Yes) Then

        End If

        Return True
    End Function

    ''================================================================================
    ''    ウィンドウを初期位置に移動する。
    ''================================================================================
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

    ''================================================================================
    ''    ファイルを開いてデータを読み込む。
    ''================================================================================
    Private Function processOpenFile(ByVal fileName As String) As Boolean
        Dim objDoc As Score4Wrapper.Common.ScoreDocument
        Dim retVal As Score4Wrapper.Common.ErrCode

        objDoc = New Score4Wrapper.Common.ScoreDocument
        retVal = Score4Wrapper.Common.DocumentFile.readFromBinaryFile(fileName, objDoc)

        MessageBox.Show(retVal)
        Return False
    End Function

    ''================================================================================
    ''    ウィンドウの現在位置を保存する。
    ''================================================================================
    Private Sub saveWindowPrefs()
        With Me
            SaveSettingINI(m_iniFileName, INI_SEC_MAINWINDOW, "Left", .Left)
            SaveSettingINI(m_iniFileName, INI_SEC_MAINWINDOW, "Top", .Top)
        End With
    End Sub

    ''================================================================================
    ''    メニュー「ファイル」－「終了」
    ''================================================================================
    Private Sub mnuFileExit_Click(sender As Object, e As EventArgs) Handles mnuFileExit.Click

    End Sub

    ''================================================================================
    ''    メニュー「ファイル」－「新規作成」
    ''================================================================================
    Private Sub mnuFileNew_Click(sender As Object, e As EventArgs) Handles mnuFileNew.Click

    End Sub

    ''================================================================================
    ''    メニュー「ファイル」－「開く」
    ''================================================================================
    Private Sub mnuFileOpen_Click(sender As Object, e As EventArgs) Handles mnuFileOpen.Click
        If isModificationClean() = False Then Exit Sub

        With dlgOpen
            .DefaultExt = ".gsr"
            .FileName = m_lastFileName
            .Filter = "Game Score Record(*.gsr)|*.gsr|All files(*.*)|*.*"
            .FilterIndex = 1
            .InitialDirectory = m_appPath

            If .ShowDialog() = DialogResult.OK Then
                processOpenFile(.FileName)
            End If
        End With

    End Sub

    ''================================================================================
    ''    メニュー「ファイル」－「上書き保存」
    ''================================================================================
    Private Sub mnuFileSave_Click(sender As Object, e As EventArgs) Handles mnuFileSave.Click

    End Sub

    ''================================================================================
    ''    メニュー「ファイル」－「名前をつけて保存」
    ''================================================================================
    Private Sub mnuFileSaveAs_Click(sender As Object, e As EventArgs) Handles mnuFileSaveAs.Click

    End Sub

    ''================================================================================
    ''    メニュー「マジック」－「簡易計算で行う」
    ''================================================================================
    Private Sub mnuMagicEasy_Click(sender As Object, e As EventArgs) Handles mnuMagicEasy.Click

    End Sub

    ''================================================================================
    ''    メニュー「マジック」－「詳細表示」
    ''================================================================================
    Private Sub mnuMagicLine_Click(sender As Object, e As EventArgs) Handles mnuMagicLine.Click

    End Sub

    ''================================================================================
    ''    メニュー「マジック」－「プレーオフマジック」
    ''================================================================================
    Private Sub mnuMagicPlayoff_Click(sender As Object, e As EventArgs) Handles mnuMagicPlayoff.Click

    End Sub

    ''================================================================================
    ''    メニュー「マジック」－「優勝マジック」
    ''================================================================================
    Private Sub mnuMagicVictory_Click(sender As Object, e As EventArgs) Handles mnuMagicVictory.Click

    End Sub

    ''================================================================================
    ''    メニュー「オプション」－「フォント」
    ''================================================================================
    Private Sub mnuOptionsFont_Click(sender As Object, e As EventArgs) Handles mnuOptionsFont.Click

    End Sub

    ''================================================================================
    ''    メニュー「スコア」－「詳細」
    ''================================================================================
    Private Sub mnuScoreDetail_Click(sender As Object, e As EventArgs) Handles mnuScoreDetail.Click

    End Sub

    ''================================================================================
    ''    メニュー「スコア」－「編集」
    ''================================================================================
    Private Sub mnuScoreEdit_Click(sender As Object, e As EventArgs) Handles mnuScoreEdit.Click

    End Sub

    ''================================================================================
    ''    メニュー「スコア」－「インポート」
    ''================================================================================
    Private Sub mnuScoreImport_Click(sender As Object, e As EventArgs) Handles mnuScoreImport.Click

    End Sub

    ''================================================================================
    ''    メニュー「スコア」－「最新の情報に更新」
    ''================================================================================
    Private Sub mnuScoreRefresh_Click(sender As Object, e As EventArgs) Handles mnuScoreRefresh.Click

    End Sub

    ''================================================================================
    ''    メニュー「スコア」－「設定の変更」
    ''================================================================================
    Private Sub mnuScoreSettings_Click(sender As Object, e As EventArgs) Handles mnuScoreSettings.Click

    End Sub

    Private Sub MainView_FormClosing(sender As Object, e As FormClosingEventArgs) Handles Me.FormClosing
        saveWindowPrefs()
    End Sub

    Private Sub MainView_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        m_appPath = GetAppPath()
        m_iniFileName = m_appPath & "\Score.ini"
        moveWindowToStartPosition()
    End Sub

End Class
