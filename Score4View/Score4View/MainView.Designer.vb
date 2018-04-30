<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class MainView
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(MainView))
        Me.mnuMain = New System.Windows.Forms.MenuStrip()
        Me.mnuFile = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuFileNew = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuFileOpen = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuFileSep0 = New System.Windows.Forms.ToolStripSeparator()
        Me.mnuFileSave = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuFileSaveAs = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuFileSep1 = New System.Windows.Forms.ToolStripSeparator()
        Me.mnuFileExit = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuScore = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuScoreEdit = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuScoreDetail = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuScoreImport = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuScoreSep0 = New System.Windows.Forms.ToolStripSeparator()
        Me.mnuScoreSettings = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuScoreSep1 = New System.Windows.Forms.ToolStripSeparator()
        Me.mnuScoreRefresh = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuMagic = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuMagicVictory = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuMagicPlayoff = New System.Windows.Forms.ToolStripMenuItem()
        Me.ToolStripMenuItem1 = New System.Windows.Forms.ToolStripSeparator()
        Me.mnuMagicEasy = New System.Windows.Forms.ToolStripMenuItem()
        Me.ToolStripMenuItem2 = New System.Windows.Forms.ToolStripSeparator()
        Me.mnuMagicLine = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuOptions = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuOptionsFont = New System.Windows.Forms.ToolStripMenuItem()
        Me.dlgOpen = New System.Windows.Forms.OpenFileDialog()
        Me.dlgSave = New System.Windows.Forms.SaveFileDialog()
        Me.dlgFont = New System.Windows.Forms.FontDialog()
        Me.mnuMain.SuspendLayout()
        Me.SuspendLayout()
        '
        'mnuMain
        '
        resources.ApplyResources(Me.mnuMain, "mnuMain")
        Me.mnuMain.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.mnuFile, Me.mnuScore, Me.mnuMagic, Me.mnuOptions})
        Me.mnuMain.Name = "mnuMain"
        '
        'mnuFile
        '
        resources.ApplyResources(Me.mnuFile, "mnuFile")
        Me.mnuFile.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.mnuFileNew, Me.mnuFileOpen, Me.mnuFileSep0, Me.mnuFileSave, Me.mnuFileSaveAs, Me.mnuFileSep1, Me.mnuFileExit})
        Me.mnuFile.Name = "mnuFile"
        '
        'mnuFileNew
        '
        resources.ApplyResources(Me.mnuFileNew, "mnuFileNew")
        Me.mnuFileNew.Name = "mnuFileNew"
        '
        'mnuFileOpen
        '
        resources.ApplyResources(Me.mnuFileOpen, "mnuFileOpen")
        Me.mnuFileOpen.Name = "mnuFileOpen"
        '
        'mnuFileSep0
        '
        resources.ApplyResources(Me.mnuFileSep0, "mnuFileSep0")
        Me.mnuFileSep0.Name = "mnuFileSep0"
        '
        'mnuFileSave
        '
        resources.ApplyResources(Me.mnuFileSave, "mnuFileSave")
        Me.mnuFileSave.Name = "mnuFileSave"
        '
        'mnuFileSaveAs
        '
        resources.ApplyResources(Me.mnuFileSaveAs, "mnuFileSaveAs")
        Me.mnuFileSaveAs.Name = "mnuFileSaveAs"
        '
        'mnuFileSep1
        '
        resources.ApplyResources(Me.mnuFileSep1, "mnuFileSep1")
        Me.mnuFileSep1.Name = "mnuFileSep1"
        '
        'mnuFileExit
        '
        resources.ApplyResources(Me.mnuFileExit, "mnuFileExit")
        Me.mnuFileExit.Name = "mnuFileExit"
        '
        'mnuScore
        '
        resources.ApplyResources(Me.mnuScore, "mnuScore")
        Me.mnuScore.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.mnuScoreEdit, Me.mnuScoreDetail, Me.mnuScoreImport, Me.mnuScoreSep0, Me.mnuScoreSettings, Me.mnuScoreSep1, Me.mnuScoreRefresh})
        Me.mnuScore.Name = "mnuScore"
        '
        'mnuScoreEdit
        '
        resources.ApplyResources(Me.mnuScoreEdit, "mnuScoreEdit")
        Me.mnuScoreEdit.Name = "mnuScoreEdit"
        '
        'mnuScoreDetail
        '
        resources.ApplyResources(Me.mnuScoreDetail, "mnuScoreDetail")
        Me.mnuScoreDetail.Name = "mnuScoreDetail"
        '
        'mnuScoreImport
        '
        resources.ApplyResources(Me.mnuScoreImport, "mnuScoreImport")
        Me.mnuScoreImport.Name = "mnuScoreImport"
        '
        'mnuScoreSep0
        '
        resources.ApplyResources(Me.mnuScoreSep0, "mnuScoreSep0")
        Me.mnuScoreSep0.Name = "mnuScoreSep0"
        '
        'mnuScoreSettings
        '
        resources.ApplyResources(Me.mnuScoreSettings, "mnuScoreSettings")
        Me.mnuScoreSettings.Name = "mnuScoreSettings"
        '
        'mnuScoreSep1
        '
        resources.ApplyResources(Me.mnuScoreSep1, "mnuScoreSep1")
        Me.mnuScoreSep1.Name = "mnuScoreSep1"
        '
        'mnuScoreRefresh
        '
        resources.ApplyResources(Me.mnuScoreRefresh, "mnuScoreRefresh")
        Me.mnuScoreRefresh.Name = "mnuScoreRefresh"
        '
        'mnuMagic
        '
        resources.ApplyResources(Me.mnuMagic, "mnuMagic")
        Me.mnuMagic.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.mnuMagicVictory, Me.mnuMagicPlayoff, Me.ToolStripMenuItem1, Me.mnuMagicEasy, Me.ToolStripMenuItem2, Me.mnuMagicLine})
        Me.mnuMagic.Name = "mnuMagic"
        '
        'mnuMagicVictory
        '
        resources.ApplyResources(Me.mnuMagicVictory, "mnuMagicVictory")
        Me.mnuMagicVictory.Name = "mnuMagicVictory"
        '
        'mnuMagicPlayoff
        '
        resources.ApplyResources(Me.mnuMagicPlayoff, "mnuMagicPlayoff")
        Me.mnuMagicPlayoff.Name = "mnuMagicPlayoff"
        '
        'ToolStripMenuItem1
        '
        resources.ApplyResources(Me.ToolStripMenuItem1, "ToolStripMenuItem1")
        Me.ToolStripMenuItem1.Name = "ToolStripMenuItem1"
        '
        'mnuMagicEasy
        '
        resources.ApplyResources(Me.mnuMagicEasy, "mnuMagicEasy")
        Me.mnuMagicEasy.Name = "mnuMagicEasy"
        '
        'ToolStripMenuItem2
        '
        resources.ApplyResources(Me.ToolStripMenuItem2, "ToolStripMenuItem2")
        Me.ToolStripMenuItem2.Name = "ToolStripMenuItem2"
        '
        'mnuMagicLine
        '
        resources.ApplyResources(Me.mnuMagicLine, "mnuMagicLine")
        Me.mnuMagicLine.Name = "mnuMagicLine"
        '
        'mnuOptions
        '
        resources.ApplyResources(Me.mnuOptions, "mnuOptions")
        Me.mnuOptions.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.mnuOptionsFont})
        Me.mnuOptions.Name = "mnuOptions"
        '
        'mnuOptionsFont
        '
        resources.ApplyResources(Me.mnuOptionsFont, "mnuOptionsFont")
        Me.mnuOptionsFont.Name = "mnuOptionsFont"
        '
        'dlgOpen
        '
        Me.dlgOpen.FileName = "OpenFileDialog1"
        resources.ApplyResources(Me.dlgOpen, "dlgOpen")
        '
        'dlgSave
        '
        resources.ApplyResources(Me.dlgSave, "dlgSave")
        '
        'MainView
        '
        resources.ApplyResources(Me, "$this")
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.Controls.Add(Me.mnuMain)
        Me.MainMenuStrip = Me.mnuMain
        Me.Name = "MainView"
        Me.mnuMain.ResumeLayout(False)
        Me.mnuMain.PerformLayout()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents mnuMain As System.Windows.Forms.MenuStrip
    Friend WithEvents dlgOpen As System.Windows.Forms.OpenFileDialog
    Friend WithEvents dlgSave As System.Windows.Forms.SaveFileDialog
    Friend WithEvents dlgFont As System.Windows.Forms.FontDialog
    Friend WithEvents mnuFile As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuFileNew As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuFileOpen As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuFileSep0 As System.Windows.Forms.ToolStripSeparator
    Friend WithEvents mnuFileSave As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuFileSaveAs As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuFileSep1 As System.Windows.Forms.ToolStripSeparator
    Friend WithEvents mnuFileExit As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuScore As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuScoreEdit As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuScoreDetail As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuScoreImport As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuScoreSep0 As System.Windows.Forms.ToolStripSeparator
    Friend WithEvents mnuScoreSettings As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuScoreSep1 As System.Windows.Forms.ToolStripSeparator
    Friend WithEvents mnuScoreRefresh As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuMagic As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuOptions As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuOptionsFont As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuMagicVictory As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuMagicPlayoff As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ToolStripMenuItem1 As System.Windows.Forms.ToolStripSeparator
    Friend WithEvents mnuMagicEasy As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ToolStripMenuItem2 As System.Windows.Forms.ToolStripSeparator
    Friend WithEvents mnuMagicLine As System.Windows.Forms.ToolStripMenuItem

End Class
