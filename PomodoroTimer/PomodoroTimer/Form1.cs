using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
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
        // ステータス
        const int STATUS_STOP  = 0;
        const int STATUS_START = 1;
        const int STATUS_REST  = 2;

        Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
        System.Timers.Timer timer = new System.Timers.Timer(500);
        delegate void UpdateDisplayTimeLabelDelegate();

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // 画面の右上に表示
            this.Left = System.Windows.Forms.Screen.PrimaryScreen.Bounds.Width - 450;
            this.Top = 0;

            // コンボボックスに値を追加
            for (int i = 1; i <= 60; i++) {
                WorkTimeComboBox.Items.Add(i);
                RestTimeComboBox.Items.Add(i);
            }
            WorkTimeComboBox.SelectedIndex = 24;
            RestTimeComboBox.SelectedIndex = 4;

            // タイマーの設定
            timer.Elapsed += new System.Timers.ElapsedEventHandler(OnElapsed);
        }

        private void StartButton_Click(object sender, EventArgs e)
        {
            DialogResult ret;

            if (StartButton.Text == "スタート") {
                ret = MessageBox.Show(this, "スタートしますか？", "Pomodoro Timer", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                if (ret == DialogResult.Yes) {
                    InitStatus(STATUS_START);
                }
                
            }
            else if (StartButton.Text == "ストップ") {
                ret = MessageBox.Show(this, "ストップしますか？", "Pomodoro Timer", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                if (ret == DialogResult.Yes) {
                    InitStatus(STATUS_STOP);
                }
            }

        }

        // タイマーのイベント
        private void OnElapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            this.Invoke(new UpdateDisplayTimeLabelDelegate(this.UpdateDisplayTimeLabel));
        }

        private void UpdateDisplayTimeLabel()
        {
            DialogResult ret;
            TimeSpan spendTime = stopwatch.Elapsed;

            DisplayTimeLabel.Text = spendTime.ToString(@"mm\:ss");

            // 作業時間になったら休憩時間にする
            if (DisplayStatusLabel.Text == "作業中") {
                if (spendTime.Minutes.ToString() != WorkTimeComboBox.SelectedItem.ToString()) {
                    return;
                }
                stopwatch.Stop();
                timer.Stop();

                ret = MessageBox.Show(this, "休憩開始です", "Pomodoro Timer", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
                if (ret == DialogResult.OK) {
                    InitStatus(STATUS_REST);
                }
                else {
                    InitStatus(STATUS_STOP);
                    return;
                }              
            }
            // 休憩時間になったら作業時間にする
            else if (DisplayStatusLabel.Text == "休憩中") {   
                if (spendTime.Minutes.ToString() != RestTimeComboBox.SelectedItem.ToString()) {
                    return;
                }
                stopwatch.Stop();
                timer.Stop();

                ret = MessageBox.Show(this, "作業開始です", "Pomodoro Timer", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
                if (ret == DialogResult.OK) {
                    InitStatus(STATUS_START);
                }
                else {
                    InitStatus(STATUS_STOP);
                    return;
                }
            }
        }

        private void CloseButton_Click(object sender, EventArgs e)
        {
            DialogResult ret;
            ret = MessageBox.Show(this, "アプリを閉じますか？", "Pomodoro Timer", MessageBoxButtons.YesNo, MessageBoxIcon.Question);

            if (ret == DialogResult.Yes) {
                this.Close();
            }
        }

        private void InitStatus(int nStatus)
        {
            if (nStatus == STATUS_STOP) {
                stopwatch.Stop();
                timer.Stop();
                StartButton.Text = "スタート";
                DisplayStatusLabel.Text = "停止";
                DisplayStatusLabel.ForeColor = default;

                WorkTimeComboBox.Enabled = true;
                RestTimeComboBox.Enabled = true;
                CloseButton.Enabled = true;
            }
            else if (nStatus == STATUS_START) {
                stopwatch.Restart();
                timer.Start();
                StartButton.Text = "ストップ";
                DisplayStatusLabel.Text = "作業中";
                DisplayTimeLabel.Text = "00:00";
                DisplayStatusLabel.ForeColor = Color.Red;

                WorkTimeComboBox.Enabled = false;
                RestTimeComboBox.Enabled = false;
                CloseButton.Enabled = false;
            }
            else if (nStatus == STATUS_REST) {
                stopwatch.Restart();
                timer.Start();
                DisplayStatusLabel.Text = "休憩中";
                DisplayTimeLabel.Text = "00:00";
                DisplayStatusLabel.ForeColor = Color.Lime;
            }

        }
    }
}
