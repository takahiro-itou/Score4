<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()>
Partial Class MainView
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()>
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
    <System.Diagnostics.DebuggerStepThrough()>
    Private Sub InitializeComponent()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(MainView))
        Dim DataGridViewCellStyle1 As System.Windows.Forms.DataGridViewCellStyle = New System.Windows.Forms.DataGridViewCellStyle()
        Dim DataGridViewCellStyle2 As System.Windows.Forms.DataGridViewCellStyle = New System.Windows.Forms.DataGridViewCellStyle()
        Dim DataGridViewCellStyle3 As System.Windows.Forms.DataGridViewCellStyle = New System.Windows.Forms.DataGridViewCellStyle()
        Dim DataGridViewCellStyle4 As System.Windows.Forms.DataGridViewCellStyle = New System.Windows.Forms.DataGridViewCellStyle()
        Dim DataGridViewCellStyle5 As System.Windows.Forms.DataGridViewCellStyle = New System.Windows.Forms.DataGridViewCellStyle()
        Dim DataGridViewCellStyle6 As System.Windows.Forms.DataGridViewCellStyle = New System.Windows.Forms.DataGridViewCellStyle()
        Dim DataGridViewCellStyle7 As System.Windows.Forms.DataGridViewCellStyle = New System.Windows.Forms.DataGridViewCellStyle()
        Dim DataGridViewCellStyle8 As System.Windows.Forms.DataGridViewCellStyle = New System.Windows.Forms.DataGridViewCellStyle()
        Dim DataGridViewCellStyle9 As System.Windows.Forms.DataGridViewCellStyle = New System.Windows.Forms.DataGridViewCellStyle()

        Me.mnuMain = New System.Windows.Forms.MenuStrip()
        Me.mnuFile = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuFileNew = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuFileOpen = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuFileSep0 = New System.Windows.Forms.ToolStripSeparator()
        Me.mnuFileSave = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuFileSaveAs = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuFileSep1 = New System.Windows.Forms.ToolStripSeparator()
        Me.mnuFileOpenText = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuFileExportText = New System.Windows.Forms.ToolStripMenuItem()
        Me.mnuFileSep2 = New System.Windows.Forms.ToolStripSeparator()
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
        Me.tabLeague = New System.Windows.Forms.TabControl()
        Me.fraScore = New System.Windows.Forms.GroupBox()
        Me.fraDate = New System.Windows.Forms.GroupBox()
        Me.mnvDate = New System.Windows.Forms.MonthCalendar()
        Me.lblDate = New System.Windows.Forms.Label()
        Me.dgvScore = New System.Windows.Forms.DataGridView()
        Me.chkSchedule = New System.Windows.Forms.CheckBox()
        Me.optShowRest = New System.Windows.Forms.RadioButton()
        Me.optShowMagic = New System.Windows.Forms.RadioButton()
        Me.optShowWins = New System.Windows.Forms.RadioButton()
        Me.dgvExtra = New System.Windows.Forms.DataGridView()

        Me.colTeam = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.colTotal = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.colWon = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.colLost = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.colDraw = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.colDiff = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.colPercent = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.colMagic = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.colRank = New System.Windows.Forms.DataGridViewTextBoxColumn()

        Me.mnuMain.SuspendLayout()
        Me.fraScore.SuspendLayout()
        Me.fraDate.SuspendLayout()
        CType(Me.dgvScore, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.dgvExtra, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()

        '
        ' mnuMain
        '
        resources.ApplyResources(Me.mnuMain, "mnuMain")
        Me.mnuMain.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.mnuFile, Me.mnuScore, Me.mnuMagic, Me.mnuOptions})
        Me.mnuMain.Name = "mnuMain"
        '
        ' mnuFile
        '
        resources.ApplyResources(Me.mnuFile, "mnuFile")
        Me.mnuFile.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.mnuFileNew, Me.mnuFileOpen, Me.mnuFileSep0, Me.mnuFileSave, Me.mnuFileSaveAs, Me.mnuFileSep1, Me.mnuFileOpenText, Me.mnuFileExportText, Me.mnuFileSep2, Me.mnuFileExit})
        Me.mnuFile.Name = "mnuFile"
        '
        ' mnuFileNew
        '
        Me.mnuFileNew.Name = "mnuFileNew"
        resources.ApplyResources(Me.mnuFileNew, "mnuFileNew")
        '
        ' mnuFileOpen
        '
        Me.mnuFileOpen.Name = "mnuFileOpen"
        resources.ApplyResources(Me.mnuFileOpen, "mnuFileOpen")
        '
        ' mnuFileSep0
        '
        Me.mnuFileSep0.Name = "mnuFileSep0"
        resources.ApplyResources(Me.mnuFileSep0, "mnuFileSep0")
        '
        ' mnuFileSave
        '
        Me.mnuFileSave.Name = "mnuFileSave"
        resources.ApplyResources(Me.mnuFileSave, "mnuFileSave")
        '
        ' mnuFileSaveAs
        '
        Me.mnuFileSaveAs.Name = "mnuFileSaveAs"
        resources.ApplyResources(Me.mnuFileSaveAs, "mnuFileSaveAs")
        '
        ' mnuFileSep1
        '
        Me.mnuFileSep1.Name = "mnuFileSep1"
        resources.ApplyResources(Me.mnuFileSep1, "mnuFileSep1")
        '
        ' mnuFileExit
        '
        Me.mnuFileExit.Name = "mnuFileExit"
        resources.ApplyResources(Me.mnuFileExit, "mnuFileExit")
        '
        ' mnuScore
        '
        Me.mnuScore.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.mnuScoreEdit, Me.mnuScoreDetail, Me.mnuScoreImport, Me.mnuScoreSep0, Me.mnuScoreSettings, Me.mnuScoreSep1, Me.mnuScoreRefresh})
        Me.mnuScore.Name = "mnuScore"
        resources.ApplyResources(Me.mnuScore, "mnuScore")
        '
        ' mnuScoreEdit
        '
        Me.mnuScoreEdit.Name = "mnuScoreEdit"
        resources.ApplyResources(Me.mnuScoreEdit, "mnuScoreEdit")
        '
        ' mnuScoreDetail
        '
        Me.mnuScoreDetail.Name = "mnuScoreDetail"
        resources.ApplyResources(Me.mnuScoreDetail, "mnuScoreDetail")
        '
        ' mnuScoreImport
        '
        Me.mnuScoreImport.Name = "mnuScoreImport"
        resources.ApplyResources(Me.mnuScoreImport, "mnuScoreImport")
        '
        ' mnuScoreSep0
        '
        Me.mnuScoreSep0.Name = "mnuScoreSep0"
        resources.ApplyResources(Me.mnuScoreSep0, "mnuScoreSep0")
        '
        ' mnuScoreSettings
        '
        Me.mnuScoreSettings.Name = "mnuScoreSettings"
        resources.ApplyResources(Me.mnuScoreSettings, "mnuScoreSettings")
        '
        ' mnuScoreSep1
        '
        Me.mnuScoreSep1.Name = "mnuScoreSep1"
        resources.ApplyResources(Me.mnuScoreSep1, "mnuScoreSep1")
        '
        ' mnuScoreRefresh
        '
        Me.mnuScoreRefresh.Name = "mnuScoreRefresh"
        resources.ApplyResources(Me.mnuScoreRefresh, "mnuScoreRefresh")
        '
        ' mnuMagic
        '
        Me.mnuMagic.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.mnuMagicVictory, Me.mnuMagicPlayoff, Me.mnuMagicSep0, Me.mnuMagicEasy, Me.mnuMagicSep1, Me.mnuMagicLine})
        Me.mnuMagic.Name = "mnuMagic"
        resources.ApplyResources(Me.mnuMagic, "mnuMagic")
        '
        ' mnuMagicVictory
        '
        Me.mnuMagicVictory.Name = "mnuMagicVictory"
        resources.ApplyResources(Me.mnuMagicVictory, "mnuMagicVictory")
        '
        ' mnuMagicPlayoff
        '
        Me.mnuMagicPlayoff.Name = "mnuMagicPlayoff"
        resources.ApplyResources(Me.mnuMagicPlayoff, "mnuMagicPlayoff")
        '
        ' mnuMagicSep0
        '
        Me.mnuMagicSep0.Name = "mnuMagicSep0"
        resources.ApplyResources(Me.mnuMagicSep0, "mnuMagicSep0")
        '
        ' mnuMagicEasy
        '
        Me.mnuMagicEasy.Name = "mnuMagicEasy"
        resources.ApplyResources(Me.mnuMagicEasy, "mnuMagicEasy")
        '
        ' mnuMagicSep1
        '
        Me.mnuMagicSep1.Name = "mnuMagicSep1"
        resources.ApplyResources(Me.mnuMagicSep1, "mnuMagicSep1")
        '
        ' mnuMagicLine
        '
        Me.mnuMagicLine.Name = "mnuMagicLine"
        resources.ApplyResources(Me.mnuMagicLine, "mnuMagicLine")
        '
        ' mnuOptions
        '
        Me.mnuOptions.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.mnuOptionsFont})
        Me.mnuOptions.Name = "mnuOptions"
        resources.ApplyResources(Me.mnuOptions, "mnuOptions")
        '
        ' mnuOptionsFont
        '
        Me.mnuOptionsFont.Name = "mnuOptionsFont"
        resources.ApplyResources(Me.mnuOptionsFont, "mnuOptionsFont")

        '
        ' dlgOpen
        '
        Me.dlgOpen.FileName = "OpenFileDialog1"


        '
        'tabLeague
        '
        resources.ApplyResources(Me.tabLeague, "tabLeague")
        Me.tabLeague.Name = "tabLeague"
        Me.tabLeague.SelectedIndex = 0

        '
        ' fraScore
        '
        resources.ApplyResources(Me.fraScore, "fraScore")
        Me.fraScore.Controls.Add(Me.fraDate)
        Me.fraDate.Controls.Add(Me.mnvDate)
        Me.fraDate.Controls.Add(Me.lblDate)
        Me.fraScore.Controls.Add(Me.dgvScore)
        Me.fraScore.Controls.Add(Me.chkSchedule)
        Me.fraScore.Controls.Add(Me.optShowRest)
        Me.fraScore.Controls.Add(Me.optShowMagic)
        Me.fraScore.Controls.Add(Me.optShowWins)
        Me.fraScore.Controls.Add(Me.dgvExtra)

        Me.fraScore.Name = "fraScore"
        Me.fraScore.TabStop = False

        '
        ' dgvScore
        '
        Me.dgvScore.AllowUserToAddRows = False
        Me.dgvScore.AllowUserToDeleteRows = False
        Me.dgvScore.AllowUserToResizeColumns = True
        Me.dgvScore.AllowUserToResizeRows = False
        Me.dgvScore.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize
        Me.dgvScore.Columns.AddRange(New System.Windows.Forms.DataGridViewColumn() {Me.colTeam, Me.colTotal, Me.colWon, Me.colLost, Me.colDraw, Me.colDiff, Me.colPercent, Me.colMagic, Me.colRank})
        resources.ApplyResources(Me.dgvScore, "dgvScore")
        Me.dgvScore.MultiSelect = False
        Me.dgvScore.Name = "dgvScore"
        Me.dgvScore.ReadOnly = True
        Me.dgvScore.RowHeadersVisible = False
        Me.dgvScore.RowTemplate.Height = 21

        '
        ' fraDate
        '
        Me.fraDate.Controls.Add(Me.mnvDate)
        Me.fraDate.Controls.Add(Me.lblDate)
        resources.ApplyResources(Me.fraDate, "fraDate")
        Me.fraDate.Name = "fraScore"
        Me.fraDate.TabStop = False

        '
        ' mnvDate
        '
        resources.ApplyResources(Me.mnvDate, "mnvDate")
        Me.mnvDate.MaxSelectionCount = 1
        Me.mnvDate.Name = "mnvDate"

        '
        ' lblDate
        '
        resources.ApplyResources(Me.lblDate, "lblDate")
        Me.lblDate.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.lblDate.Name = "lblDate"

        '
        ' dgvExtra
        '
        Me.dgvExtra.AllowUserToAddRows = False
        Me.dgvExtra.AllowUserToDeleteRows = False
        Me.dgvExtra.AllowUserToResizeColumns = True
        Me.dgvExtra.AllowUserToResizeRows = False
        resources.ApplyResources(Me.dgvExtra, "dgvExtra")
        Me.dgvExtra.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize
        Me.dgvExtra.MultiSelect = False
        Me.dgvExtra.Name = "dgvExtra"
        Me.dgvExtra.ReadOnly = True
        Me.dgvExtra.RowHeadersVisible = False
        Me.dgvExtra.RowTemplate.Height = 21

        '
        'chkSchedule
        '
        Me.chkSchedule.BackColor = System.Drawing.SystemColors.Window
        resources.ApplyResources(Me.chkSchedule, "chkSchedule")
        Me.chkSchedule.Name = "chkSchedule"
        Me.chkSchedule.UseVisualStyleBackColor = False

        '
        ' optShowWins
        '
        Me.optShowWins.BackColor = System.Drawing.SystemColors.Window
        resources.ApplyResources(Me.optShowWins, "optShowWins")
        Me.optShowWins.Name = "optShowWins"
        Me.optShowWins.TabStop = True
        Me.optShowWins.UseVisualStyleBackColor = False

        '
        ' optShowMagic
        '
        Me.optShowMagic.BackColor = System.Drawing.SystemColors.Window
        resources.ApplyResources(Me.optShowMagic, "optShowMagic")
        Me.optShowMagic.Name = "optShowMagic"
        Me.optShowMagic.TabStop = True
        Me.optShowMagic.UseVisualStyleBackColor = False

        '
        ' optShowRest
        '
        Me.optShowRest.BackColor = System.Drawing.SystemColors.Window
        resources.ApplyResources(Me.optShowRest, "optShowRest")
        Me.optShowRest.Name = "optShowRest"
        Me.optShowRest.TabStop = True
        Me.optShowRest.UseVisualStyleBackColor = False

        '
        ' colTeam
        '
        DataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft
        Me.colTeam.DefaultCellStyle = DataGridViewCellStyle1
        Me.colTeam.Frozen = True
        resources.ApplyResources(Me.colTeam, "colTeam")
        Me.colTeam.Name = "colTeam"
        Me.colTeam.ReadOnly = True
        Me.colTeam.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable
        '
        ' colTotal
        '
        DataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleRight
        Me.colTotal.DefaultCellStyle = DataGridViewCellStyle2
        resources.ApplyResources(Me.colTotal, "colTotal")
        Me.colTotal.Name = "colTotal"
        Me.colTotal.ReadOnly = True
        Me.colTotal.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable
        '
        ' colWon
        '
        DataGridViewCellStyle3.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleRight
        Me.colWon.DefaultCellStyle = DataGridViewCellStyle3
        resources.ApplyResources(Me.colWon, "colWon")
        Me.colWon.Name = "colWon"
        Me.colWon.ReadOnly = True
        Me.colWon.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable
        '
        ' colLost
        '
        DataGridViewCellStyle4.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleRight
        Me.colLost.DefaultCellStyle = DataGridViewCellStyle4
        resources.ApplyResources(Me.colLost, "colLost")
        Me.colLost.Name = "colLost"
        Me.colLost.ReadOnly = True
        Me.colLost.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable
        '
        ' colDraw
        '
        DataGridViewCellStyle5.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleRight
        Me.colDraw.DefaultCellStyle = DataGridViewCellStyle5
        resources.ApplyResources(Me.colDraw, "colDraw")
        Me.colDraw.Name = "colDraw"
        Me.colDraw.ReadOnly = True
        Me.colDraw.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable
        '
        ' colDiff
        '
        DataGridViewCellStyle6.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleRight
        Me.colDiff.DefaultCellStyle = DataGridViewCellStyle6
        resources.ApplyResources(Me.colDiff, "colDiff")
        Me.colDiff.Name = "colDiff"
        Me.colDiff.ReadOnly = True
        Me.colDiff.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable
        '
        ' colPercent
        '
        DataGridViewCellStyle7.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleRight
        Me.colPercent.DefaultCellStyle = DataGridViewCellStyle7
        resources.ApplyResources(Me.colPercent, "colPercent")
        Me.colPercent.Name = "colPercent"
        Me.colPercent.ReadOnly = True
        Me.colPercent.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable
        '
        ' colMagic
        '
        DataGridViewCellStyle8.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleRight
        Me.colMagic.DefaultCellStyle = DataGridViewCellStyle8
        resources.ApplyResources(Me.colMagic, "colMagic")
        Me.colMagic.Name = "colMagic"
        Me.colMagic.ReadOnly = True
        Me.colMagic.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable
        '
        ' colRank
        '
        DataGridViewCellStyle9.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleRight
        Me.colRank.DefaultCellStyle = DataGridViewCellStyle9
        resources.ApplyResources(Me.colRank, "colRank")
        Me.colRank.Name = "colRank"
        Me.colRank.ReadOnly = True
        Me.colRank.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable

        '
        'MainView
        '
        resources.ApplyResources(Me, "$this")
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.Controls.Add(Me.fraScore)
        Me.Controls.Add(Me.mnuMain)
        Me.Controls.Add(Me.tabLeague)
        Me.MainMenuStrip = Me.mnuMain
        Me.Name = "MainView"
        Me.mnuMain.ResumeLayout(False)
        Me.mnuMain.PerformLayout()
        Me.fraScore.ResumeLayout(False)
        CType(Me.dgvExtra, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.dgvScore, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents mnuMain As System.Windows.Forms.MenuStrip
    Friend WithEvents mnuFile As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuFileNew As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuFileOpen As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuFileSep0 As System.Windows.Forms.ToolStripSeparator
    Friend WithEvents mnuFileSave As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuFileSaveAs As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuFileSep1 As System.Windows.Forms.ToolStripSeparator
    Friend WithEvents mnuFileExit As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents mnuFileOpenText As ToolStripMenuItem
    Friend WithEvents mnuFileExportText As ToolStripMenuItem
    Friend WithEvents mnuFileSep2 As ToolStripSeparator
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

    Friend WithEvents dlgOpen As System.Windows.Forms.OpenFileDialog
    Friend WithEvents dlgSave As System.Windows.Forms.SaveFileDialog
    Friend WithEvents dlgFont As System.Windows.Forms.FontDialog

    Friend WithEvents tabLeague As System.Windows.Forms.TabControl
    Friend WithEvents fraScore As System.Windows.Forms.GroupBox
    Friend WithEvents dgvScore As System.Windows.Forms.DataGridView
    Friend WithEvents fraDate As System.Windows.Forms.GroupBox
    Friend WithEvents mnvDate As System.Windows.Forms.MonthCalendar
    Friend WithEvents lblDate As System.Windows.Forms.Label
    Friend WithEvents chkSchedule As System.Windows.Forms.CheckBox
    Friend WithEvents optShowRest As System.Windows.Forms.RadioButton
    Friend WithEvents optShowMagic As System.Windows.Forms.RadioButton
    Friend WithEvents optShowWins As System.Windows.Forms.RadioButton
    Friend WithEvents dgvExtra As System.Windows.Forms.DataGridView

    Friend WithEvents colTeam As System.Windows.Forms.DataGridViewTextBoxColumn
    Friend WithEvents colTotal As System.Windows.Forms.DataGridViewTextBoxColumn
    Friend WithEvents colWon As System.Windows.Forms.DataGridViewTextBoxColumn
    Friend WithEvents colLost As System.Windows.Forms.DataGridViewTextBoxColumn
    Friend WithEvents colDraw As System.Windows.Forms.DataGridViewTextBoxColumn
    Friend WithEvents colDiff As System.Windows.Forms.DataGridViewTextBoxColumn
    Friend WithEvents colPercent As System.Windows.Forms.DataGridViewTextBoxColumn
    Friend WithEvents colMagic As System.Windows.Forms.DataGridViewTextBoxColumn
    Friend WithEvents colRank As System.Windows.Forms.DataGridViewTextBoxColumn

End Class
