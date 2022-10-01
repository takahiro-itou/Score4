Module AppCommon

''========================================================================
''    ウィンドウを初期位置に移動する。
''========================================================================
Public Sub moveWindowToStartPosition(
        ByVal iniFileName As String,
        ByVal iniSecName As String,
        ByRef targetForm As System.Windows.Forms.Form,
        ByRef ownerForm As System.Windows.Forms.Form)

    Dim fx As Integer, fy As Integer, fw As Integer, fh As Integer
    Dim sc As System.Windows.Forms.Screen
    Dim sx As Integer, sy As Integer

    With targetForm
        fw = .Width
        fh = .Height
    End With

    sc = System.Windows.Forms.Screen.FromControl(targetForm)
    With sc.Bounds
        sx = .Left
        sy = .Top
    End With

    fx = GetSettingINI(iniFileName, iniSecName, "Left", -1)
    fy = GetSettingINI(iniFileName, iniSecName, "Top", -1)
    If (fx < sx) Or (fx + fw > sc.Bounds.Right) Then
        ' ウィンドウが画面からはみ出す場合は、画面中央に移動させる。 '
        fx = sx + (sc.Bounds.Width - fw) \ 2
    End If
    If (fy < sy) Or (fy + fh > sc.Bounds.Bottom) Then
        ' ウィンドウが画面からはみ出す場合は、画面中央に移動させる。 '
        fy = sy + (sc.Bounds.Height - fh) \ 2
    End If

    targetForm.Bounds = New Rectangle(fx, fy, fw, fh)

End Sub

''========================================================================
''    ウィンドウの現在位置を保存する。
''========================================================================
Public Sub saveWindowPrefs(
        ByVal iniFileName As String,
        ByVal iniSecName As String,
        ByRef sourceForm As System.Windows.Forms.Form)

    With sourceForm
        SaveSettingINI(iniFileName, iniSecName, "Left", .Left)
        SaveSettingINI(iniFileName, iniSecName, "Height", .Height)
        SaveSettingINI(iniFileName, iniSecName, "Top", .Top)
        SaveSettingINI(iniFileName, iniSecName, "Width", .Width)
    End With

End Sub

End Module
