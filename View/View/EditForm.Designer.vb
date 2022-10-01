<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class EditForm
    Inherits System.Windows.Forms.Form

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

    Private components As System.ComponentModel.IContainer

    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Dim resources As System.ComponentModel.ComponentResourceManager = _
            New System.ComponentModel.ComponentResourceManager(GetType(EditForm))

        Me.btnOK = New System.Windows.Forms.Button()
        Me.btnApply = New System.Windows.Forms.Button()
        Me.btnCancel = New System.Windows.Forms.Button()
        Me.dgvRecord = New System.Windows.Forms.DataGridView()
        Me.fraInput = New System.Windows.Forms.GroupBox()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.cmbTeamHome = New System.Windows.Forms.ComboBox()
        Me.updScoreHome = New System.Windows.Forms.NumericUpDown()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.cmbTeamAway = New System.Windows.Forms.ComboBox()
        Me.updScoreAway = New System.Windows.Forms.NumericUpDown()
        Me.cmbFlags = New System.Windows.Forms.ComboBox()
        Me.btnEdit = New System.Windows.Forms.Button()
        Me.btnDelete = New System.Windows.Forms.Button()
        Me.fraView = New System.Windows.Forms.GroupBox()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.mnvEdit = New System.Windows.Forms.MonthCalendar()
        Me.lblDate = New System.Windows.Forms.Label()

        CType(Me.dgvRecord, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.fraInput.SuspendLayout()
        CType(Me.updScoreHome, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.updScoreAway, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.fraView.SuspendLayout()
        Me.SuspendLayout()

        '
        ' btnOK
        '
        resources.ApplyResources(Me.btnOK, "btnOK")
        Me.btnOK.Name = "btnOK"
        Me.btnOK.UseVisualStyleBackColor = True
        '
        ' btnApply
        '
        resources.ApplyResources(Me.btnApply, "btnApply")
        Me.btnApply.Name = "btnApply"
        Me.btnApply.UseVisualStyleBackColor = True
        '
        ' btnCancel
        '
        resources.ApplyResources(Me.btnCancel, "btnCancel")
        Me.btnCancel.Name = "btnCancel"
        Me.btnCancel.UseVisualStyleBackColor = True
        '
        ' dgvRecord
        '
        resources.ApplyResources(Me.dgvRecord, "dgvRecord")
        Me.dgvRecord.AllowUserToAddRows = False
        Me.dgvRecord.AllowUserToDeleteRows = False
        Me.dgvRecord.AllowUserToResizeColumns = True
        Me.dgvRecord.AllowUserToResizeRows = False
        Me.dgvRecord.ColumnHeadersHeightSizeMode = _
                System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize
        Me.dgvRecord.MultiSelect = False
        Me.dgvRecord.Name = "dgvRecord"
        Me.dgvRecord.ReadOnly = True
        Me.dgvRecord.RowHeadersVisible = False
        Me.dgvRecord.RowTemplate.Height = 21
        Me.dgvRecord.SelectionMode = DataGridViewSelectionMode.FullRowSelect

        '
        ' fraInput
        '
        resources.ApplyResources(Me.fraInput, "fraInput")
        Me.fraInput.Controls.Add(Me.Label1)
        Me.fraInput.Controls.Add(Me.Label2)
        Me.fraInput.Controls.Add(Me.Label3)
        Me.fraInput.Controls.Add(Me.cmbTeamHome)
        Me.fraInput.Controls.Add(Me.updScoreHome)
        Me.fraInput.Controls.Add(Me.Label4)
        Me.fraInput.Controls.Add(Me.cmbTeamAway)
        Me.fraInput.Controls.Add(Me.updScoreAway)
        Me.fraInput.Controls.Add(Me.cmbFlags)
        Me.fraInput.Controls.Add(Me.btnEdit)
        Me.fraInput.Controls.Add(Me.btnDelete)
        Me.fraInput.Name = "fraInput"
        Me.fraInput.TabStop = False
        '
        ' Label1
        '
        resources.ApplyResources(Me.Label1, "Label1")
        Me.Label1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.Label1.Name = "Label1"
        '
        ' Label2
        '
        resources.ApplyResources(Me.Label2, "Label2")
        Me.Label2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.Label2.Name = "Label2"
        '
        ' Label3
        '
        resources.ApplyResources(Me.Label3, "Label3")
        Me.Label3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.Label3.Name = "Label3"
        '
        ' cmbTeamHome
        '
        resources.ApplyResources(Me.cmbTeamHome, "cmbTeamHome")
        Me.cmbTeamHome.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cmbTeamHome.FormattingEnabled = True
        Me.cmbTeamHome.Name = "cmbTeamHome"
        '
        ' updScoreHome
        '
        resources.ApplyResources(Me.updScoreHome, "updScoreHome")
        Me.updScoreHome.Maximum = New Decimal(New Integer() {999, 0, 0, 0})
        Me.updScoreHome.Name = "updScoreHome"
        '
        'Label4
        '
        resources.ApplyResources(Me.Label4, "Label4")
        Me.Label4.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.Label4.Name = "Label4"
        '
        ' cmbTeamAway
        '
        resources.ApplyResources(Me.cmbTeamAway, "cmbTeamAway")
        Me.cmbTeamAway.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cmbTeamAway.FormattingEnabled = True
        Me.cmbTeamAway.Name = "cmbTeamAway"
        '
        ' updScoreAway
        '
        resources.ApplyResources(Me.updScoreAway, "updScoreAway")
        Me.updScoreAway.Maximum = New Decimal(New Integer() {999, 0, 0, 0})
        Me.updScoreAway.Name = "updScoreAway"
        '
        ' cmbFlags
        '
        resources.ApplyResources(Me.cmbFlags, "cmbFlags")
        Me.cmbFlags.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cmbFlags.FormattingEnabled = True
        Me.cmbFlags.Name = "cmbFlags"
        '
        ' btnEdit
        '
        resources.ApplyResources(Me.btnEdit, "btnEdit")
        Me.btnEdit.Name = "btnEdit"
        Me.btnEdit.UseVisualStyleBackColor = True
        '
        ' btnDelete
        '
        resources.ApplyResources(Me.btnDelete, "btnDelete")
        Me.btnDelete.Name = "btnDelete"
        Me.btnDelete.UseVisualStyleBackColor = True

        '
        ' fraView
        '
        resources.ApplyResources(Me.fraView, "fraView")
        Me.fraView.Controls.Add(Me.Label5)
        Me.fraView.Controls.Add(Me.mnvEdit)
        Me.fraView.Controls.Add(Me.lblDate)
        Me.fraView.Name = "fraView"
        Me.fraView.TabStop = False
        '
        ' Label5
        '
        resources.ApplyResources(Me.Label5, "Label5")
        Me.Label5.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.Label5.Name = "Label5"
        '
        ' mnvEdit
        '
        resources.ApplyResources(Me.mnvEdit, "mnvEdit")
        Me.mnvEdit.MaxSelectionCount = 1
        Me.mnvEdit.Name = "mnvEdit"
        '
        ' lblDate
        '
        resources.ApplyResources(Me.lblDate, "lblDate")
        Me.lblDate.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.lblDate.Name = "lblDate"

        '
        ' EditForm
        '
        resources.ApplyResources(Me, "$this")
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None
        Me.CancelButton = Me.btnCancel

        Me.Controls.Add(Me.btnOK)
        Me.Controls.Add(Me.btnApply)
        Me.Controls.Add(Me.btnCancel)
        Me.Controls.Add(Me.dgvRecord)
        Me.Controls.Add(Me.fraInput)
        Me.Controls.Add(Me.fraView)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
        Me.Name = "EditForm"

        CType(Me.dgvRecord, System.ComponentModel.ISupportInitialize).EndInit()
        Me.fraInput.ResumeLayout(False)
        CType(Me.updScoreHome, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.updScoreAway, System.ComponentModel.ISupportInitialize).EndInit()
        Me.fraView.ResumeLayout(False)
        Me.ResumeLayout(False)
    End Sub

    Friend WithEvents btnOK As Button
    Friend WithEvents btnApply As Button
    Friend WithEvents btnCancel As Button
    Friend WithEvents dgvRecord As DataGridView
    Friend WithEvents fraInput As GroupBox
    Friend WithEvents Label1 As Label
    Friend WithEvents Label2 As Label
    Friend WithEvents Label3 As Label
    Friend WithEvents cmbTeamHome As ComboBox
    Friend WithEvents updScoreHome As NumericUpDown
    Friend WithEvents Label4 As Label
    Friend WithEvents cmbTeamAway As ComboBox
    Friend WithEvents updScoreAway As NumericUpDown
    Friend WithEvents cmbFlags As ComboBox
    Friend WithEvents btnEdit As Button
    Friend WithEvents btnDelete As Button
    Friend WithEvents fraView As GroupBox
    Friend WithEvents Label5 As Label
    Friend WithEvents mnvEdit As MonthCalendar
    Friend WithEvents lblDate As Label

End Class
