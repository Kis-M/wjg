namespace WindowsFormsApplication1
{
    partial class Form2
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
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle3 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle4 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle5 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle6 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle7 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle8 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle9 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle10 = new System.Windows.Forms.DataGridViewCellStyle();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form2));
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.btnOpen = new System.Windows.Forms.Button();
            this.cbxPortName = new System.Windows.Forms.ComboBox();
            this.cbxPortBaud = new System.Windows.Forms.ComboBox();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.comboBoxCheck = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.comboBoxStop = new System.Windows.Forms.ComboBox();
            this.label6 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label4 = new System.Windows.Forms.Label();
            this.comboBoxBits = new System.Windows.Forms.ComboBox();
            this.saveFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.textBoxMinTmp = new System.Windows.Forms.TextBox();
            this.textBoxMinHum = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.label3 = new System.Windows.Forms.Label();
            this.textBoxMaxTmp = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.textBoxMaxHum = new System.Windows.Forms.TextBox();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.btnRead = new System.Windows.Forms.Button();
            this.btnInsert = new System.Windows.Forms.Button();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.btnDeleteAll = new System.Windows.Forms.Button();
            this.序号 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.温度 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.湿度 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.温度最小 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.温度最大 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.湿度最小 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.湿度最大 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.触发报警 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.时间 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.statusStrip1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.SuspendLayout();
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1});
            this.statusStrip1.Location = new System.Drawing.Point(0, 649);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(1416, 22);
            this.statusStrip1.TabIndex = 107;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(0, 17);
            // 
            // btnOpen
            // 
            this.btnOpen.Location = new System.Drawing.Point(574, 25);
            this.btnOpen.Name = "btnOpen";
            this.btnOpen.Size = new System.Drawing.Size(80, 23);
            this.btnOpen.TabIndex = 6;
            this.btnOpen.Text = "打开串口";
            this.btnOpen.UseVisualStyleBackColor = true;
            this.btnOpen.Click += new System.EventHandler(this.btnOpen_Click);
            // 
            // cbxPortName
            // 
            this.cbxPortName.FormattingEnabled = true;
            this.cbxPortName.Location = new System.Drawing.Point(53, 25);
            this.cbxPortName.Name = "cbxPortName";
            this.cbxPortName.Size = new System.Drawing.Size(53, 20);
            this.cbxPortName.TabIndex = 7;
            this.cbxPortName.Text = "COM2";
            // 
            // cbxPortBaud
            // 
            this.cbxPortBaud.FormattingEnabled = true;
            this.cbxPortBaud.Items.AddRange(new object[] {
            "9600",
            "14400",
            "19200",
            "28800",
            "38400",
            "57600",
            "115200"});
            this.cbxPortBaud.Location = new System.Drawing.Point(164, 25);
            this.cbxPortBaud.Name = "cbxPortBaud";
            this.cbxPortBaud.Size = new System.Drawing.Size(66, 20);
            this.cbxPortBaud.TabIndex = 8;
            this.cbxPortBaud.Text = "9600";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(6, 29);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(41, 12);
            this.label11.TabIndex = 9;
            this.label11.Text = "串口号";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(121, 29);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(41, 12);
            this.label12.TabIndex = 10;
            this.label12.Text = "波特率";
            // 
            // comboBoxCheck
            // 
            this.comboBoxCheck.FormattingEnabled = true;
            this.comboBoxCheck.Items.AddRange(new object[] {
            "None",
            "Odd ",
            "Even ",
            "Mark ",
            "Space "});
            this.comboBoxCheck.Location = new System.Drawing.Point(291, 26);
            this.comboBoxCheck.Name = "comboBoxCheck";
            this.comboBoxCheck.Size = new System.Drawing.Size(67, 20);
            this.comboBoxCheck.TabIndex = 11;
            this.comboBoxCheck.Text = "None";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(249, 29);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(41, 12);
            this.label5.TabIndex = 13;
            this.label5.Text = "校验位";
            // 
            // comboBoxStop
            // 
            this.comboBoxStop.FormattingEnabled = true;
            this.comboBoxStop.Items.AddRange(new object[] {
            "1",
            "2",
            "1.5"});
            this.comboBoxStop.Location = new System.Drawing.Point(528, 25);
            this.comboBoxStop.Name = "comboBoxStop";
            this.comboBoxStop.Size = new System.Drawing.Size(32, 20);
            this.comboBoxStop.TabIndex = 15;
            this.comboBoxStop.Text = "1";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(484, 29);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(41, 12);
            this.label6.TabIndex = 16;
            this.label6.Text = "停止位";
            // 
            // groupBox2
            // 
            this.groupBox2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Controls.Add(this.comboBoxStop);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.comboBoxBits);
            this.groupBox2.Controls.Add(this.btnOpen);
            this.groupBox2.Controls.Add(this.comboBoxCheck);
            this.groupBox2.Controls.Add(this.label12);
            this.groupBox2.Controls.Add(this.label11);
            this.groupBox2.Controls.Add(this.cbxPortBaud);
            this.groupBox2.Controls.Add(this.cbxPortName);
            this.groupBox2.Location = new System.Drawing.Point(6, 585);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(896, 59);
            this.groupBox2.TabIndex = 106;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "串口属性";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(376, 29);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(41, 12);
            this.label4.TabIndex = 14;
            this.label4.Text = "数据位";
            // 
            // comboBoxBits
            // 
            this.comboBoxBits.FormattingEnabled = true;
            this.comboBoxBits.Items.AddRange(new object[] {
            "8",
            "9"});
            this.comboBoxBits.Location = new System.Drawing.Point(420, 25);
            this.comboBoxBits.Name = "comboBoxBits";
            this.comboBoxBits.Size = new System.Drawing.Size(49, 20);
            this.comboBoxBits.TabIndex = 12;
            this.comboBoxBits.Text = "8";
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.FileName = "openFileDialog1";
            // 
            // chart1
            // 
            chartArea1.AxisX.Maximum = 255D;
            chartArea1.AxisX.Minimum = 0D;
            chartArea1.AxisY.MajorGrid.Interval = 0D;
            chartArea1.AxisY.MajorTickMark.Interval = 0D;
            chartArea1.AxisY.MajorTickMark.LineColor = System.Drawing.Color.Red;
            chartArea1.AxisY.Maximum = 255D;
            chartArea1.AxisY.Minimum = 0D;
            chartArea1.Name = "ChartArea1";
            this.chart1.ChartAreas.Add(chartArea1);
            legend1.Name = "Legend1";
            this.chart1.Legends.Add(legend1);
            this.chart1.Location = new System.Drawing.Point(2, 1);
            this.chart1.Name = "chart1";
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series1.Legend = "Legend1";
            series1.Name = "温度";
            series2.ChartArea = "ChartArea1";
            series2.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series2.Legend = "Legend1";
            series2.Name = "湿度";
            this.chart1.Series.Add(series1);
            this.chart1.Series.Add(series2);
            this.chart1.Size = new System.Drawing.Size(703, 399);
            this.chart1.TabIndex = 108;
            this.chart1.Text = "chart1";
            // 
            // textBoxMinTmp
            // 
            this.textBoxMinTmp.Location = new System.Drawing.Point(87, 452);
            this.textBoxMinTmp.Name = "textBoxMinTmp";
            this.textBoxMinTmp.Size = new System.Drawing.Size(100, 21);
            this.textBoxMinTmp.TabIndex = 109;
            this.textBoxMinTmp.Text = "5";
            // 
            // textBoxMinHum
            // 
            this.textBoxMinHum.Location = new System.Drawing.Point(432, 452);
            this.textBoxMinHum.Name = "textBoxMinHum";
            this.textBoxMinHum.Size = new System.Drawing.Size(100, 21);
            this.textBoxMinHum.TabIndex = 110;
            this.textBoxMinHum.Tag = "5";
            this.textBoxMinHum.Text = "5";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(11, 455);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(65, 12);
            this.label1.TabIndex = 111;
            this.label1.Text = "温度最小值";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(358, 455);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 12);
            this.label2.TabIndex = 112;
            this.label2.Text = "湿度最小值";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(11, 482);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(65, 12);
            this.label3.TabIndex = 114;
            this.label3.Text = "温度最大值";
            // 
            // textBoxMaxTmp
            // 
            this.textBoxMaxTmp.Location = new System.Drawing.Point(87, 479);
            this.textBoxMaxTmp.Name = "textBoxMaxTmp";
            this.textBoxMaxTmp.Size = new System.Drawing.Size(100, 21);
            this.textBoxMaxTmp.TabIndex = 113;
            this.textBoxMaxTmp.Text = "50";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(358, 482);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(65, 12);
            this.label7.TabIndex = 116;
            this.label7.Text = "湿度最大值";
            // 
            // textBoxMaxHum
            // 
            this.textBoxMaxHum.Location = new System.Drawing.Point(432, 479);
            this.textBoxMaxHum.Name = "textBoxMaxHum";
            this.textBoxMaxHum.Size = new System.Drawing.Size(100, 21);
            this.textBoxMaxHum.TabIndex = 115;
            this.textBoxMaxHum.Text = "40";
            // 
            // pictureBox2
            // 
            this.pictureBox2.Image = global::串口数据采集.Properties.Resources.normal;
            this.pictureBox2.Location = new System.Drawing.Point(360, 506);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(63, 66);
            this.pictureBox2.TabIndex = 118;
            this.pictureBox2.TabStop = false;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::串口数据采集.Properties.Resources.normal;
            this.pictureBox1.Location = new System.Drawing.Point(13, 506);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(67, 66);
            this.pictureBox1.TabIndex = 117;
            this.pictureBox1.TabStop = false;
            // 
            // btnRead
            // 
            this.btnRead.Location = new System.Drawing.Point(584, 455);
            this.btnRead.Name = "btnRead";
            this.btnRead.Size = new System.Drawing.Size(80, 23);
            this.btnRead.TabIndex = 119;
            this.btnRead.Text = "读取";
            this.btnRead.UseVisualStyleBackColor = true;
            this.btnRead.Click += new System.EventHandler(this.btnRead_Click);
            // 
            // btnInsert
            // 
            this.btnInsert.Location = new System.Drawing.Point(584, 484);
            this.btnInsert.Name = "btnInsert";
            this.btnInsert.Size = new System.Drawing.Size(80, 23);
            this.btnInsert.TabIndex = 120;
            this.btnInsert.Text = "追加";
            this.btnInsert.UseVisualStyleBackColor = true;
            this.btnInsert.Click += new System.EventHandler(this.btnInsert_Click);
            // 
            // dataGridView1
            // 
            this.dataGridView1.AllowUserToAddRows = false;
            this.dataGridView1.AllowUserToDeleteRows = false;
            this.dataGridView1.AllowUserToResizeColumns = false;
            this.dataGridView1.AllowUserToResizeRows = false;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dataGridView1.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.序号,
            this.温度,
            this.湿度,
            this.温度最小,
            this.温度最大,
            this.湿度最小,
            this.湿度最大,
            this.触发报警,
            this.时间});
            this.dataGridView1.Location = new System.Drawing.Point(685, 1);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowHeadersVisible = false;
            this.dataGridView1.RowTemplate.Height = 23;
            this.dataGridView1.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.dataGridView1.Size = new System.Drawing.Size(731, 643);
            this.dataGridView1.TabIndex = 122;
            // 
            // btnDeleteAll
            // 
            this.btnDeleteAll.Location = new System.Drawing.Point(584, 513);
            this.btnDeleteAll.Name = "btnDeleteAll";
            this.btnDeleteAll.Size = new System.Drawing.Size(80, 23);
            this.btnDeleteAll.TabIndex = 123;
            this.btnDeleteAll.Text = "删除all";
            this.btnDeleteAll.UseVisualStyleBackColor = true;
            this.btnDeleteAll.Click += new System.EventHandler(this.btnDeleteAll_Click);
            // 
            // 序号
            // 
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            this.序号.DefaultCellStyle = dataGridViewCellStyle2;
            this.序号.HeaderText = "序号";
            this.序号.Name = "序号";
            this.序号.Width = 60;
            // 
            // 温度
            // 
            dataGridViewCellStyle3.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            this.温度.DefaultCellStyle = dataGridViewCellStyle3;
            this.温度.HeaderText = "温度";
            this.温度.Name = "温度";
            this.温度.Width = 80;
            // 
            // 湿度
            // 
            dataGridViewCellStyle4.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            this.湿度.DefaultCellStyle = dataGridViewCellStyle4;
            this.湿度.HeaderText = "湿度";
            this.湿度.Name = "湿度";
            this.湿度.Width = 60;
            // 
            // 温度最小
            // 
            dataGridViewCellStyle5.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            this.温度最小.DefaultCellStyle = dataGridViewCellStyle5;
            this.温度最小.HeaderText = "温度最小";
            this.温度最小.Name = "温度最小";
            this.温度最小.Width = 80;
            // 
            // 温度最大
            // 
            dataGridViewCellStyle6.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            this.温度最大.DefaultCellStyle = dataGridViewCellStyle6;
            this.温度最大.HeaderText = "温度最大";
            this.温度最大.Name = "温度最大";
            this.温度最大.Width = 80;
            // 
            // 湿度最小
            // 
            dataGridViewCellStyle7.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            this.湿度最小.DefaultCellStyle = dataGridViewCellStyle7;
            this.湿度最小.HeaderText = "湿度最小";
            this.湿度最小.Name = "湿度最小";
            this.湿度最小.Width = 80;
            // 
            // 湿度最大
            // 
            dataGridViewCellStyle8.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            this.湿度最大.DefaultCellStyle = dataGridViewCellStyle8;
            this.湿度最大.HeaderText = "湿度最大";
            this.湿度最大.Name = "湿度最大";
            this.湿度最大.Width = 80;
            // 
            // 触发报警
            // 
            dataGridViewCellStyle9.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            this.触发报警.DefaultCellStyle = dataGridViewCellStyle9;
            this.触发报警.HeaderText = "触发报警";
            this.触发报警.Name = "触发报警";
            this.触发报警.Width = 80;
            // 
            // 时间
            // 
            dataGridViewCellStyle10.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            this.时间.DefaultCellStyle = dataGridViewCellStyle10;
            this.时间.HeaderText = "时间";
            this.时间.Name = "时间";
            this.时间.Width = 140;
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1416, 671);
            this.Controls.Add(this.btnDeleteAll);
            this.Controls.Add(this.dataGridView1);
            this.Controls.Add(this.btnInsert);
            this.Controls.Add(this.btnRead);
            this.Controls.Add(this.pictureBox2);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.textBoxMaxHum);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.textBoxMaxTmp);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBoxMinHum);
            this.Controls.Add(this.textBoxMinTmp);
            this.Controls.Add(this.chart1);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.groupBox2);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form2";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "串口数据采集";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form2_FormClosing);
            this.Load += new System.EventHandler(this.Form2_Load);
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.Button btnOpen;
        private System.Windows.Forms.ComboBox cbxPortName;
        private System.Windows.Forms.ComboBox cbxPortBaud;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.ComboBox comboBoxCheck;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox comboBoxStop;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.OpenFileDialog saveFileDialog1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox comboBoxBits;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart1;
        private System.Windows.Forms.TextBox textBoxMinTmp;
        private System.Windows.Forms.TextBox textBoxMinHum;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBoxMaxTmp;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox textBoxMaxHum;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.Button btnRead;
        private System.Windows.Forms.Button btnInsert;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.Button btnDeleteAll;
        private System.Windows.Forms.DataGridViewTextBoxColumn 序号;
        private System.Windows.Forms.DataGridViewTextBoxColumn 温度;
        private System.Windows.Forms.DataGridViewTextBoxColumn 湿度;
        private System.Windows.Forms.DataGridViewTextBoxColumn 温度最小;
        private System.Windows.Forms.DataGridViewTextBoxColumn 温度最大;
        private System.Windows.Forms.DataGridViewTextBoxColumn 湿度最小;
        private System.Windows.Forms.DataGridViewTextBoxColumn 湿度最大;
        private System.Windows.Forms.DataGridViewTextBoxColumn 触发报警;
        private System.Windows.Forms.DataGridViewTextBoxColumn 时间;
    }
}