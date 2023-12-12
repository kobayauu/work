namespace WorkSupportTool
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            this.ScheduleButton = new System.Windows.Forms.Button();
            this.RecordButton = new System.Windows.Forms.Button();
            this.PomodoroTimerButton = new System.Windows.Forms.Button();
            this.SubjectComboBox = new System.Windows.Forms.ComboBox();
            this.WorkButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // ScheduleButton
            // 
            this.ScheduleButton.Location = new System.Drawing.Point(3, 2);
            this.ScheduleButton.Name = "ScheduleButton";
            this.ScheduleButton.Size = new System.Drawing.Size(81, 20);
            this.ScheduleButton.TabIndex = 0;
            this.ScheduleButton.Text = "予定表";
            this.ScheduleButton.UseVisualStyleBackColor = true;
            this.ScheduleButton.Click += new System.EventHandler(this.ScheduleButton_Click);
            // 
            // RecordButton
            // 
            this.RecordButton.Location = new System.Drawing.Point(3, 23);
            this.RecordButton.Name = "RecordButton";
            this.RecordButton.Size = new System.Drawing.Size(81, 20);
            this.RecordButton.TabIndex = 1;
            this.RecordButton.Text = "記録開始";
            this.RecordButton.UseVisualStyleBackColor = true;
            this.RecordButton.Click += new System.EventHandler(this.RecordButton_Click);
            // 
            // PomodoroTimerButton
            // 
            this.PomodoroTimerButton.Location = new System.Drawing.Point(85, 2);
            this.PomodoroTimerButton.Name = "PomodoroTimerButton";
            this.PomodoroTimerButton.Size = new System.Drawing.Size(81, 20);
            this.PomodoroTimerButton.TabIndex = 2;
            this.PomodoroTimerButton.Text = "タイマー開始";
            this.PomodoroTimerButton.UseVisualStyleBackColor = true;
            this.PomodoroTimerButton.Click += new System.EventHandler(this.PomodoroTimerButton_Click);
            // 
            // SubjectComboBox
            // 
            this.SubjectComboBox.FormattingEnabled = true;
            this.SubjectComboBox.Location = new System.Drawing.Point(85, 23);
            this.SubjectComboBox.Name = "SubjectComboBox";
            this.SubjectComboBox.Size = new System.Drawing.Size(163, 20);
            this.SubjectComboBox.TabIndex = 3;
            // 
            // WorkButton
            // 
            this.WorkButton.Location = new System.Drawing.Point(167, 2);
            this.WorkButton.Name = "WorkButton";
            this.WorkButton.Size = new System.Drawing.Size(81, 20);
            this.WorkButton.TabIndex = 4;
            this.WorkButton.Text = "出勤切替";
            this.WorkButton.UseVisualStyleBackColor = true;
            this.WorkButton.Click += new System.EventHandler(this.WorkButton_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(254, 46);
            this.Controls.Add(this.WorkButton);
            this.Controls.Add(this.SubjectComboBox);
            this.Controls.Add(this.PomodoroTimerButton);
            this.Controls.Add(this.RecordButton);
            this.Controls.Add(this.ScheduleButton);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "MainForm";
            this.Text = "WorkSupportTool";
            this.TopMost = true;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button ScheduleButton;
        private System.Windows.Forms.Button RecordButton;
        private System.Windows.Forms.Button PomodoroTimerButton;
        private System.Windows.Forms.ComboBox SubjectComboBox;
        private System.Windows.Forms.Button WorkButton;
    }
}