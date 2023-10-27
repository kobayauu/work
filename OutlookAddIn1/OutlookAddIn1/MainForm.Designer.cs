namespace OutlookAddIn1
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
        protected override void Dispose(bool disposing) {
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
        private void InitializeComponent() {
            this.pomodoroTimerButton = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.recordButton = new System.Windows.Forms.Button();
            this.subjectComboBox = new System.Windows.Forms.ComboBox();
            this.categoryComboBox = new System.Windows.Forms.ComboBox();
            this.scheduleButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // pomodoroTimerButton
            // 
            this.pomodoroTimerButton.Font = new System.Drawing.Font("MS UI Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.pomodoroTimerButton.Location = new System.Drawing.Point(103, 0);
            this.pomodoroTimerButton.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.pomodoroTimerButton.Name = "pomodoroTimerButton";
            this.pomodoroTimerButton.Size = new System.Drawing.Size(90, 20);
            this.pomodoroTimerButton.TabIndex = 0;
            this.pomodoroTimerButton.Text = "タイマー開始";
            this.pomodoroTimerButton.UseVisualStyleBackColor = true;
            this.pomodoroTimerButton.Click += new System.EventHandler(this.pomodoroTimerButton_Click);
            this.pomodoroTimerButton.MouseEnter += new System.EventHandler(this.pomodoroTimerButton_MouseEnter);
            this.pomodoroTimerButton.MouseLeave += new System.EventHandler(this.pomodoroTimerButton_MouseLeave);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("MS UI Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.label4.Location = new System.Drawing.Point(190, 23);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(39, 12);
            this.label4.TabIndex = 22;
            this.label4.Text = "PJ No.";
            this.label4.MouseEnter += new System.EventHandler(this.label4_MouseEnter);
            this.label4.MouseLeave += new System.EventHandler(this.label4_MouseLeave);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("MS UI Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.label3.Location = new System.Drawing.Point(3, 23);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(29, 12);
            this.label3.TabIndex = 21;
            this.label3.Text = "件名";
            this.label3.MouseEnter += new System.EventHandler(this.label3_MouseEnter);
            this.label3.MouseLeave += new System.EventHandler(this.label3_MouseLeave);
            // 
            // recordButton
            // 
            this.recordButton.Font = new System.Drawing.Font("MS UI Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.recordButton.Location = new System.Drawing.Point(5, 0);
            this.recordButton.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.recordButton.Name = "recordButton";
            this.recordButton.Size = new System.Drawing.Size(90, 20);
            this.recordButton.TabIndex = 24;
            this.recordButton.Text = "記録開始";
            this.recordButton.UseVisualStyleBackColor = true;
            this.recordButton.Click += new System.EventHandler(this.recordButton_Click);
            this.recordButton.MouseEnter += new System.EventHandler(this.recordButton_MouseEnter);
            this.recordButton.MouseLeave += new System.EventHandler(this.recordButton_MouseLeave);
            // 
            // subjectComboBox
            // 
            this.subjectComboBox.Font = new System.Drawing.Font("MS UI Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.subjectComboBox.FormattingEnabled = true;
            this.subjectComboBox.Location = new System.Drawing.Point(32, 20);
            this.subjectComboBox.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.subjectComboBox.Name = "subjectComboBox";
            this.subjectComboBox.Size = new System.Drawing.Size(150, 20);
            this.subjectComboBox.TabIndex = 25;
            this.subjectComboBox.MouseEnter += new System.EventHandler(this.subjectComboBox_MouseEnter);
            this.subjectComboBox.MouseLeave += new System.EventHandler(this.subjectComboBox_MouseLeave);
            // 
            // categoryComboBox
            // 
            this.categoryComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.categoryComboBox.Font = new System.Drawing.Font("MS UI Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.categoryComboBox.FormattingEnabled = true;
            this.categoryComboBox.Location = new System.Drawing.Point(233, 20);
            this.categoryComboBox.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.categoryComboBox.Name = "categoryComboBox";
            this.categoryComboBox.Size = new System.Drawing.Size(150, 20);
            this.categoryComboBox.TabIndex = 26;
            this.categoryComboBox.MouseEnter += new System.EventHandler(this.categoryComboBox_MouseEnter);
            this.categoryComboBox.MouseLeave += new System.EventHandler(this.categoryComboBox_MouseLeave);
            // 
            // scheduleButton
            // 
            this.scheduleButton.Font = new System.Drawing.Font("MS UI Gothic", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.scheduleButton.Location = new System.Drawing.Point(201, 0);
            this.scheduleButton.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.scheduleButton.Name = "scheduleButton";
            this.scheduleButton.Size = new System.Drawing.Size(90, 20);
            this.scheduleButton.TabIndex = 31;
            this.scheduleButton.Text = "予定表";
            this.scheduleButton.UseVisualStyleBackColor = true;
            this.scheduleButton.Click += new System.EventHandler(this.scheduleButton_Click);
            this.scheduleButton.MouseEnter += new System.EventHandler(this.scheduleButton_MouseEnter);
            this.scheduleButton.MouseLeave += new System.EventHandler(this.scheduleButton_MouseLeave);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(390, 40);
            this.Controls.Add(this.scheduleButton);
            this.Controls.Add(this.recordButton);
            this.Controls.Add(this.categoryComboBox);
            this.Controls.Add(this.subjectComboBox);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.pomodoroTimerButton);
            this.Controls.Add(this.label3);
            this.Font = new System.Drawing.Font("MS UI Gothic", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.MaximizeBox = false;
            this.Name = "MainForm";
            this.Opacity = 0.6D;
            this.ShowInTaskbar = false;
            this.Text = "Pomodoro Timer";
            this.TopMost = true;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.MouseEnter += new System.EventHandler(this.MainForm_MouseEnter);
            this.MouseLeave += new System.EventHandler(this.MainForm_MouseLeave);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button pomodoroTimerButton;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button recordButton;
        private System.Windows.Forms.ComboBox subjectComboBox;
        private System.Windows.Forms.ComboBox categoryComboBox;
        private System.Windows.Forms.Button scheduleButton;
    }
}