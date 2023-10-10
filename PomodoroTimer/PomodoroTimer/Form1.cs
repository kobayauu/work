using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace PomodoroTimer
{
    public partial class Form1 : Form
    {
        System.Timers.Timer timer;
        delegate void UpdateDisplayTimeLabelDelegate();
        int workSeconds = 0;
        int workMinutes = 0;
        bool isWorkTime = false;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            int w = System.Windows.Forms.Screen.PrimaryScreen.Bounds.Width;
            this.Left = w - 460;
            this.Top = 0;

            for (int i = 1; i <= 60; i++) {
                WorkTimeComboBox.Items.Add(i);
                RestTimeComboBox.Items.Add(i);
            }

            WorkTimeComboBox.SelectedIndex = 24;
            RestTimeComboBox.SelectedIndex = 4;

            timer = new System.Timers.Timer(1000);
            timer.Elapsed += new System.Timers.ElapsedEventHandler(OnElapsed);
        }

        private void StartButton_Click(object sender, EventArgs e)
        {
            if (StartButton.Text == "スタート") {
                if (MessageBox.Show(this, "スタートしますか？", "Pomodoro Timer", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.No) {
                    return;
                }

                workMinutes = 0;
                workSeconds = 0;
                isWorkTime = true;
                timer.Start();
                StartButton.Text = "ストップ";
                DisplayStatusLabel.Text = "作業中";
                DisplayStatusLabel.ForeColor = Color.Red;

                WorkTimeComboBox.Enabled = false;
                RestTimeComboBox.Enabled = false;
                CloseButton.Enabled = false;
            }
            else if (StartButton.Text == "ストップ") {
                if (MessageBox.Show(this, "ストップしますか？", "Pomodoro Timer", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.No)
                {
                    return;
                }

                isWorkTime = false;
                timer.Stop();
                StartButton.Text = "スタート";
                DisplayStatusLabel.Text = "停止";
                DisplayStatusLabel.ForeColor = default;

                WorkTimeComboBox.Enabled = true;
                RestTimeComboBox.Enabled = true;
                CloseButton.Enabled = true;
            }

        }

        private void OnElapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            this.Invoke(new UpdateDisplayTimeLabelDelegate(this.UpdateDisplayTimeLabel));
        }

        private void UpdateDisplayTimeLabel()
        {
            // 作業時間になったら休憩時間にする
            if (isWorkTime == true) {
                if (workMinutes.ToString() == WorkTimeComboBox.SelectedItem.ToString()) {
                    timer.Stop();
                    isWorkTime = false;                
                    MessageBox.Show(this, "休憩開始です", "Pomodoro Timer", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    DisplayStatusLabel.Text = "休憩中";
                    DisplayStatusLabel.ForeColor = Color.Lime;
                    workMinutes = 0;
                    workSeconds = 0;
                    timer.Start();
                }
            }
            else {
                // 休憩時間になったら作業時間にする
                if (workMinutes.ToString() == WorkTimeComboBox.SelectedItem.ToString()) {
                    timer.Stop();
                    isWorkTime = true;                    
                    MessageBox.Show(this, "作業開始です", "Pomodoro Timer", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    DisplayStatusLabel.Text = "作業中";
                    DisplayStatusLabel.ForeColor = Color.Red;
                    workMinutes = 0;
                    workSeconds = 0;
                    timer.Start();
                }
            }

            // 60秒経過したら分を加算
            if (workSeconds == 60) {
                workSeconds = 0;
                workMinutes++;
            }

            DisplayTimeLabel.Text = workMinutes.ToString("00") + ":"+ workSeconds.ToString("00");
            workSeconds++;
        }

        private void CloseButton_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show(this, "アプリを閉じますか？", "Pomodoro Timer", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
            {
                this.Close();
            }
        }
    }
}
