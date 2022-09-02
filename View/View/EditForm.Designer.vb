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
        Me.cmbTeamVisitor = New System.Windows.Forms.ComboBox()
        Me.updScoreVisitor = New System.Windows.Forms.NumericUpDown()
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
        CType(Me.updScoreVisitor, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.fraView.SuspendLayout()
        Me.SuspendLayout()

        '
        ' btnOK
        '
        resources.ApplyResources(Me.btnOK, "btnOK")
        With Me.btnOK
            .Name = "btnOK"
            .UseVisualStyleBackColor = True
        End With
        '
        ' btnApply
        '
        resources.ApplyResources(Me.btnApply, "btnApply")
        With Me.btnApply
            .Name = "btnApply"
            .UseVisualStyleBackColor = True
        End With
        '
        ' btnCancel
        '
        resources.ApplyResources(Me.btnCancel, "btnCancel")
        With Me.btnCancel
            .Name = "btnCancel"
            .UseVisualStyleBackColor = True
        End With
        '
        ' dgvRecord
        '
        resources.ApplyResources(Me.dgvRecord, "dgvRecord")
        With Me.dgvRecord
            .ColumnHeadersHeightSizeMode = _
                System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize
            .Name = "dgvRecord"
            .RowTemplate.Height = 25
        End With

        '
        ' fraInput
        '
        resources.ApplyResources(Me.fraInput, "fraInput")
        With Me.fraInput
            With .Controls
                .Add(Me.Label1)
                .Add(Me.Label2)
                .Add(Me.Label3)
                .Add(Me.cmbTeamHome)
                .Add(Me.updScoreHome)
                .Add(Me.Label4)
                .Add(Me.cmbTeamVisitor)
                .Add(Me.updScoreVisitor)
                .Add(Me.cmbFlags)
                .Add(Me.btnEdit)
                .Add(Me.btnDelete)
            End With
            .Name = "fraInput"
            .TabStop = False
        End With
        '
        ' Label1
        '
        resources.ApplyResources(Me.Label1, "Label1")
        With Me.Label1
            .BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
            .Name = "Label1"
        End With
        '
        ' Label2
        '
        resources.ApplyResources(Me.Label2, "Label2")
        With Me.Label2
            .BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
            .Name = "Label2"
        End With
        '
        ' Label3
        '
        resources.ApplyResources(Me.Label3, "Label3")
        With Me.Label3
            .BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
            .Name = "Label3"
        End With
        '
        ' cmbTeamHome
        '
        resources.ApplyResources(Me.cmbTeamHome, "cmbTeamHome")
        With Me.cmbTeamHome
            .DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
            .FormattingEnabled = True
            .Name = "cmbTeamHome"
        End With
        '
        ' updScoreHome
        '
        resources.ApplyResources(Me.updScoreHome, "updScoreHome")
        With Me.updScoreHome
            .Maximum = New Decimal(New Integer() {999, 0, 0, 0})
            .Name = "updScoreHome"
        End With
        '
        'Label4
        '
        resources.ApplyResources(Me.Label4, "Label4")
        With Me.Label4
            .BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
            .Name = "Label4"
        End With
        '
        ' cmbTeamVisitor
        '
        resources.ApplyResources(Me.cmbTeamVisitor, "cmbTeamVisitor")
        With Me.cmbTeamVisitor
            .DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
            .FormattingEnabled = True
            .Name = "cmbTeamVisitor"
        End With
        '
        ' updScoreVisitor
        '
        resources.ApplyResources(Me.updScoreVisitor, "updScoreVisitor")
        With Me.updScoreVisitor
            .Maximum = New Decimal(New Integer() {999, 0, 0, 0})
            .Name = "updScoreVisitor"
        End With
        '
        ' cmbFlags
        '
        resources.ApplyResources(Me.cmbFlags, "cmbFlags")
        With Me.cmbFlags
            .DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
            .FormattingEnabled = True
            .Name = "cmbFlags"
        End With
        '
        ' btnEdit
        '
        resources.ApplyResources(Me.btnEdit, "btnEdit")
        With Me.btnEdit
            .Name = "btnEdit"
            .UseVisualStyleBackColor = True
        End With
        '
        ' btnDelete
        '
        resources.ApplyResources(Me.btnDelete, "btnDelete")
        With Me.btnDelete
            .Name = "btnDelete"
            .UseVisualStyleBackColor = True
        End With

        '
        ' fraView
        '
        resources.ApplyResources(Me.fraView, "fraView")
        With Me.fraView
            With .Controls
                .Add(Me.Label5)
                .Add(Me.mnvEdit)
                .Add(Me.lblDate)
            End With
            .Name = "fraView"
            .TabStop = False
        End With
        '
        ' Label5
        '
        resources.ApplyResources(Me.Label5, "Label5")
        With Me.Label5
            .BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
            .Name = "Label5"
        End With
        '
        ' mnvEdit
        '
        resources.ApplyResources(Me.mnvEdit, "mnvEdit")
        With Me.mnvEdit
            .Name = "mnvEdit"
        End With
        '
        ' lblDate
        '
        resources.ApplyResources(Me.lblDate, "lblDate")
        With Me.lblDate
            .BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
            .Name = "lblDate"
        End With

        '
        'EditForm
        '
        resources.ApplyResources(Me, "$this")
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None
        Me.CancelButton = Me.btnCancel

        With Me.Controls
            .Add(Me.btnOK)
            .Add(Me.btnApply)
            .Add(Me.btnCancel)
            .Add(Me.dgvRecord)
            .Add(Me.fraInput)
            .Add(Me.fraView)
        End With
        Me.Name = "EditForm"

        CType(Me.dgvRecord, System.ComponentModel.ISupportInitialize).EndInit()
        Me.fraInput.ResumeLayout(False)
        CType(Me.updScoreHome, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.updScoreVisitor, System.ComponentModel.ISupportInitialize).EndInit()
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
    Friend WithEvents cmbTeamVisitor As ComboBox
    Friend WithEvents updScoreVisitor As NumericUpDown
    Friend WithEvents cmbFlags As ComboBox
    Friend WithEvents btnEdit As Button
    Friend WithEvents btnDelete As Button
    Friend WithEvents fraView As GroupBox
    Friend WithEvents Label5 As Label
    Friend WithEvents mnvEdit As MonthCalendar
    Friend WithEvents lblDate As Label

End Class
