namespace ParserTreeViewer
{
 partial class Form1
 {
  /// <summary>
  /// Required designer variable.
  /// </summary>
  private System.ComponentModel.IContainer components = null;

  /// <summary>
  /// Clean up any resources being used.
  /// </summary>
  /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
  protected override void Dispose( bool disposing )
  {
   if( disposing && ( components != null ) )
   {
    components.Dispose();
   }
   base.Dispose( disposing );
  }

  #region Windows Form Designer generated code

  /// <summary>
  /// Required method for Designer support - do not modify
  /// the contents of this method with the code editor.
  /// </summary>
  private void InitializeComponent()
  {
   this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
   this.splitContainer1 = new System.Windows.Forms.SplitContainer();
   this.treeView1 = new System.Windows.Forms.TreeView();
   this.listView1 = new System.Windows.Forms.ListView();
   this.columnHeader1 = new System.Windows.Forms.ColumnHeader();
   this.splitContainer1.Panel1.SuspendLayout();
   this.splitContainer1.Panel2.SuspendLayout();
   this.splitContainer1.SuspendLayout();
   this.SuspendLayout();
   // 
   // openFileDialog1
   // 
   this.openFileDialog1.FileName = "openFileDialog1";
   // 
   // splitContainer1
   // 
   this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
   this.splitContainer1.Location = new System.Drawing.Point( 0, 0 );
   this.splitContainer1.Name = "splitContainer1";
   // 
   // splitContainer1.Panel1
   // 
   this.splitContainer1.Panel1.Controls.Add( this.listView1 );
   // 
   // splitContainer1.Panel2
   // 
   this.splitContainer1.Panel2.Controls.Add( this.treeView1 );
   this.splitContainer1.Size = new System.Drawing.Size( 1494, 789 );
   this.splitContainer1.SplitterDistance = 498;
   this.splitContainer1.TabIndex = 0;
   // 
   // treeView1
   // 
   this.treeView1.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
               | System.Windows.Forms.AnchorStyles.Left )
               | System.Windows.Forms.AnchorStyles.Right ) ) );
   this.treeView1.Font = new System.Drawing.Font( "Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.treeView1.Location = new System.Drawing.Point( 3, 3 );
   this.treeView1.Name = "treeView1";
   this.treeView1.Size = new System.Drawing.Size( 986, 783 );
   this.treeView1.TabIndex = 0;
   // 
   // listView1
   // 
   this.listView1.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
               | System.Windows.Forms.AnchorStyles.Left )
               | System.Windows.Forms.AnchorStyles.Right ) ) );
   this.listView1.Columns.AddRange( new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1} );
   this.listView1.Font = new System.Drawing.Font( "Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
   this.listView1.Location = new System.Drawing.Point( 4, 3 );
   this.listView1.Name = "listView1";
   this.listView1.Size = new System.Drawing.Size( 491, 783 );
   this.listView1.TabIndex = 0;
   this.listView1.UseCompatibleStateImageBehavior = false;
   this.listView1.View = System.Windows.Forms.View.List;
   this.listView1.VirtualMode = true;
   this.listView1.SelectedIndexChanged += new System.EventHandler( this.listView1_SelectedIndexChanged );
   this.listView1.RetrieveVirtualItem += new System.Windows.Forms.RetrieveVirtualItemEventHandler( this.listView1_RetrieveVirtualItem );
   // 
   // columnHeader1
   // 
   this.columnHeader1.Width = 0;
   // 
   // Form1
   // 
   this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
   this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
   this.ClientSize = new System.Drawing.Size( 1494, 789 );
   this.Controls.Add( this.splitContainer1 );
   this.Name = "Form1";
   this.Text = "Parser Viewer";
   this.Load += new System.EventHandler( this.Form1_Load );
   this.splitContainer1.Panel1.ResumeLayout( false );
   this.splitContainer1.Panel2.ResumeLayout( false );
   this.splitContainer1.ResumeLayout( false );
   this.ResumeLayout( false );

  }

  #endregion

  private System.Windows.Forms.OpenFileDialog openFileDialog1;
  private System.Windows.Forms.SplitContainer splitContainer1;
  private System.Windows.Forms.TreeView treeView1;
  private System.Windows.Forms.ListView listView1;
  private System.Windows.Forms.ColumnHeader columnHeader1;
 }
}

