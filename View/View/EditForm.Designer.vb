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
        Me.fraView = New System.Windows.Forms.GroupBox()

        CType(Me.dgvRecord, System.ComponentModel.ISupportInitialize).BeginInit
        Me.SuspendLayout

        Me.Name = "EditForm"
        CType(Me.dgvRecord, System.ComponentModel.ISupportInitialize).EndInit
        Me.ResumeLayout(false)
    End Sub

    Friend WithEvents btnOK As Button
    Friend WithEvents btnApply As Button
    Friend WithEvents btnCancel As Button
    Friend WithEvents dgvRecord As DataGridView
    Friend WithEvents fraInput As GroupBox
    Friend WithEvents fraView As GroupBox

End Class
