namespace PomodoroTimer
{
    partial class Form1
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
            this.WorkTimeComboBox = new System.Windows.Forms.ComboBox();
            this.RestTimeComboBox = new System.Windows.Forms.ComboBox();
            this.DisplayTimeLabel = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.DisplayStatusLabel = new System.Windows.Forms.Label();
            this.CloseButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // StartButton
            // 
            this.StartButton.Font = new System.Drawing.Font("MS UI Gothic", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.StartButton.Location = new System.Drawing.Point(318, 17);
            this.StartButton.Name = "StartButton";
            this.StartButton.Size = new System.Drawing.Size(108, 40);
            this.StartButton.TabIndex = 0;
            this.StartButton.Text = "スタート";
            this.StartButton.UseVisualStyleBackColor = true;
            this.StartButton.Click += new System.EventHandler(this.StartButton_Click);
            // 
            // WorkTimeComboBox
            // 
            this.WorkTimeComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.WorkTimeComboBox.Font = new System.Drawing.Font("MS UI Gothic", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.WorkTimeComboBox.FormattingEnabled = true;
            this.WorkTimeComboBox.Location = new System.Drawing.Point(143, 63);
            this.WorkTimeComboBox.Name = "WorkTimeComboBox";
            this.WorkTimeComboBox.Size = new System.Drawing.Size(64, 29);
            this.WorkTimeComboBox.TabIndex = 2;
            // 
            // RestTimeComboBox
            // 
            this.RestTimeComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.RestTimeComboBox.Font = new System.Drawing.Font("MS UI Gothic", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.RestTimeComboBox.FormattingEnabled = true;
            this.RestTimeComboBox.Location = new System.Drawing.Point(143, 96);
            this.RestTimeComboBox.Name = "RestTimeComboBox";
            this.RestTimeComboBox.Size = new System.Drawing.Size(64, 29);
            this.RestTimeComboBox.TabIndex = 3;
            // 
            // DisplayTimeLabel
            // 
            this.DisplayTimeLabel.AutoSize = true;
            this.DisplayTimeLabel.Font = new System.Drawing.Font("MS UI Gothic", 36F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.DisplayTimeLabel.Location = new System.Drawing.Point(181, 9);
            this.DisplayTimeLabel.Name = "DisplayTimeLabel";
            this.DisplayTimeLabel.Size = new System.Drawing.Size(131, 48);
            this.DisplayTimeLabel.TabIndex = 4;
            this.DisplayTimeLabel.Text = "00:00";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("MS UI Gothic", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.label2.Location = new System.Drawing.Point(32, 66);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(105, 21);
            this.label2.TabIndex = 5;
            this.label2.Text = "作業時間：";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("MS UI Gothic", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.label3.Location = new System.Drawing.Point(32, 101);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(105, 21);
            this.label3.TabIndex = 6;
            this.label3.Text = "休憩時間：";
            // 
            // DisplayStatusLabel
            // 
            this.DisplayStatusLabel.AutoSize = true;
            this.DisplayStatusLabel.Font = new System.Drawing.Font("MS UI Gothic", 36F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.DisplayStatusLabel.ForeColor = System.Drawing.SystemColors.ControlText;
            this.DisplayStatusLabel.Location = new System.Drawing.Point(8, 9);
            this.DisplayStatusLabel.Name = "DisplayStatusLabel";
            this.DisplayStatusLabel.Size = new System.Drawing.Size(118, 48);
            this.DisplayStatusLabel.TabIndex = 7;
            this.DisplayStatusLabel.Text = "停止";
            // 
            // CloseButton
            // 
            this.CloseButton.Font = new System.Drawing.Font("MS UI Gothic", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.CloseButton.Location = new System.Drawing.Point(318, 85);
            this.CloseButton.Name = "CloseButton";
            this.CloseButton.Size = new System.Drawing.Size(108, 40);
            this.CloseButton.TabIndex = 8;
            this.CloseButton.Text = "閉じる";
            this.CloseButton.UseVisualStyleBackColor = true;
            this.CloseButton.Click += new System.EventHandler(this.CloseButton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("MS UI Gothic", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.label1.Location = new System.Drawing.Point(213, 66);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(45, 21);
            this.label1.TabIndex = 9;
            this.label1.Text = "[分]";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("MS UI Gothic", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.label4.Location = new System.Drawing.Point(213, 99);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(45, 21);
            this.label4.TabIndex = 10;
            this.label4.Text = "[分]";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(444, 141);
            this.ControlBox = false;
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.CloseButton);
            this.Controls.Add(this.DisplayStatusLabel);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.DisplayTimeLabel);
            this.Controls.Add(this.RestTimeComboBox);
            this.Controls.Add(this.WorkTimeComboBox);
            this.Controls.Add(this.StartButton);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "Form1";
            this.Opacity = 0.5D;
            this.ShowInTaskbar = false;
            this.Text = "Pomodoro Timer";
            this.TopMost = true;
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button StartButton;
        private System.Windows.Forms.ComboBox WorkTimeComboBox;
        private System.Windows.Forms.ComboBox RestTimeComboBox;
        private System.Windows.Forms.Label DisplayTimeLabel;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label DisplayStatusLabel;
        private System.Windows.Forms.Button CloseButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label4;
    }
}

