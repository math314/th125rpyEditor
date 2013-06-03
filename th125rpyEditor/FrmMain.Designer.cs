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
            this.btnEnd = new System.Windows.Forms.Button();
            this.chkCreateDebugFile = new System.Windows.Forms.CheckBox();
            this.grpFPS = new System.Windows.Forms.GroupBox();
            this.lbl0 = new System.Windows.Forms.Label();
            this.lbl9 = new System.Windows.Forms.Label();
            this.lbl8 = new System.Windows.Forms.Label();
            this.txtFPS0 = new System.Windows.Forms.TextBox();
            this.txtFPS9 = new System.Windows.Forms.TextBox();
            this.txtFPS8 = new System.Windows.Forms.TextBox();
            this.txtFPS7 = new System.Windows.Forms.TextBox();
            this.txtFPS6 = new System.Windows.Forms.TextBox();
            this.lbl7 = new System.Windows.Forms.Label();
            this.lbl6 = new System.Windows.Forms.Label();
            this.lbl5 = new System.Windows.Forms.Label();
            this.lbl4 = new System.Windows.Forms.Label();
            this.lbl3 = new System.Windows.Forms.Label();
            this.txtFPS5 = new System.Windows.Forms.TextBox();
            this.txtFPS4 = new System.Windows.Forms.TextBox();
            this.txtFPS3 = new System.Windows.Forms.TextBox();
            this.txtFPS2 = new System.Windows.Forms.TextBox();
            this.txtFPS1 = new System.Windows.Forms.TextBox();
            this.lbl2 = new System.Windows.Forms.Label();
            this.lbl1 = new System.Windows.Forms.Label();
            this.txtExePass = new System.Windows.Forms.TextBox();
            this.btnGetExePass = new System.Windows.Forms.Button();
            this.grpExePass = new System.Windows.Forms.GroupBox();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.statusStrip = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.grpReplayIndex = new System.Windows.Forms.GroupBox();
            this.txtMaxRpyIndex = new System.Windows.Forms.TextBox();
            this.lblMaxRpyIndex = new System.Windows.Forms.Label();
            this.txtSaveRpyIndex = new System.Windows.Forms.TextBox();
            this.lblSaveRpyIndex = new System.Windows.Forms.Label();
            this.rdbRandomIndex = new System.Windows.Forms.RadioButton();
            this.rdbSaveFixedIndex = new System.Windows.Forms.RadioButton();
            this.grpDebugString = new System.Windows.Forms.GroupBox();
            this.picColor = new System.Windows.Forms.PictureBox();
            this.txtColorA = new System.Windows.Forms.TextBox();
            this.lblColorA = new System.Windows.Forms.Label();
            this.txtColorB = new System.Windows.Forms.TextBox();
            this.txtColorG = new System.Windows.Forms.TextBox();
            this.txtColorR = new System.Windows.Forms.TextBox();
            this.lblColorB = new System.Windows.Forms.Label();
            this.lblColorG = new System.Windows.Forms.Label();
            this.lblColorR = new System.Windows.Forms.Label();
            this.btnChoiceColor = new System.Windows.Forms.Button();
            this.colorDialog = new System.Windows.Forms.ColorDialog();
            this.grpFPS.SuspendLayout();
            this.grpExePass.SuspendLayout();
            this.statusStrip.SuspendLayout();
            this.grpReplayIndex.SuspendLayout();
            this.grpDebugString.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picColor)).BeginInit();
            this.SuspendLayout();
            // 
            // btnStart
            // 
            this.btnStart.Location = new System.Drawing.Point(584, 154);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(75, 23);
            this.btnStart.TabIndex = 0;
            this.btnStart.Text = "開始";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // btnEnd
            // 
            this.btnEnd.Location = new System.Drawing.Point(584, 210);
            this.btnEnd.Name = "btnEnd";
            this.btnEnd.Size = new System.Drawing.Size(75, 23);
            this.btnEnd.TabIndex = 1;
            this.btnEnd.Text = "終了";
            this.btnEnd.UseVisualStyleBackColor = true;
            this.btnEnd.Click += new System.EventHandler(this.btnEnd_Click);
            // 
            // chkCreateDebugFile
            // 
            this.chkCreateDebugFile.AutoSize = true;
            this.chkCreateDebugFile.Location = new System.Drawing.Point(12, 75);
            this.chkCreateDebugFile.Name = "chkCreateDebugFile";
            this.chkCreateDebugFile.Size = new System.Drawing.Size(240, 16);
            this.chkCreateDebugFile.TabIndex = 2;
            this.chkCreateDebugFile.Text = "デバッグ文字列をファイルに出力する。";
            this.chkCreateDebugFile.UseVisualStyleBackColor = true;
            // 
            // grpFPS
            // 
            this.grpFPS.Controls.Add(this.lbl0);
            this.grpFPS.Controls.Add(this.lbl9);
            this.grpFPS.Controls.Add(this.lbl8);
            this.grpFPS.Controls.Add(this.txtFPS0);
            this.grpFPS.Controls.Add(this.txtFPS9);
            this.grpFPS.Controls.Add(this.txtFPS8);
            this.grpFPS.Controls.Add(this.txtFPS7);
            this.grpFPS.Controls.Add(this.txtFPS6);
            this.grpFPS.Controls.Add(this.lbl7);
            this.grpFPS.Controls.Add(this.lbl6);
            this.grpFPS.Controls.Add(this.lbl5);
            this.grpFPS.Controls.Add(this.lbl4);
            this.grpFPS.Controls.Add(this.lbl3);
            this.grpFPS.Controls.Add(this.txtFPS5);
            this.grpFPS.Controls.Add(this.txtFPS4);
            this.grpFPS.Controls.Add(this.txtFPS3);
            this.grpFPS.Controls.Add(this.txtFPS2);
            this.grpFPS.Controls.Add(this.txtFPS1);
            this.grpFPS.Controls.Add(this.lbl2);
            this.grpFPS.Controls.Add(this.lbl1);
            this.grpFPS.Location = new System.Drawing.Point(12, 97);
            this.grpFPS.Name = "grpFPS";
            this.grpFPS.Size = new System.Drawing.Size(330, 163);
            this.grpFPS.TabIndex = 3;
            this.grpFPS.TabStop = false;
            this.grpFPS.Text = "FPSの設定(3.0 ～ 600.0)";
            // 
            // lbl0
            // 
            this.lbl0.AutoSize = true;
            this.lbl0.Location = new System.Drawing.Point(182, 124);
            this.lbl0.Name = "lbl0";
            this.lbl0.Size = new System.Drawing.Size(23, 12);
            this.lbl0.TabIndex = 19;
            this.lbl0.Text = "0 :";
            // 
            // lbl9
            // 
            this.lbl9.AutoSize = true;
            this.lbl9.Location = new System.Drawing.Point(182, 99);
            this.lbl9.Name = "lbl9";
            this.lbl9.Size = new System.Drawing.Size(23, 12);
            this.lbl9.TabIndex = 18;
            this.lbl9.Text = "9 :";
            // 
            // lbl8
            // 
            this.lbl8.AutoSize = true;
            this.lbl8.Location = new System.Drawing.Point(182, 73);
            this.lbl8.Name = "lbl8";
            this.lbl8.Size = new System.Drawing.Size(23, 12);
            this.lbl8.TabIndex = 17;
            this.lbl8.Text = "8 :";
            // 
            // txtFPS0
            // 
            this.txtFPS0.Location = new System.Drawing.Point(211, 121);
            this.txtFPS0.MaxLength = 8;
            this.txtFPS0.Name = "txtFPS0";
            this.txtFPS0.Size = new System.Drawing.Size(88, 19);
            this.txtFPS0.TabIndex = 16;
            // 
            // txtFPS9
            // 
            this.txtFPS9.Location = new System.Drawing.Point(211, 96);
            this.txtFPS9.MaxLength = 8;
            this.txtFPS9.Name = "txtFPS9";
            this.txtFPS9.Size = new System.Drawing.Size(88, 19);
            this.txtFPS9.TabIndex = 15;
            // 
            // txtFPS8
            // 
            this.txtFPS8.Location = new System.Drawing.Point(211, 70);
            this.txtFPS8.MaxLength = 8;
            this.txtFPS8.Name = "txtFPS8";
            this.txtFPS8.Size = new System.Drawing.Size(88, 19);
            this.txtFPS8.TabIndex = 14;
            // 
            // txtFPS7
            // 
            this.txtFPS7.Location = new System.Drawing.Point(211, 44);
            this.txtFPS7.MaxLength = 8;
            this.txtFPS7.Name = "txtFPS7";
            this.txtFPS7.Size = new System.Drawing.Size(88, 19);
            this.txtFPS7.TabIndex = 13;
            // 
            // txtFPS6
            // 
            this.txtFPS6.Location = new System.Drawing.Point(211, 18);
            this.txtFPS6.MaxLength = 8;
            this.txtFPS6.Name = "txtFPS6";
            this.txtFPS6.Size = new System.Drawing.Size(88, 19);
            this.txtFPS6.TabIndex = 12;
            // 
            // lbl7
            // 
            this.lbl7.AutoSize = true;
            this.lbl7.Location = new System.Drawing.Point(182, 47);
            this.lbl7.Name = "lbl7";
            this.lbl7.Size = new System.Drawing.Size(23, 12);
            this.lbl7.TabIndex = 11;
            this.lbl7.Text = "7 :";
            // 
            // lbl6
            // 
            this.lbl6.AutoSize = true;
            this.lbl6.Location = new System.Drawing.Point(182, 21);
            this.lbl6.Name = "lbl6";
            this.lbl6.Size = new System.Drawing.Size(23, 12);
            this.lbl6.TabIndex = 10;
            this.lbl6.Text = "6 :";
            // 
            // lbl5
            // 
            this.lbl5.AutoSize = true;
            this.lbl5.Location = new System.Drawing.Point(16, 124);
            this.lbl5.Name = "lbl5";
            this.lbl5.Size = new System.Drawing.Size(23, 12);
            this.lbl5.TabIndex = 9;
            this.lbl5.Text = "5 :";
            // 
            // lbl4
            // 
            this.lbl4.AutoSize = true;
            this.lbl4.Location = new System.Drawing.Point(16, 99);
            this.lbl4.Name = "lbl4";
            this.lbl4.Size = new System.Drawing.Size(23, 12);
            this.lbl4.TabIndex = 8;
            this.lbl4.Text = "4 :";
            // 
            // lbl3
            // 
            this.lbl3.AutoSize = true;
            this.lbl3.Location = new System.Drawing.Point(16, 73);
            this.lbl3.Name = "lbl3";
            this.lbl3.Size = new System.Drawing.Size(23, 12);
            this.lbl3.TabIndex = 7;
            this.lbl3.Text = "3 :";
            // 
            // txtFPS5
            // 
            this.txtFPS5.Location = new System.Drawing.Point(45, 121);
            this.txtFPS5.MaxLength = 8;
            this.txtFPS5.Name = "txtFPS5";
            this.txtFPS5.Size = new System.Drawing.Size(88, 19);
            this.txtFPS5.TabIndex = 6;
            // 
            // txtFPS4
            // 
            this.txtFPS4.Location = new System.Drawing.Point(45, 96);
            this.txtFPS4.MaxLength = 8;
            this.txtFPS4.Name = "txtFPS4";
            this.txtFPS4.Size = new System.Drawing.Size(88, 19);
            this.txtFPS4.TabIndex = 5;
            // 
            // txtFPS3
            // 
            this.txtFPS3.Location = new System.Drawing.Point(45, 70);
            this.txtFPS3.MaxLength = 8;
            this.txtFPS3.Name = "txtFPS3";
            this.txtFPS3.Size = new System.Drawing.Size(88, 19);
            this.txtFPS3.TabIndex = 4;
            // 
            // txtFPS2
            // 
            this.txtFPS2.Location = new System.Drawing.Point(45, 44);
            this.txtFPS2.MaxLength = 8;
            this.txtFPS2.Name = "txtFPS2";
            this.txtFPS2.Size = new System.Drawing.Size(88, 19);
            this.txtFPS2.TabIndex = 3;
            // 
            // txtFPS1
            // 
            this.txtFPS1.Location = new System.Drawing.Point(45, 18);
            this.txtFPS1.MaxLength = 8;
            this.txtFPS1.Name = "txtFPS1";
            this.txtFPS1.Size = new System.Drawing.Size(88, 19);
            this.txtFPS1.TabIndex = 2;
            // 
            // lbl2
            // 
            this.lbl2.AutoSize = true;
            this.lbl2.Location = new System.Drawing.Point(16, 47);
            this.lbl2.Name = "lbl2";
            this.lbl2.Size = new System.Drawing.Size(23, 12);
            this.lbl2.TabIndex = 1;
            this.lbl2.Text = "2 :";
            // 
            // lbl1
            // 
            this.lbl1.AutoSize = true;
            this.lbl1.Location = new System.Drawing.Point(16, 21);
            this.lbl1.Name = "lbl1";
            this.lbl1.Size = new System.Drawing.Size(23, 12);
            this.lbl1.TabIndex = 0;
            this.lbl1.Text = "1 :";
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
            this.statusStrip.Location = new System.Drawing.Point(0, 272);
            this.statusStrip.Name = "statusStrip";
            this.statusStrip.Size = new System.Drawing.Size(716, 23);
            this.statusStrip.SizingGrip = false;
            this.statusStrip.TabIndex = 8;
            // 
            // toolStripStatusLabel
            // 
            this.toolStripStatusLabel.AutoSize = false;
            this.toolStripStatusLabel.Name = "toolStripStatusLabel";
            this.toolStripStatusLabel.Size = new System.Drawing.Size(710, 18);
            this.toolStripStatusLabel.Text = "th125RpyEditor";
            // 
            // grpReplayIndex
            // 
            this.grpReplayIndex.Controls.Add(this.txtMaxRpyIndex);
            this.grpReplayIndex.Controls.Add(this.lblMaxRpyIndex);
            this.grpReplayIndex.Controls.Add(this.txtSaveRpyIndex);
            this.grpReplayIndex.Controls.Add(this.lblSaveRpyIndex);
            this.grpReplayIndex.Controls.Add(this.rdbRandomIndex);
            this.grpReplayIndex.Controls.Add(this.rdbSaveFixedIndex);
            this.grpReplayIndex.Location = new System.Drawing.Point(348, 12);
            this.grpReplayIndex.Name = "grpReplayIndex";
            this.grpReplayIndex.Size = new System.Drawing.Size(356, 118);
            this.grpReplayIndex.TabIndex = 11;
            this.grpReplayIndex.TabStop = false;
            this.grpReplayIndex.Text = "セーブするリプレイの設定";
            // 
            // txtMaxRpyIndex
            // 
            this.txtMaxRpyIndex.Location = new System.Drawing.Point(260, 89);
            this.txtMaxRpyIndex.MaxLength = 4;
            this.txtMaxRpyIndex.Name = "txtMaxRpyIndex";
            this.txtMaxRpyIndex.Size = new System.Drawing.Size(60, 19);
            this.txtMaxRpyIndex.TabIndex = 5;
            // 
            // lblMaxRpyIndex
            // 
            this.lblMaxRpyIndex.AutoSize = true;
            this.lblMaxRpyIndex.Location = new System.Drawing.Point(6, 92);
            this.lblMaxRpyIndex.Name = "lblMaxRpyIndex";
            this.lblMaxRpyIndex.Size = new System.Drawing.Size(239, 12);
            this.lblMaxRpyIndex.TabIndex = 4;
            this.lblMaxRpyIndex.Tag = "";
            this.lblMaxRpyIndex.Text = "保存するリプレイの番号の上限(25~9999) :";
            // 
            // txtSaveRpyIndex
            // 
            this.txtSaveRpyIndex.Location = new System.Drawing.Point(209, 41);
            this.txtSaveRpyIndex.MaxLength = 4;
            this.txtSaveRpyIndex.Name = "txtSaveRpyIndex";
            this.txtSaveRpyIndex.Size = new System.Drawing.Size(60, 19);
            this.txtSaveRpyIndex.TabIndex = 3;
            // 
            // lblSaveRpyIndex
            // 
            this.lblSaveRpyIndex.AutoSize = true;
            this.lblSaveRpyIndex.Location = new System.Drawing.Point(6, 45);
            this.lblSaveRpyIndex.Name = "lblSaveRpyIndex";
            this.lblSaveRpyIndex.Size = new System.Drawing.Size(197, 12);
            this.lblSaveRpyIndex.TabIndex = 2;
            this.lblSaveRpyIndex.Text = "保存するリプレイの番号(1~9999) :";
            // 
            // rdbRandomIndex
            // 
            this.rdbRandomIndex.AutoSize = true;
            this.rdbRandomIndex.Checked = true;
            this.rdbRandomIndex.Location = new System.Drawing.Point(6, 67);
            this.rdbRandomIndex.Name = "rdbRandomIndex";
            this.rdbRandomIndex.Size = new System.Drawing.Size(276, 16);
            this.rdbRandomIndex.TabIndex = 1;
            this.rdbRandomIndex.TabStop = true;
            this.rdbRandomIndex.Text = "リプレイが保存されていない番号にリプレイを保存する。";
            this.rdbRandomIndex.UseVisualStyleBackColor = true;
            // 
            // rdbSaveFixedIndex
            // 
            this.rdbSaveFixedIndex.AutoSize = true;
            this.rdbSaveFixedIndex.Location = new System.Drawing.Point(6, 19);
            this.rdbSaveFixedIndex.Name = "rdbSaveFixedIndex";
            this.rdbSaveFixedIndex.Size = new System.Drawing.Size(205, 16);
            this.rdbSaveFixedIndex.TabIndex = 0;
            this.rdbSaveFixedIndex.Text = "同じリプレイ番号にリプレイを保存する。";
            this.rdbSaveFixedIndex.UseVisualStyleBackColor = true;
            this.rdbSaveFixedIndex.CheckedChanged += new System.EventHandler(this.rdbSaveFixedIndex_CheckedChanged);
            // 
            // grpDebugString
            // 
            this.grpDebugString.Controls.Add(this.picColor);
            this.grpDebugString.Controls.Add(this.txtColorA);
            this.grpDebugString.Controls.Add(this.lblColorA);
            this.grpDebugString.Controls.Add(this.txtColorB);
            this.grpDebugString.Controls.Add(this.txtColorG);
            this.grpDebugString.Controls.Add(this.txtColorR);
            this.grpDebugString.Controls.Add(this.lblColorB);
            this.grpDebugString.Controls.Add(this.lblColorG);
            this.grpDebugString.Controls.Add(this.lblColorR);
            this.grpDebugString.Controls.Add(this.btnChoiceColor);
            this.grpDebugString.Location = new System.Drawing.Point(348, 136);
            this.grpDebugString.Name = "grpDebugString";
            this.grpDebugString.Size = new System.Drawing.Size(177, 124);
            this.grpDebugString.TabIndex = 12;
            this.grpDebugString.TabStop = false;
            this.grpDebugString.Text = "デバック文字列の描画色";
            // 
            // picColor
            // 
            this.picColor.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.picColor.Location = new System.Drawing.Point(116, 28);
            this.picColor.Name = "picColor";
            this.picColor.Size = new System.Drawing.Size(30, 30);
            this.picColor.TabIndex = 9;
            this.picColor.TabStop = false;
            this.picColor.Paint += new System.Windows.Forms.PaintEventHandler(this.picColor_Paint);
            // 
            // txtColorA
            // 
            this.txtColorA.Location = new System.Drawing.Point(59, 93);
            this.txtColorA.MaxLength = 3;
            this.txtColorA.Name = "txtColorA";
            this.txtColorA.Size = new System.Drawing.Size(30, 19);
            this.txtColorA.TabIndex = 8;
            this.txtColorA.TextChanged += new System.EventHandler(this.txtColor_TextChanged);
            // 
            // lblColorA
            // 
            this.lblColorA.AutoSize = true;
            this.lblColorA.Location = new System.Drawing.Point(6, 96);
            this.lblColorA.Name = "lblColorA";
            this.lblColorA.Size = new System.Drawing.Size(47, 12);
            this.lblColorA.TabIndex = 7;
            this.lblColorA.Text = "A(α) :";
            // 
            // txtColorB
            // 
            this.txtColorB.Location = new System.Drawing.Point(59, 68);
            this.txtColorB.MaxLength = 3;
            this.txtColorB.Name = "txtColorB";
            this.txtColorB.Size = new System.Drawing.Size(30, 19);
            this.txtColorB.TabIndex = 6;
            this.txtColorB.TextChanged += new System.EventHandler(this.txtColor_TextChanged);
            // 
            // txtColorG
            // 
            this.txtColorG.Location = new System.Drawing.Point(59, 43);
            this.txtColorG.MaxLength = 3;
            this.txtColorG.Name = "txtColorG";
            this.txtColorG.Size = new System.Drawing.Size(30, 19);
            this.txtColorG.TabIndex = 5;
            this.txtColorG.TextChanged += new System.EventHandler(this.txtColor_TextChanged);
            // 
            // txtColorR
            // 
            this.txtColorR.Location = new System.Drawing.Point(59, 18);
            this.txtColorR.MaxLength = 3;
            this.txtColorR.Name = "txtColorR";
            this.txtColorR.Size = new System.Drawing.Size(30, 19);
            this.txtColorR.TabIndex = 4;
            this.txtColorR.TextChanged += new System.EventHandler(this.txtColor_TextChanged);
            // 
            // lblColorB
            // 
            this.lblColorB.AutoSize = true;
            this.lblColorB.Location = new System.Drawing.Point(6, 71);
            this.lblColorB.Name = "lblColorB";
            this.lblColorB.Size = new System.Drawing.Size(47, 12);
            this.lblColorB.TabIndex = 3;
            this.lblColorB.Text = "B(青) :";
            // 
            // lblColorG
            // 
            this.lblColorG.AutoSize = true;
            this.lblColorG.Location = new System.Drawing.Point(6, 46);
            this.lblColorG.Name = "lblColorG";
            this.lblColorG.Size = new System.Drawing.Size(47, 12);
            this.lblColorG.TabIndex = 2;
            this.lblColorG.Text = "G(緑) :";
            // 
            // lblColorR
            // 
            this.lblColorR.AutoSize = true;
            this.lblColorR.Location = new System.Drawing.Point(6, 21);
            this.lblColorR.Name = "lblColorR";
            this.lblColorR.Size = new System.Drawing.Size(47, 12);
            this.lblColorR.TabIndex = 1;
            this.lblColorR.Text = "R(赤) :";
            // 
            // btnChoiceColor
            // 
            this.btnChoiceColor.Location = new System.Drawing.Point(95, 80);
            this.btnChoiceColor.Name = "btnChoiceColor";
            this.btnChoiceColor.Size = new System.Drawing.Size(75, 23);
            this.btnChoiceColor.TabIndex = 0;
            this.btnChoiceColor.Text = "色の編集";
            this.btnChoiceColor.UseVisualStyleBackColor = true;
            this.btnChoiceColor.Click += new System.EventHandler(this.btnChoiceColor_Click);
            // 
            // colorDialog
            // 
            this.colorDialog.AnyColor = true;
            this.colorDialog.FullOpen = true;
            // 
            // FrmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(716, 295);
            this.Controls.Add(this.grpDebugString);
            this.Controls.Add(this.grpReplayIndex);
            this.Controls.Add(this.statusStrip);
            this.Controls.Add(this.grpExePass);
            this.Controls.Add(this.grpFPS);
            this.Controls.Add(this.chkCreateDebugFile);
            this.Controls.Add(this.btnEnd);
            this.Controls.Add(this.btnStart);
            this.Font = new System.Drawing.Font("ＭＳ ゴシック", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.MaximizeBox = false;
            this.Name = "FrmMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "th125RpyEditor Ver1.0";
            this.grpFPS.ResumeLayout(false);
            this.grpFPS.PerformLayout();
            this.grpExePass.ResumeLayout(false);
            this.grpExePass.PerformLayout();
            this.statusStrip.ResumeLayout(false);
            this.statusStrip.PerformLayout();
            this.grpReplayIndex.ResumeLayout(false);
            this.grpReplayIndex.PerformLayout();
            this.grpDebugString.ResumeLayout(false);
            this.grpDebugString.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picColor)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.Button btnEnd;
        private System.Windows.Forms.CheckBox chkCreateDebugFile;
        private System.Windows.Forms.GroupBox grpFPS;
        private System.Windows.Forms.Label lbl0;
        private System.Windows.Forms.Label lbl9;
        private System.Windows.Forms.Label lbl8;
        private System.Windows.Forms.TextBox txtFPS0;
        private System.Windows.Forms.TextBox txtFPS9;
        private System.Windows.Forms.TextBox txtFPS8;
        private System.Windows.Forms.TextBox txtFPS7;
        private System.Windows.Forms.TextBox txtFPS6;
        private System.Windows.Forms.Label lbl7;
        private System.Windows.Forms.Label lbl6;
        private System.Windows.Forms.Label lbl5;
        private System.Windows.Forms.Label lbl4;
        private System.Windows.Forms.Label lbl3;
        private System.Windows.Forms.TextBox txtFPS5;
        private System.Windows.Forms.TextBox txtFPS4;
        private System.Windows.Forms.TextBox txtFPS3;
        private System.Windows.Forms.TextBox txtFPS2;
        private System.Windows.Forms.TextBox txtFPS1;
        private System.Windows.Forms.Label lbl2;
        private System.Windows.Forms.Label lbl1;
        private System.Windows.Forms.TextBox txtExePass;
        private System.Windows.Forms.Button btnGetExePass;
        private System.Windows.Forms.GroupBox grpExePass;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.StatusStrip statusStrip;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel;
        private System.Windows.Forms.GroupBox grpReplayIndex;
        private System.Windows.Forms.RadioButton rdbRandomIndex;
        private System.Windows.Forms.RadioButton rdbSaveFixedIndex;
        private System.Windows.Forms.TextBox txtMaxRpyIndex;
        private System.Windows.Forms.Label lblMaxRpyIndex;
        private System.Windows.Forms.TextBox txtSaveRpyIndex;
        private System.Windows.Forms.Label lblSaveRpyIndex;
        private System.Windows.Forms.GroupBox grpDebugString;
        private System.Windows.Forms.ColorDialog colorDialog;
        private System.Windows.Forms.PictureBox picColor;
        private System.Windows.Forms.TextBox txtColorA;
        private System.Windows.Forms.Label lblColorA;
        private System.Windows.Forms.TextBox txtColorB;
        private System.Windows.Forms.TextBox txtColorG;
        private System.Windows.Forms.TextBox txtColorR;
        private System.Windows.Forms.Label lblColorB;
        private System.Windows.Forms.Label lblColorG;
        private System.Windows.Forms.Label lblColorR;
        private System.Windows.Forms.Button btnChoiceColor;
    }
}

