namespace CameraCapture
{
    partial class CameraCapture
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
            ReleaseData();
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
            this.captureButton = new System.Windows.Forms.Button();
            this.captureImageBox = new Emgu.CV.UI.ImageBox();
            this.trackBarMin = new System.Windows.Forms.TrackBar();
            this.label3 = new System.Windows.Forms.Label();
            this.textBoxMin = new System.Windows.Forms.TextBox();
            this.textBoxMax = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.trackBarMax = new System.Windows.Forms.TrackBar();
            this.textBoxBubbleLine = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.trackBarBubbleLine = new System.Windows.Forms.TrackBar();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.labelDistance = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.label8 = new System.Windows.Forms.Label();
            this.labelSend = new System.Windows.Forms.Label();
            this.labelStatus = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.buttonConnect = new System.Windows.Forms.Button();
            this.textBoxBaudRate = new System.Windows.Forms.TextBox();
            this.textBoxPort = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.captureImageBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarMin)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarMax)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarBubbleLine)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // captureButton
            // 
            this.captureButton.Location = new System.Drawing.Point(6, 337);
            this.captureButton.Name = "captureButton";
            this.captureButton.Size = new System.Drawing.Size(102, 23);
            this.captureButton.TabIndex = 0;
            this.captureButton.Text = "Start Camera";
            this.captureButton.UseVisualStyleBackColor = true;
            this.captureButton.Click += new System.EventHandler(this.captureButtonClick);
            // 
            // captureImageBox
            // 
            this.captureImageBox.Location = new System.Drawing.Point(6, 19);
            this.captureImageBox.Name = "captureImageBox";
            this.captureImageBox.Size = new System.Drawing.Size(315, 255);
            this.captureImageBox.TabIndex = 1;
            this.captureImageBox.TabStop = false;
            // 
            // trackBarMin
            // 
            this.trackBarMin.Location = new System.Drawing.Point(99, 224);
            this.trackBarMin.Maximum = 255;
            this.trackBarMin.Name = "trackBarMin";
            this.trackBarMin.Size = new System.Drawing.Size(230, 45);
            this.trackBarMin.TabIndex = 3;
            this.trackBarMin.TickFrequency = 5;
            this.trackBarMin.ValueChanged += new System.EventHandler(this.trackBarMin_ValueChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(16, 229);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(79, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Min gray colour";
            // 
            // textBoxMin
            // 
            this.textBoxMin.Location = new System.Drawing.Point(335, 226);
            this.textBoxMin.Name = "textBoxMin";
            this.textBoxMin.Size = new System.Drawing.Size(58, 20);
            this.textBoxMin.TabIndex = 5;
            this.textBoxMin.Text = "0";
            this.textBoxMin.TextChanged += new System.EventHandler(this.textBoxMin_TextChanged);
            // 
            // textBoxMax
            // 
            this.textBoxMax.Location = new System.Drawing.Point(335, 274);
            this.textBoxMax.Name = "textBoxMax";
            this.textBoxMax.Size = new System.Drawing.Size(58, 20);
            this.textBoxMax.TabIndex = 8;
            this.textBoxMax.Text = "200";
            this.textBoxMax.TextChanged += new System.EventHandler(this.textBoxMax_TextChanged);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(16, 277);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(82, 13);
            this.label4.TabIndex = 7;
            this.label4.Text = "Max gray colour";
            // 
            // trackBarMax
            // 
            this.trackBarMax.Location = new System.Drawing.Point(99, 272);
            this.trackBarMax.Maximum = 255;
            this.trackBarMax.Name = "trackBarMax";
            this.trackBarMax.Size = new System.Drawing.Size(230, 45);
            this.trackBarMax.TabIndex = 6;
            this.trackBarMax.TickFrequency = 5;
            this.trackBarMax.Value = 200;
            this.trackBarMax.ValueChanged += new System.EventHandler(this.trackBarMax_ValueChanged);
            // 
            // textBoxBubbleLine
            // 
            this.textBoxBubbleLine.Location = new System.Drawing.Point(19, 182);
            this.textBoxBubbleLine.Name = "textBoxBubbleLine";
            this.textBoxBubbleLine.Size = new System.Drawing.Size(58, 20);
            this.textBoxBubbleLine.TabIndex = 11;
            this.textBoxBubbleLine.Text = "0";
            this.textBoxBubbleLine.TextChanged += new System.EventHandler(this.textBoxBubbleLine_TextChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(16, 22);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(59, 13);
            this.label5.TabIndex = 10;
            this.label5.Text = "Bubble line";
            // 
            // trackBarBubbleLine
            // 
            this.trackBarBubbleLine.Location = new System.Drawing.Point(32, 38);
            this.trackBarBubbleLine.Maximum = 119;
            this.trackBarBubbleLine.Name = "trackBarBubbleLine";
            this.trackBarBubbleLine.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.trackBarBubbleLine.Size = new System.Drawing.Size(45, 138);
            this.trackBarBubbleLine.TabIndex = 9;
            this.trackBarBubbleLine.TickFrequency = 10;
            this.trackBarBubbleLine.ValueChanged += new System.EventHandler(this.trackBarBubbleLine_ValueChanged);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(93, 47);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(160, 120);
            this.pictureBox1.TabIndex = 12;
            this.pictureBox1.TabStop = false;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.captureImageBox);
            this.groupBox1.Controls.Add(this.captureButton);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(404, 366);
            this.groupBox1.TabIndex = 13;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Original Image";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.labelDistance);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.pictureBox1);
            this.groupBox2.Controls.Add(this.trackBarMin);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.textBoxBubbleLine);
            this.groupBox2.Controls.Add(this.textBoxMin);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.trackBarMax);
            this.groupBox2.Controls.Add(this.trackBarBubbleLine);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.textBoxMax);
            this.groupBox2.Location = new System.Drawing.Point(422, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(404, 366);
            this.groupBox2.TabIndex = 14;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Converted Image";
            // 
            // labelDistance
            // 
            this.labelDistance.AutoSize = true;
            this.labelDistance.Location = new System.Drawing.Point(220, 185);
            this.labelDistance.Name = "labelDistance";
            this.labelDistance.Size = new System.Drawing.Size(0, 13);
            this.labelDistance.TabIndex = 14;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(90, 185);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(124, 13);
            this.label1.TabIndex = 13;
            this.label1.Text = "Distance to Bubble tube:";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.label8);
            this.groupBox3.Controls.Add(this.labelSend);
            this.groupBox3.Controls.Add(this.labelStatus);
            this.groupBox3.Controls.Add(this.label7);
            this.groupBox3.Controls.Add(this.buttonConnect);
            this.groupBox3.Controls.Add(this.textBoxBaudRate);
            this.groupBox3.Controls.Add(this.textBoxPort);
            this.groupBox3.Controls.Add(this.label6);
            this.groupBox3.Controls.Add(this.label2);
            this.groupBox3.Location = new System.Drawing.Point(832, 12);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(193, 366);
            this.groupBox3.TabIndex = 15;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Communication with Arduino";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(6, 140);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(107, 13);
            this.label8.TabIndex = 5;
            this.label8.Text = "Last send to Arduino:";
            // 
            // labelSend
            // 
            this.labelSend.AutoSize = true;
            this.labelSend.Location = new System.Drawing.Point(109, 140);
            this.labelSend.Name = "labelSend";
            this.labelSend.Size = new System.Drawing.Size(10, 13);
            this.labelSend.TabIndex = 4;
            this.labelSend.Text = "-";
            // 
            // labelStatus
            // 
            this.labelStatus.AutoSize = true;
            this.labelStatus.Location = new System.Drawing.Point(109, 113);
            this.labelStatus.Name = "labelStatus";
            this.labelStatus.Size = new System.Drawing.Size(78, 13);
            this.labelStatus.TabIndex = 4;
            this.labelStatus.Text = "Not connected";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(6, 113);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(40, 13);
            this.label7.TabIndex = 3;
            this.label7.Text = "Status:";
            // 
            // buttonConnect
            // 
            this.buttonConnect.Location = new System.Drawing.Point(112, 72);
            this.buttonConnect.Name = "buttonConnect";
            this.buttonConnect.Size = new System.Drawing.Size(75, 23);
            this.buttonConnect.TabIndex = 2;
            this.buttonConnect.Text = "Connect";
            this.buttonConnect.UseVisualStyleBackColor = true;
            this.buttonConnect.Click += new System.EventHandler(this.buttonConnect_Click);
            // 
            // textBoxBaudRate
            // 
            this.textBoxBaudRate.Location = new System.Drawing.Point(95, 46);
            this.textBoxBaudRate.Name = "textBoxBaudRate";
            this.textBoxBaudRate.Size = new System.Drawing.Size(92, 20);
            this.textBoxBaudRate.TabIndex = 1;
            this.textBoxBaudRate.Text = "9600";
            // 
            // textBoxPort
            // 
            this.textBoxPort.Location = new System.Drawing.Point(95, 22);
            this.textBoxPort.Name = "textBoxPort";
            this.textBoxPort.Size = new System.Drawing.Size(92, 20);
            this.textBoxPort.TabIndex = 1;
            this.textBoxPort.Text = "COM6";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(6, 49);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(58, 13);
            this.label6.TabIndex = 0;
            this.label6.Text = "Baud Rate";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 25);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(26, 13);
            this.label2.TabIndex = 0;
            this.label2.Text = "Port";
            // 
            // CameraCapture
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1038, 395);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "CameraCapture";
            this.Text = "Bubble Vision";
            ((System.ComponentModel.ISupportInitialize)(this.captureImageBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarMin)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarMax)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarBubbleLine)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button captureButton;
        private Emgu.CV.UI.ImageBox captureImageBox;
        private System.Windows.Forms.TrackBar trackBarMin;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBoxMin;
        private System.Windows.Forms.TextBox textBoxMax;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TrackBar trackBarMax;
        private System.Windows.Forms.TextBox textBoxBubbleLine;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TrackBar trackBarBubbleLine;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label labelDistance;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button buttonConnect;
        private System.Windows.Forms.TextBox textBoxBaudRate;
        private System.Windows.Forms.TextBox textBoxPort;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label labelStatus;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label labelSend;



    }
}

