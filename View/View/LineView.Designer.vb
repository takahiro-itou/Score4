<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class LineView
    Inherits System.Windows.Forms.Form

    'フォームがコンポーネントの一覧をクリーンアップするために dispose をオーバーライドします。
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

    'Windows フォーム デザイナーで必要です。
    Private components As System.ComponentModel.IContainer

    'メモ: 以下のプロシージャは Windows フォーム デザイナーで必要です。
    'Windows フォーム デザイナーを使用して変更できます。
    'コード エディターを使って変更しないでください。
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(LineView))
        Me.tabLeague = New System.Windows.Forms.TabControl()
        Me.fraLine = New System.Windows.Forms.GroupBox()
        Me.btnExit = New System.Windows.Forms.Button()
        Me.fraShowMode = New System.Windows.Forms.GroupBox()
        Me.optShowPlayoff = New System.Windows.Forms.RadioButton()
        Me.optShowVictory = New System.Windows.Forms.RadioButton()
        Me.fraDate = New System.Windows.Forms.GroupBox()
        Me.lblDate = New System.Windows.Forms.Label()
        Me.MonthCalendar1 = New System.Windows.Forms.MonthCalendar()
        Me.dgvLine = New System.Windows.Forms.DataGridView()
        Me.fraLine.SuspendLayout()
        Me.fraShowMode.SuspendLayout()
        Me.fraDate.SuspendLayout()
        CType(Me.dgvLine, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'tabLeague
        '
        resources.ApplyResources(Me.tabLeague, "tabLeague")
        Me.tabLeague.Name = "tabLeague"
        Me.tabLeague.SelectedIndex = 0
        '
        'fraLine
        '
        resources.ApplyResources(Me.fraLine, "fraLine")
        Me.fraLine.Controls.Add(Me.btnExit)
        Me.fraLine.Controls.Add(Me.fraShowMode)
        Me.fraLine.Controls.Add(Me.fraDate)
        Me.fraLine.Controls.Add(Me.dgvLine)
        Me.fraLine.Name = "fraLine"
        Me.fraLine.TabStop = False
        '
        'btnExit
        '
        resources.ApplyResources(Me.btnExit, "btnExit")
        Me.btnExit.Name = "btnExit"
        Me.btnExit.UseVisualStyleBackColor = True
        '
        'fraShowMode
        '
        resources.ApplyResources(Me.fraShowMode, "fraShowMode")
        Me.fraShowMode.Controls.Add(Me.optShowPlayoff)
        Me.fraShowMode.Controls.Add(Me.optShowVictory)
        Me.fraShowMode.Name = "fraShowMode"
        Me.fraShowMode.TabStop = False
        '
        'optShowPlayoff
        '
        Me.optShowPlayoff.BackColor = System.Drawing.Color.White
        resources.ApplyResources(Me.optShowPlayoff, "optShowPlayoff")
        Me.optShowPlayoff.Name = "optShowPlayoff"
        Me.optShowPlayoff.TabStop = True
        Me.optShowPlayoff.UseVisualStyleBackColor = False
        '
        'optShowVictory
        '
        Me.optShowVictory.BackColor = System.Drawing.Color.White
        resources.ApplyResources(Me.optShowVictory, "optShowVictory")
        Me.optShowVictory.Name = "optShowVictory"
        Me.optShowVictory.TabStop = True
        Me.optShowVictory.UseVisualStyleBackColor = False
        '
        'fraDate
        '
        resources.ApplyResources(Me.fraDate, "fraDate")
        Me.fraDate.Controls.Add(Me.lblDate)
        Me.fraDate.Controls.Add(Me.MonthCalendar1)
        Me.fraDate.Name = "fraDate"
        Me.fraDate.TabStop = False
        '
        'lblDate
        '
        resources.ApplyResources(Me.lblDate, "lblDate")
        Me.lblDate.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.lblDate.Name = "lblDate"
        '
        'MonthCalendar1
        '
        resources.ApplyResources(Me.MonthCalendar1, "MonthCalendar1")
        Me.MonthCalendar1.Name = "MonthCalendar1"
        '
        'dgvLine
        '
        Me.dgvLine.AllowUserToAddRows = False
        Me.dgvLine.AllowUserToDeleteRows = False
        resources.ApplyResources(Me.dgvLine, "dgvLine")
        Me.dgvLine.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize
        Me.dgvLine.Name = "dgvLine"
        Me.dgvLine.ReadOnly = True
        Me.dgvLine.RowTemplate.Height = 25
        '
        'LineView
        '
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None
        Me.CancelButton = Me.btnExit
        resources.ApplyResources(Me, "$this")
        Me.Controls.Add(Me.fraLine)
        Me.Controls.Add(Me.tabLeague)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "LineView"
        Me.fraLine.ResumeLayout(False)
        Me.fraShowMode.ResumeLayout(False)
        Me.fraDate.ResumeLayout(False)
        CType(Me.dgvLine, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub

    Friend WithEvents tabLeague As TabControl
    Friend WithEvents fraLine As GroupBox
    Friend WithEvents dgvLine As DataGridView
    Friend WithEvents fraDate As GroupBox
    Friend WithEvents MonthCalendar1 As MonthCalendar
    Friend WithEvents lblDate As Label
    Friend WithEvents fraShowMode As GroupBox
    Friend WithEvents btnExit As Button
    Friend WithEvents optShowPlayoff As RadioButton
    Friend WithEvents optShowVictory As RadioButton
End Class
