namespace WorldGenGUI
{
    partial class PGZForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(PGZForm));
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.butGenerate = new System.Windows.Forms.Button();
            this.butClose = new System.Windows.Forms.Button();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.numZones = new System.Windows.Forms.NumericUpDown();
            this.tBoxName = new System.Windows.Forms.TextBox();
            this.comboDiff = new System.Windows.Forms.ComboBox();
            this.comboTheme = new System.Windows.Forms.ComboBox();
            this.comboSize = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.toolViewer = new System.Windows.Forms.DataGridView();
            this.enemyViewer = new System.Windows.Forms.DataGridView();
            this.label2 = new System.Windows.Forms.Label();
            this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.barSize = new System.Windows.Forms.TrackBar();
            this.barRatio = new System.Windows.Forms.TrackBar();
            this.label5 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.labCoheren = new System.Windows.Forms.Label();
            this.labInsane = new System.Windows.Forms.Label();
            this.barCoheren = new System.Windows.Forms.TrackBar();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.statusProgress = new System.Windows.Forms.ToolStripProgressBar();
            this.statusText = new System.Windows.Forms.ToolStripStatusLabel();
            this.charImgList = new System.Windows.Forms.ImageList(this.components);
            this.butPlay = new System.Windows.Forms.Button();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numZones)).BeginInit();
            this.tabPage2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.toolViewer)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.enemyViewer)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
            this.tabPage3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.barSize)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.barRatio)).BeginInit();
            this.tabPage4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.barCoheren)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(8, 12);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(494, 46);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // butGenerate
            // 
            this.butGenerate.Location = new System.Drawing.Point(87, 346);
            this.butGenerate.Name = "butGenerate";
            this.butGenerate.Size = new System.Drawing.Size(102, 28);
            this.butGenerate.TabIndex = 4;
            this.butGenerate.Text = "Generate";
            this.butGenerate.UseVisualStyleBackColor = true;
            this.butGenerate.Click += new System.EventHandler(this.butGenerate_Click_1);
            // 
            // butClose
            // 
            this.butClose.Location = new System.Drawing.Point(374, 346);
            this.butClose.Name = "butClose";
            this.butClose.Size = new System.Drawing.Size(102, 28);
            this.butClose.TabIndex = 4;
            this.butClose.Text = "Close";
            this.butClose.UseVisualStyleBackColor = true;
            this.butClose.Click += new System.EventHandler(this.butClose_Click_1);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Controls.Add(this.tabPage4);
            this.tabControl1.Location = new System.Drawing.Point(12, 64);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(502, 265);
            this.tabControl1.TabIndex = 6;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.numZones);
            this.tabPage1.Controls.Add(this.tBoxName);
            this.tabPage1.Controls.Add(this.comboDiff);
            this.tabPage1.Controls.Add(this.comboTheme);
            this.tabPage1.Controls.Add(this.comboSize);
            this.tabPage1.Controls.Add(this.label7);
            this.tabPage1.Controls.Add(this.label8);
            this.tabPage1.Controls.Add(this.label1);
            this.tabPage1.Controls.Add(this.label9);
            this.tabPage1.Controls.Add(this.label4);
            this.tabPage1.Controls.Add(this.label10);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(494, 239);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Quick Start";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // numZones
            // 
            this.numZones.Location = new System.Drawing.Point(227, 129);
            this.numZones.Maximum = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.numZones.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numZones.Name = "numZones";
            this.numZones.Size = new System.Drawing.Size(53, 20);
            this.numZones.TabIndex = 14;
            this.numZones.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // tBoxName
            // 
            this.tBoxName.Location = new System.Drawing.Point(34, 38);
            this.tBoxName.Name = "tBoxName";
            this.tBoxName.Size = new System.Drawing.Size(139, 20);
            this.tBoxName.TabIndex = 13;
            // 
            // comboDiff
            // 
            this.comboDiff.FormattingEnabled = true;
            this.comboDiff.Items.AddRange(new object[] {
            "Baby",
            "Easy",
            "Normal",
            "Hard",
            "You will cry"});
            this.comboDiff.Location = new System.Drawing.Point(34, 173);
            this.comboDiff.Name = "comboDiff";
            this.comboDiff.Size = new System.Drawing.Size(140, 21);
            this.comboDiff.TabIndex = 10;
            // 
            // comboTheme
            // 
            this.comboTheme.FormattingEnabled = true;
            this.comboTheme.Items.AddRange(new object[] {
            "Zoldo",
            "Indiana Janes",
            "Blackman"});
            this.comboTheme.Location = new System.Drawing.Point(33, 84);
            this.comboTheme.Name = "comboTheme";
            this.comboTheme.Size = new System.Drawing.Size(140, 21);
            this.comboTheme.TabIndex = 11;
            // 
            // comboSize
            // 
            this.comboSize.FormattingEnabled = true;
            this.comboSize.Items.AddRange(new object[] {
            "Tiny",
            "Small",
            "Medium",
            "Big",
            "Collosal",
            "Universe"});
            this.comboSize.Location = new System.Drawing.Point(34, 129);
            this.comboSize.Name = "comboSize";
            this.comboSize.Size = new System.Drawing.Size(140, 21);
            this.comboSize.TabIndex = 12;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(31, 157);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(53, 13);
            this.label7.TabIndex = 7;
            this.label7.Text = "Difficulty :";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(31, 68);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(46, 13);
            this.label8.TabIndex = 6;
            this.label8.Text = "Theme :";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(221, 22);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(59, 13);
            this.label1.TabIndex = 9;
            this.label1.Text = "Character :";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(30, 22);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(66, 13);
            this.label9.TabIndex = 9;
            this.label9.Text = "Your Name :";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(221, 112);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(68, 13);
            this.label4.TabIndex = 8;
            this.label4.Text = "Num Zones :";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(31, 112);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(33, 13);
            this.label10.TabIndex = 8;
            this.label10.Text = "Size :";
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.toolViewer);
            this.tabPage2.Controls.Add(this.enemyViewer);
            this.tabPage2.Controls.Add(this.label2);
            this.tabPage2.Controls.Add(this.numericUpDown1);
            this.tabPage2.Controls.Add(this.label11);
            this.tabPage2.Controls.Add(this.label12);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(494, 239);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Tools & Enemies";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // toolViewer
            // 
            this.toolViewer.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.toolViewer.Location = new System.Drawing.Point(18, 56);
            this.toolViewer.Name = "toolViewer";
            this.toolViewer.RowHeadersVisible = false;
            this.toolViewer.Size = new System.Drawing.Size(221, 166);
            this.toolViewer.TabIndex = 12;
            this.toolViewer.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.toolViewer_CellValueChanged);
            // 
            // enemyViewer
            // 
            this.enemyViewer.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.enemyViewer.Location = new System.Drawing.Point(249, 32);
            this.enemyViewer.Name = "enemyViewer";
            this.enemyViewer.RowHeadersVisible = false;
            this.enemyViewer.Size = new System.Drawing.Size(232, 189);
            this.enemyViewer.TabIndex = 11;
            this.enemyViewer.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.enemyViewer_CellValueChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(15, 32);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(74, 13);
            this.label2.TabIndex = 9;
            this.label2.Text = "Starting tools :";
            // 
            // numericUpDown1
            // 
            this.numericUpDown1.Location = new System.Drawing.Point(95, 30);
            this.numericUpDown1.Maximum = new decimal(new int[] {
            4,
            0,
            0,
            0});
            this.numericUpDown1.Name = "numericUpDown1";
            this.numericUpDown1.Size = new System.Drawing.Size(53, 20);
            this.numericUpDown1.TabIndex = 8;
            this.numericUpDown1.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(246, 10);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(53, 13);
            this.label11.TabIndex = 4;
            this.label11.Text = "Enemies :";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(15, 10);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(39, 13);
            this.label12.TabIndex = 5;
            this.label12.Text = "Tools :";
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.barSize);
            this.tabPage3.Controls.Add(this.barRatio);
            this.tabPage3.Controls.Add(this.label5);
            this.tabPage3.Controls.Add(this.label3);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage3.Size = new System.Drawing.Size(494, 239);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "Dungeons";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // barSize
            // 
            this.barSize.Location = new System.Drawing.Point(127, 121);
            this.barSize.Name = "barSize";
            this.barSize.Size = new System.Drawing.Size(174, 42);
            this.barSize.TabIndex = 2;
            // 
            // barRatio
            // 
            this.barRatio.Location = new System.Drawing.Point(127, 54);
            this.barRatio.Name = "barRatio";
            this.barRatio.Size = new System.Drawing.Size(174, 42);
            this.barRatio.TabIndex = 2;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(79, 95);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(33, 13);
            this.label5.TabIndex = 0;
            this.label5.Text = "Size :";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(81, 23);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(110, 13);
            this.label3.TabIndex = 0;
            this.label3.Text = "Ratio puzzles/action :";
            // 
            // tabPage4
            // 
            this.tabPage4.Controls.Add(this.labCoheren);
            this.tabPage4.Controls.Add(this.labInsane);
            this.tabPage4.Controls.Add(this.barCoheren);
            this.tabPage4.Controls.Add(this.pictureBox2);
            this.tabPage4.Location = new System.Drawing.Point(4, 22);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage4.Size = new System.Drawing.Size(494, 239);
            this.tabPage4.TabIndex = 3;
            this.tabPage4.Text = "Coherenciator";
            this.tabPage4.UseVisualStyleBackColor = true;
            // 
            // labCoheren
            // 
            this.labCoheren.AutoSize = true;
            this.labCoheren.Location = new System.Drawing.Point(49, 12);
            this.labCoheren.Name = "labCoheren";
            this.labCoheren.Size = new System.Drawing.Size(50, 13);
            this.labCoheren.TabIndex = 2;
            this.labCoheren.Text = "Coherent";
            // 
            // labInsane
            // 
            this.labInsane.AutoSize = true;
            this.labInsane.Location = new System.Drawing.Point(410, 12);
            this.labInsane.Name = "labInsane";
            this.labInsane.Size = new System.Drawing.Size(42, 13);
            this.labInsane.TabIndex = 2;
            this.labInsane.Text = "Insane!";
            // 
            // barCoheren
            // 
            this.barCoheren.Location = new System.Drawing.Point(68, 29);
            this.barCoheren.Maximum = 30;
            this.barCoheren.Name = "barCoheren";
            this.barCoheren.Size = new System.Drawing.Size(369, 42);
            this.barCoheren.TabIndex = 1;
            this.barCoheren.Value = 15;
            // 
            // pictureBox2
            // 
            this.pictureBox2.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox2.Image")));
            this.pictureBox2.Location = new System.Drawing.Point(99, 29);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(305, 237);
            this.pictureBox2.TabIndex = 0;
            this.pictureBox2.TabStop = false;
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.statusProgress,
            this.statusText});
            this.statusStrip1.Location = new System.Drawing.Point(0, 385);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.statusStrip1.Size = new System.Drawing.Size(526, 22);
            this.statusStrip1.SizingGrip = false;
            this.statusStrip1.TabIndex = 7;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // statusProgress
            // 
            this.statusProgress.ForeColor = System.Drawing.SystemColors.ControlText;
            this.statusProgress.MarqueeAnimationSpeed = 50;
            this.statusProgress.Maximum = 16;
            this.statusProgress.Name = "statusProgress";
            this.statusProgress.Size = new System.Drawing.Size(100, 16);
            // 
            // statusText
            // 
            this.statusText.Name = "statusText";
            this.statusText.Size = new System.Drawing.Size(25, 17);
            this.statusText.Text = "Idle";
            // 
            // charImgList
            // 
            this.charImgList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("charImgList.ImageStream")));
            this.charImgList.TransparentColor = System.Drawing.Color.Transparent;
            this.charImgList.Images.SetKeyName(0, "indi.bmp");
            this.charImgList.Images.SetKeyName(1, "skull.bmp");
            // 
            // butPlay
            // 
            this.butPlay.Enabled = false;
            this.butPlay.Location = new System.Drawing.Point(234, 346);
            this.butPlay.Name = "butPlay";
            this.butPlay.Size = new System.Drawing.Size(101, 27);
            this.butPlay.TabIndex = 8;
            this.butPlay.Text = "Play";
            this.butPlay.UseVisualStyleBackColor = true;
            this.butPlay.Click += new System.EventHandler(this.butPlay_Click);
            // 
            // backgroundWorker1
            // 
            this.backgroundWorker1.DoWork += new System.ComponentModel.DoWorkEventHandler(this.backgroundWorker1_DoWork);
            // 
            // PGZForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(526, 407);
            this.Controls.Add(this.butPlay);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.butClose);
            this.Controls.Add(this.butGenerate);
            this.Controls.Add(this.pictureBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "PGZForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "PGZ Game Generator";
            this.Load += new System.EventHandler(this.PGZForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numZones)).EndInit();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.toolViewer)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.enemyViewer)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
            this.tabPage3.ResumeLayout(false);
            this.tabPage3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.barSize)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.barRatio)).EndInit();
            this.tabPage4.ResumeLayout(false);
            this.tabPage4.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.barCoheren)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Button butGenerate;
        private System.Windows.Forms.Button butClose;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TextBox tBoxName;
        private System.Windows.Forms.ComboBox comboDiff;
        private System.Windows.Forms.ComboBox comboTheme;
        private System.Windows.Forms.ComboBox comboSize;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel statusText;
        private System.Windows.Forms.ToolStripProgressBar statusProgress;
        private System.Windows.Forms.NumericUpDown numericUpDown1;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.TabPage tabPage4;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TrackBar barSize;
        private System.Windows.Forms.TrackBar barRatio;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.ImageList charImgList;
        private System.Windows.Forms.DataGridView enemyViewer;
        private System.Windows.Forms.DataGridView toolViewer;
        private System.Windows.Forms.TrackBar barCoheren;
        private System.Windows.Forms.Label labCoheren;
        private System.Windows.Forms.Label labInsane;
        private System.Windows.Forms.NumericUpDown numZones;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button butPlay;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
    }
}

