namespace th125rpyEditor
{
    partial class FrmMain
    {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージ リソースが破棄される場合 true、破棄されない場合は false です。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.btnStart = new System.Windows.Forms.Button();
            this.txtExePass = new System.Windows.Forms.TextBox();
            this.btnGetExePass = new System.Windows.Forms.Button();
            this.grpExePass = new System.Windows.Forms.GroupBox();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.statusStrip = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.grpExePass.SuspendLayout();
            this.statusStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnStart
            // 
            this.btnStart.Location = new System.Drawing.Point(367, 30);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(75, 23);
            this.btnStart.TabIndex = 0;
            this.btnStart.Text = "開始";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // txtExePass
            // 
            this.txtExePass.AllowDrop = true;
            this.txtExePass.Location = new System.Drawing.Point(11, 18);
            this.txtExePass.Name = "txtExePass";
            this.txtExePass.Size = new System.Drawing.Size(260, 19);
            this.txtExePass.TabIndex = 5;
            this.txtExePass.DragDrop += new System.Windows.Forms.DragEventHandler(this.txtExePass_DragDrop);
            this.txtExePass.DragOver += new System.Windows.Forms.DragEventHandler(this.txtExePass_DragOver);
            // 
            // btnGetExePass
            // 
            this.btnGetExePass.Location = new System.Drawing.Point(277, 16);
            this.btnGetExePass.Name = "btnGetExePass";
            this.btnGetExePass.Size = new System.Drawing.Size(43, 23);
            this.btnGetExePass.TabIndex = 6;
            this.btnGetExePass.Text = "参照";
            this.btnGetExePass.UseVisualStyleBackColor = true;
            this.btnGetExePass.Click += new System.EventHandler(this.btnGetExePass_Click);
            // 
            // grpExePass
            // 
            this.grpExePass.Controls.Add(this.txtExePass);
            this.grpExePass.Controls.Add(this.btnGetExePass);
            this.grpExePass.Location = new System.Drawing.Point(12, 12);
            this.grpExePass.Name = "grpExePass";
            this.grpExePass.Size = new System.Drawing.Size(330, 57);
            this.grpExePass.TabIndex = 7;
            this.grpExePass.TabStop = false;
            this.grpExePass.Text = "東方文花帖　～　ダブルスポイラー　へのパス";
            // 
            // openFileDialog
            // 
            this.openFileDialog.Filter = "\"実行　ファイル(*.exe)|*.exe|すべてのファイル (*.*)|*.*\"";
            this.openFileDialog.Title = "実行exeファイルの選択";
            // 
            // statusStrip
            // 
            this.statusStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel});
            this.statusStrip.Location = new System.Drawing.Point(0, 76);
            this.statusStrip.Name = "statusStrip";
            this.statusStrip.Size = new System.Drawing.Size(461, 23);
            this.statusStrip.SizingGrip = false;
            this.statusStrip.TabIndex = 8;
            // 
            // toolStripStatusLabel
            // 
            this.toolStripStatusLabel.Name = "toolStripStatusLabel";
            this.toolStripStatusLabel.Size = new System.Drawing.Size(97, 18);
            this.toolStripStatusLabel.Text = "th125RpyEditor";
            // 
            // FrmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(461, 99);
            this.Controls.Add(this.statusStrip);
            this.Controls.Add(this.grpExePass);
            this.Controls.Add(this.btnStart);
            this.Font = new System.Drawing.Font("ＭＳ ゴシック", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.MaximizeBox = false;
            this.Name = "FrmMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "th125RpyEditor Ver1.0";
            this.grpExePass.ResumeLayout(false);
            this.grpExePass.PerformLayout();
            this.statusStrip.ResumeLayout(false);
            this.statusStrip.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.TextBox txtExePass;
        private System.Windows.Forms.Button btnGetExePass;
        private System.Windows.Forms.GroupBox grpExePass;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.StatusStrip statusStrip;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel;
    }
}

