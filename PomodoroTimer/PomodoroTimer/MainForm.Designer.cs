namespace PomodoroTimer
{
    partial class MainForm
    {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージド リソースを破棄する場合は true を指定し、その他の場合は false を指定します。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
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
            this.StartButton = new System.Windows.Forms.Button();
            this.DisplayTimeLabel = new System.Windows.Forms.Label();
            this.DisplayStatusLabel = new System.Windows.Forms.Label();
            this.CloseButton = new System.Windows.Forms.Button();
            this.SettingButton = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.RestTimeComboBox = new System.Windows.Forms.ComboBox();
            this.WorkTimeComboBox = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // StartButton
            // 
            this.StartButton.Font = new System.Drawing.Font("MS UI Gothic", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.StartButton.Location = new System.Drawing.Point(284, 3);
            this.StartButton.Name = "StartButton";
            this.StartButton.Size = new System.Drawing.Size(70, 35);
            this.StartButton.TabIndex = 0;
            this.StartButton.Text = "開始";
            this.StartButton.UseVisualStyleBackColor = true;
            this.StartButton.Click += new System.EventHandler(this.StartButton_Click);
            // 
            // DisplayTimeLabel
            // 
            this.DisplayTimeLabel.AutoSize = true;
            this.DisplayTimeLabel.Font = new System.Drawing.Font("MS UI Gothic", 26.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.DisplayTimeLabel.Location = new System.Drawing.Point(177, 3);
            this.DisplayTimeLabel.Name = "DisplayTimeLabel";
            this.DisplayTimeLabel.Size = new System.Drawing.Size(99, 35);
            this.DisplayTimeLabel.TabIndex = 4;
            this.DisplayTimeLabel.Text = "25:00";
            // 
            // DisplayStatusLabel
            // 
            this.DisplayStatusLabel.AutoSize = true;
            this.DisplayStatusLabel.Font = new System.Drawing.Font("MS UI Gothic", 26.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.DisplayStatusLabel.ForeColor = System.Drawing.SystemColors.ControlText;
            this.DisplayStatusLabel.Location = new System.Drawing.Point(48, 3);
            this.DisplayStatusLabel.Name = "DisplayStatusLabel";
            this.DisplayStatusLabel.Size = new System.Drawing.Size(87, 35);
            this.DisplayStatusLabel.TabIndex = 7;
            this.DisplayStatusLabel.Text = "停止";
            // 
            // CloseButton
            // 
            this.CloseButton.Font = new System.Drawing.Font("MS UI Gothic", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.CloseButton.Location = new System.Drawing.Point(360, 3);
            this.CloseButton.Name = "CloseButton";
            this.CloseButton.Size = new System.Drawing.Size(70, 35);
            this.CloseButton.TabIndex = 8;
            this.CloseButton.Text = "閉じる";
            this.CloseButton.UseVisualStyleBackColor = true;
            this.CloseButton.Click += new System.EventHandler(this.CloseButton_Click);
            // 
            // SettingButton
            // 
            this.SettingButton.Font = new System.Drawing.Font("MS UI Gothic", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.SettingButton.Location = new System.Drawing.Point(7, 3);
            this.SettingButton.Name = "SettingButton";
            this.SettingButton.Size = new System.Drawing.Size(35, 35);
            this.SettingButton.TabIndex = 11;
            this.SettingButton.Text = "▼";
            this.SettingButton.UseVisualStyleBackColor = true;
            this.SettingButton.Click += new System.EventHandler(this.SettingButton_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("MS UI Gothic", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.label4.Location = new System.Drawing.Point(355, 48);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(45, 21);
            this.label4.TabIndex = 22;
            this.label4.Text = "[分]";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("MS UI Gothic", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.label1.Location = new System.Drawing.Point(165, 50);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(45, 21);
            this.label1.TabIndex = 21;
            this.label1.Text = "[分]";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("MS UI Gothic", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.label3.Location = new System.Drawing.Point(216, 50);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(63, 21);
            this.label3.TabIndex = 20;
            this.label3.Text = "休憩：";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("MS UI Gothic", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.label2.Location = new System.Drawing.Point(26, 50);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(63, 21);
            this.label2.TabIndex = 19;
            this.label2.Text = "作業：";
            // 
            // RestTimeComboBox
            // 
            this.RestTimeComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.RestTimeComboBox.Font = new System.Drawing.Font("MS UI Gothic", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.RestTimeComboBox.FormattingEnabled = true;
            this.RestTimeComboBox.Location = new System.Drawing.Point(285, 45);
            this.RestTimeComboBox.Name = "RestTimeComboBox";
            this.RestTimeComboBox.Size = new System.Drawing.Size(64, 29);
            this.RestTimeComboBox.TabIndex = 18;
            // 
            // WorkTimeComboBox
            // 
            this.WorkTimeComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.WorkTimeComboBox.Font = new System.Drawing.Font("MS UI Gothic", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.WorkTimeComboBox.FormattingEnabled = true;
            this.WorkTimeComboBox.Location = new System.Drawing.Point(95, 47);
            this.WorkTimeComboBox.Name = "WorkTimeComboBox";
            this.WorkTimeComboBox.Size = new System.Drawing.Size(64, 29);
            this.WorkTimeComboBox.TabIndex = 17;
            this.WorkTimeComboBox.SelectedIndexChanged += new System.EventHandler(this.WorkTimeComboBox_SelectedIndexChanged);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(440, 40);
            this.ControlBox = false;
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.RestTimeComboBox);
            this.Controls.Add(this.WorkTimeComboBox);
            this.Controls.Add(this.SettingButton);
            this.Controls.Add(this.CloseButton);
            this.Controls.Add(this.DisplayStatusLabel);
            this.Controls.Add(this.DisplayTimeLabel);
            this.Controls.Add(this.StartButton);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "MainForm";
            this.Opacity = 0.6D;
            this.ShowInTaskbar = false;
            this.Text = "Pomodoro Timer";
            this.TopMost = true;
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button StartButton;
        private System.Windows.Forms.Label DisplayTimeLabel;
        private System.Windows.Forms.Label DisplayStatusLabel;
        private System.Windows.Forms.Button CloseButton;
        private System.Windows.Forms.Button SettingButton;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox RestTimeComboBox;
        private System.Windows.Forms.ComboBox WorkTimeComboBox;
    }
}

