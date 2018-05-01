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
        Me.mnuMagicSep0 = New System.Windows.Forms.ToolStripSeparator()
        Me.mnuMagicEasy = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuMagicSep1 = New System.Windows.Forms.ToolStripSeparator()
        Me.mnuMagicLine = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuOptions = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuOptionsFont = New System.Windows.Forms.ToolStripMenuItem()
        Me.dlgOpen = New System.Windows.Forms.OpenFileDialog()
        Me.dlgSave = New System.Windows.Forms.SaveFileDialog()
        Me.dlgFont = New System.Windows.Forms.FontDialog()
        Me.grpScore = New System.Windows.Forms.GroupBox()
        Me.DataGridView2 = New System.Windows.Forms.DataGridView()
        Me.optShowWins = New System.Windows.Forms.RadioButton()
        Me.optShowMagic = New System.Windows.Forms.RadioButton()
        Me.optShowRest = New System.Windows.Forms.RadioButton()
        Me.chkSchedule = New System.Windows.Forms.CheckBox()
        Me.MonthCalendar1 = New System.Windows.Forms.MonthCalendar()
        Me.DataGridView1 = New System.Windows.Forms.DataGridView()
        Me.tabLeague = New System.Windows.Forms.TabControl()
        Me.mnuMain.SuspendLayout()
        Me.grpScore.SuspendLayout()
        CType(Me.DataGridView2, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.DataGridView1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'mnuMain
        '
        Me.mnuMain.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.mnuFile, Me.mnuScore, Me.mnuMagic, Me.mnuOptions})
        resources.ApplyResources(Me.mnuMain, "mnuMain")
        Me.mnuMain.Name = "mnuMain"
        '
        'mnuFile
        '
        Me.mnuFile.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.mnuFileNew, Me.mnuFileOpen, Me.mnuFileSep0, Me.mnuFileSave, Me.mnuFileSaveAs, Me.mnuFileSep1, Me.mnuFileExit})
        Me.mnuFile.Name = "mnuFile"
        resources.ApplyResources(Me.mnuFile, "mnuFile")
        '
        'mnuFileNew
        '
        Me.mnuFileNew.Name = "mnuFileNew"
        resources.ApplyResources(Me.mnuFileNew, "mnuFileNew")
        '
        'mnuFileOpen
        '
        Me.mnuFileOpen.Name = "mnuFileOpen"
        resources.ApplyResources(Me.mnuFileOpen, "mnuFileOpen")
        '
        'mnuFileSep0
        '
        Me.mnuFileSep0.Name = "mnuFileSep0"
        resources.ApplyResources(Me.mnuFileSep0, "mnuFileSep0")
        '
        'mnuFileSave
        '
        Me.mnuFileSave.Name = "mnuFileSave"
        resources.ApplyResources(Me.mnuFileSave, "mnuFileSave")
        '
        'mnuFileSaveAs
        '
        Me.mnuFileSaveAs.Name = "mnuFileSaveAs"
        resources.ApplyResources(Me.mnuFileSaveAs, "mnuFileSaveAs")
        '
        'mnuFileSep1
        '
        Me.mnuFileSep1.Name = "mnuFileSep1"
        resources.ApplyResources(Me.mnuFileSep1, "mnuFileSep1")
        '
        'mnuFileExit
        '
        Me.mnuFileExit.Name = "mnuFileExit"
        resources.ApplyResources(Me.mnuFileExit, "mnuFileExit")
        '
        'mnuScore
        '
        Me.mnuScore.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.mnuScoreEdit, Me.mnuScoreDetail, Me.mnuScoreImport, Me.mnuScoreSep0, Me.mnuScoreSettings, Me.mnuScoreSep1, Me.mnuScoreRefresh})
        Me.mnuScore.Name = "mnuScore"
        resources.ApplyResources(Me.mnuScore, "mnuScore")
        '
        'mnuScoreEdit
        '
        Me.mnuScoreEdit.Name = "mnuScoreEdit"
        resources.ApplyResources(Me.mnuScoreEdit, "mnuScoreEdit")
        '
        'mnuScoreDetail
        '
        Me.mnuScoreDetail.Name = "mnuScoreDetail"
        resources.ApplyResources(Me.mnuScoreDetail, "mnuScoreDetail")
        '
        'mnuScoreImport
        '
        Me.mnuScoreImport.Name = "mnuScoreImport"
        resources.ApplyResources(Me.mnuScoreImport, "mnuScoreImport")
        '
        'mnuScoreSep0
        '
        Me.mnuScoreSep0.Name = "mnuScoreSep0"
        resources.ApplyResources(Me.mnuScoreSep0, "mnuScoreSep0")
        '
        'mnuScoreSettings
        '
        Me.mnuScoreSettings.Name = "mnuScoreSettings"
        resources.ApplyResources(Me.mnuScoreSettings, "mnuScoreSettings")
        '
        'mnuScoreSep1
        '
        Me.mnuScoreSep1.Name = "mnuScoreSep1"
        resources.ApplyResources(Me.mnuScoreSep1, "mnuScoreSep1")
        '
        'mnuScoreRefresh
        '
        Me.mnuScoreRefresh.Name = "mnuScoreRefresh"
        resources.ApplyResources(Me.mnuScoreRefresh, "mnuScoreRefresh")
        '
        'mnuMagic
        '
        Me.mnuMagic.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.mnuMagicVictory, Me.mnuMagicPlayoff, Me.mnuMagicSep0, Me.mnuMagicEasy, Me.mnuMagicSep1, Me.mnuMagicLine})
        Me.mnuMagic.Name = "mnuMagic"
        resources.ApplyResources(Me.mnuMagic, "mnuMagic")
        '
        'mnuMagicVictory
        '
        Me.mnuMagicVictory.Name = "mnuMagicVictory"
        resources.ApplyResources(Me.mnuMagicVictory, "mnuMagicVictory")
        '
        'mnuMagicPlayoff
        '
        Me.mnuMagicPlayoff.Name = "mnuMagicPlayoff"
        resources.ApplyResources(Me.mnuMagicPlayoff, "mnuMagicPlayoff")
        '
        'mnuMagicSep0
        '
        Me.mnuMagicSep0.Name = "mnuMagicSep0"
        resources.ApplyResources(Me.mnuMagicSep0, "mnuMagicSep0")
        '
        'mnuMagicEasy
        '
        Me.mnuMagicEasy.Name = "mnuMagicEasy"
        resources.ApplyResources(Me.mnuMagicEasy, "mnuMagicEasy")
        '
        'mnuMagicSep1
        '
        Me.mnuMagicSep1.Name = "mnuMagicSep1"
        resources.ApplyResources(Me.mnuMagicSep1, "mnuMagicSep1")
        '
        'mnuMagicLine
        '
        Me.mnuMagicLine.Name = "mnuMagicLine"
        resources.ApplyResources(Me.mnuMagicLine, "mnuMagicLine")
        '
        'mnuOptions
        '
        Me.mnuOptions.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.mnuOptionsFont})
        Me.mnuOptions.Name = "mnuOptions"
        resources.ApplyResources(Me.mnuOptions, "mnuOptions")
        '
        'mnuOptionsFont
        '
        Me.mnuOptionsFont.Name = "mnuOptionsFont"
        resources.ApplyResources(Me.mnuOptionsFont, "mnuOptionsFont")
        '
        'dlgOpen
        '
        Me.dlgOpen.FileName = "OpenFileDialog1"
        '
        'grpScore
        '
        resources.ApplyResources(Me.grpScore, "grpScore")
        Me.grpScore.Controls.Add(Me.DataGridView2)
        Me.grpScore.Controls.Add(Me.optShowWins)
        Me.grpScore.Controls.Add(Me.optShowMagic)
        Me.grpScore.Controls.Add(Me.optShowRest)
        Me.grpScore.Controls.Add(Me.chkSchedule)
        Me.grpScore.Controls.Add(Me.MonthCalendar1)
        Me.grpScore.Controls.Add(Me.DataGridView1)
        Me.grpScore.Name = "grpScore"
        Me.grpScore.TabStop = False
        '
        'DataGridView2
        '
        resources.ApplyResources(Me.DataGridView2, "DataGridView2")
        Me.DataGridView2.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize
        Me.DataGridView2.Name = "DataGridView2"
        Me.DataGridView2.RowTemplate.Height = 21
        '
        'optShowWins
        '
        Me.optShowWins.BackColor = System.Drawing.SystemColors.Window
        resources.ApplyResources(Me.optShowWins, "optShowWins")
        Me.optShowWins.Name = "optShowWins"
        Me.optShowWins.TabStop = True
        Me.optShowWins.UseVisualStyleBackColor = False
        '
        'optShowMagic
        '
        Me.optShowMagic.BackColor = System.Drawing.SystemColors.Window
        resources.ApplyResources(Me.optShowMagic, "optShowMagic")
        Me.optShowMagic.Name = "optShowMagic"
        Me.optShowMagic.TabStop = True
        Me.optShowMagic.UseVisualStyleBackColor = False
        '
        'optShowRest
        '
        Me.optShowRest.BackColor = System.Drawing.SystemColors.Window
        resources.ApplyResources(Me.optShowRest, "optShowRest")
        Me.optShowRest.Name = "optShowRest"
        Me.optShowRest.TabStop = True
        Me.optShowRest.UseVisualStyleBackColor = False
        '
        'chkSchedule
        '
        Me.chkSchedule.BackColor = System.Drawing.SystemColors.Window
        resources.ApplyResources(Me.chkSchedule, "chkSchedule")
        Me.chkSchedule.Name = "chkSchedule"
        Me.chkSchedule.UseVisualStyleBackColor = False
        '
        'MonthCalendar1
        '
        resources.ApplyResources(Me.MonthCalendar1, "MonthCalendar1")
        Me.MonthCalendar1.Name = "MonthCalendar1"
        '
        'DataGridView1
        '
        Me.DataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize
        resources.ApplyResources(Me.DataGridView1, "DataGridView1")
        Me.DataGridView1.Name = "DataGridView1"
        Me.DataGridView1.RowTemplate.Height = 21
        '
        'tabLeague
        '
        resources.ApplyResources(Me.tabLeague, "tabLeague")
        Me.tabLeague.Name = "tabLeague"
        Me.tabLeague.SelectedIndex = 0
        '
        'MainView
        '
        resources.ApplyResources(Me, "$this")
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.Controls.Add(Me.grpScore)
        Me.Controls.Add(Me.mnuMain)
        Me.Controls.Add(Me.tabLeague)
        Me.MainMenuStrip = Me.mnuMain
        Me.Name = "MainView"
        Me.mnuMain.ResumeLayout(False)
        Me.mnuMain.PerformLayout()
        Me.grpScore.ResumeLayout(False)
        CType(Me.DataGridView2, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.DataGridView1, System.ComponentModel.ISupportInitialize).EndInit()
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
    Friend WithEvents mnuMagicSep0 As System.Windows.Forms.ToolStripSeparator
    Friend WithEvents mnuMagicEasy As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuMagicSep1 As System.Windows.Forms.ToolStripSeparator
    Friend WithEvents mnuMagicLine As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents grpScore As System.Windows.Forms.GroupBox
    Friend WithEvents tabLeague As System.Windows.Forms.TabControl
    Friend WithEvents MonthCalendar1 As System.Windows.Forms.MonthCalendar
    Friend WithEvents DataGridView1 As System.Windows.Forms.DataGridView
    Friend WithEvents DataGridView2 As System.Windows.Forms.DataGridView
    Friend WithEvents optShowWins As System.Windows.Forms.RadioButton
    Friend WithEvents optShowMagic As System.Windows.Forms.RadioButton
    Friend WithEvents optShowRest As System.Windows.Forms.RadioButton
    Friend WithEvents chkSchedule As System.Windows.Forms.CheckBox

End Class
