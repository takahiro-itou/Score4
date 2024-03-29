﻿''================================================================================
''
''================================================================================

Imports System.Runtime.InteropServices

Module WinAPI

''  設定をファイルから読み込む。
<DllImport("KERNEL32.DLL", CharSet:=CharSet.Auto)>
Public Function GetPrivateProfileString(
            ByVal lpAppName As String,
            ByVal lpKeyName As String,
            ByVal lpDefault As String,
            ByVal lpReturnedString As System.Text.StringBuilder,
            ByVal nSize As Integer,
            ByVal lpFileName As String) As Integer
End Function

''  設定をファイルに保存する。
<DllImport("KERNEL32.DLL")>
Public Function WritePrivateProfileString(
            ByVal lpAppName As String,
            ByVal lpKeyName As String,
            ByVal lpString As String,
            ByVal lpFileName As String) As Integer
End Function

''========================================================================
''    アプリケーションの実行ディレクトリを取得する。
''========================================================================
Public Function GetAppPath() As String
    Return System.IO.Path.GetDirectoryName(
        System.Reflection.Assembly.GetExecutingAssembly().Location)
End Function

''========================================================================
''    初期化ファイル（.INIファイル）から設定を読み込む。
''========================================================================
Public Function GetSettingINI(
            ByVal fileName As String,
            ByVal strSection As String,
            ByVal strKey As String,
            ByVal strDefault As String) As String
    Dim retVal As Integer
    Dim strBuf As System.Text.StringBuilder

    strBuf = New System.Text.StringBuilder
    retVal = GetPrivateProfileString(strSection, strKey, strDefault, strBuf, strBuf.Capacity, fileName)
    Return strBuf.ToString()
End Function

''========================================================================
''    初期化ファイル（.INIファイル）に設定を書き込む。
''========================================================================
Public Sub SaveSettingINI(
            ByVal fileName As String,
            ByVal strSection As String,
            ByVal strKey As String,
            ByVal strData As String)
    Dim retVal As Integer

    retVal = WritePrivateProfileString(strSection, strKey, strData, fileName)
    Return
End Sub

End Module
