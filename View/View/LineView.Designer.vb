<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class LineView
    Inherits System.Windows.Forms.Form

    ' フォームがコンポーネントの一覧をクリーンアップするために dispose をオーバーライドします。
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

    ' Windows フォーム デザイナーで必要です。
    Private components As System.ComponentModel.IContainer

    ' メモ: 以下のプロシージャは Windows  フォームデザイナーで必要です。
    ' Windows フォームデザイナーを使用して変更できます。
    ' コードエディターを使って変更しないでください。
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Dim resources As System.ComponentModel.ComponentResourceManager = _
            New System.ComponentModel.ComponentResourceManager(GetType(LineView))

        Me.tabLeague = New System.Windows.Forms.TabControl()
        Me.fraLine = New System.Windows.Forms.GroupBox()
        Me.dgvLine = New System.Windows.Forms.DataGridView()
        Me.fraDate = New System.Windows.Forms.GroupBox()
        Me.mncDate = New System.Windows.Forms.MonthCalendar()
        Me.lblDate = New System.Windows.Forms.Label()
        Me.fraShowMode = New System.Windows.Forms.GroupBox()
        Me.optShowPlayoff = New System.Windows.Forms.RadioButton()
        Me.optShowVictory = New System.Windows.Forms.RadioButton()
        Me.btnExit = New System.Windows.Forms.Button()

        Me.fraLine.SuspendLayout()
        Me.fraShowMode.SuspendLayout()
        Me.fraDate.SuspendLayout()
        CType(Me.dgvLine, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()

        '
        ' tabLeague
        '
        resources.ApplyResources(Me.tabLeague, "tabLeague")
        Me.tabLeague.Name = "tabLeague"
        Me.tabLeague.SelectedIndex = 0

        '
        ' fraLine
        '
        resources.ApplyResources(Me.fraLine, "fraLine")
        Me.fraLine.Controls.Add(Me.btnExit)
        Me.fraLine.Controls.Add(Me.fraShowMode)
        Me.fraLine.Controls.Add(Me.fraDate)
        Me.fraLine.Controls.Add(Me.dgvLine)
        Me.fraLine.Name = "fraLine"
        Me.fraLine.TabStop = False

        '
        ' dgvLine
        '
        resources.ApplyResources(Me.dgvLine, "dgvLine")
        Me.dgvLine.AllowUserToAddRows = False
        Me.dgvLine.AllowUserToDeleteRows = False
        Me.dgvLine.ColumnHeadersHeightSizeMode = _
            System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize
        Me.dgvLine.Name = "dgvLine"
        Me.dgvLine.ReadOnly = True
        Me.dgvLine.RowTemplate.Height = 25


        '
        ' fraShowMode
        '
        resources.ApplyResources(Me.fraShowMode, "fraShowMode")
        Me.fraShowMode.Controls.Add(Me.optShowPlayoff)
        Me.fraShowMode.Controls.Add(Me.optShowVictory)
        Me.fraShowMode.Name = "fraShowMode"
        Me.fraShowMode.TabStop = False
        Me.fraShowMode.Visible = False

        '
        ' optShowPlayoff
        '
        resources.ApplyResources(Me.optShowPlayoff, "optShowPlayoff")
        Me.optShowPlayoff.BackColor = System.Drawing.Color.White
        Me.optShowPlayoff.Name = "optShowPlayoff"
        Me.optShowPlayoff.TabStop = True
        Me.optShowPlayoff.UseVisualStyleBackColor = False

        '
        'optShowVictory
        '
        resources.ApplyResources(Me.optShowVictory, "optShowVictory")
        Me.optShowVictory.BackColor = System.Drawing.Color.White
        Me.optShowVictory.Name = "optShowVictory"
        Me.optShowVictory.TabStop = True
        Me.optShowVictory.UseVisualStyleBackColor = False

        '
        ' fraDate
        '
        resources.ApplyResources(Me.fraDate, "fraDate")
        Me.fraDate.Controls.Add(Me.lblDate)
        Me.fraDate.Controls.Add(Me.mncDate)
        Me.fraDate.Name = "fraDate"
        Me.fraDate.TabStop = False

        '
        ' mncDate
        '
        resources.ApplyResources(Me.mncDate, "mncDate")
        Me.mncDate.Name = "mncDate"

        '
        ' lblDate
        '
        resources.ApplyResources(Me.lblDate, "lblDate")
        Me.lblDate.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.lblDate.Name = "lblDate"

        '
        ' btnExit
        '
        resources.ApplyResources(Me.btnExit, "btnExit")
        Me.btnExit.Name = "btnExit"
        Me.btnExit.UseVisualStyleBackColor = True

        '
        ' LineView
        '
        resources.ApplyResources(Me, "$this")
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None
        Me.CancelButton = Me.btnExit

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
    Friend WithEvents mncDate As MonthCalendar
    Friend WithEvents lblDate As Label
    Friend WithEvents fraShowMode As GroupBox
    Friend WithEvents optShowPlayoff As RadioButton
    Friend WithEvents optShowVictory As RadioButton
    Friend WithEvents btnExit As Button

End Class
