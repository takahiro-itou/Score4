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
    Dim bx As Integer, by As Integer, bw As Integer, bh As Integer
    Dim sc As System.Windows.Forms.Screen
    Dim sx As Integer, sy As Integer, sw As Integer, sh As Integer
    Dim sr As Integer, sb As Integer

    With targetForm
        fw = .Width
        fh = .Height
    End With

    sc = System.Windows.Forms.Screen.FromControl(targetForm)
    With sc.Bounds
        sx = .Left
        sy = .Top
        sw = .Width
        sh = .Height
        sr = .Right
        sb = .Bottom
    End With
    If (ownerForm Is Nothing) Then
        bx = sx
        by = sy
        bw = sw
        bh = sh
    Else
        With ownerForm
            bx = .Left
            by = .Top
            bw = .Width
            bh = .Height
        End With
    End If

    fx = GetSettingINI(iniFileName, iniSecName, "Left", -1)
    fy = GetSettingINI(iniFileName, iniSecName, "Top", -1)
    If (fx < sx) Or (fx + fw > sr) Then
        ' ウィンドウが画面からはみ出す場合は、オーナー中央に移動させる。 '
        fx = bx + (bw - fw) \ 2
    End If
    If (fy < sy) Or (fy + fh > sb) Then
        ' ウィンドウが画面からはみ出す場合は、オーナー中央に移動させる。 '
        fy = by + (bh - fh) \ 2
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
