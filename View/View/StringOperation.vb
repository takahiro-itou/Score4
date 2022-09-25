Module StringOperation

''========================================================================
''    指定した桁数で数値を表示する。
''========================================================================
Public Function formatDouble(
       ByVal dValue As Double, ByVal numDigits As Integer) As String

    Dim strFormat As String
    strFormat = repeatString("#.", "0", numDigits)
    formatDouble = dValue.ToString(strFormat)

End Function

''========================================================================
''    指定した文字列を繰り返した文字列を生成する。
''========================================================================
Public Function repeatString(
        ByVal strHead As String,
        ByVal strRep As String,
        ByVal repCount As Integer) As String

    Dim i As Integer
    Dim buf As System.Text.StringBuilder
    buf = New System.Text.StringBuilder(
            strHead.Length + strRep.Length * repCount)

    buf.Append(strHead)
    For i = 1 To repCount
        buf.Append(strRep)
    Next i
    repeatString = buf.ToString()

End Function

End Module
