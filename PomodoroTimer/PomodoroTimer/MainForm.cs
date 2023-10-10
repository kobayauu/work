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
    public partial class MainForm : Form
    {
        // ステータス
        const int STATUS_STOP  = 0;
        const int STATUS_START = 1;
        const int STATUS_REST  = 2;

        Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
        System.Timers.Timer timer = new System.Timers.Timer(500);
        int SettingWorkTime = 25;
        int SettingRestTime = 5;
        delegate void UpdateDisplayTimeLabelDelegate();

        public MainForm()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // 画面の右上に表示
            this.Left = System.Windows.Forms.Screen.PrimaryScreen.Bounds.Width - 745;
            this.Top = System.Windows.Forms.Screen.PrimaryScreen.Bounds.Height - 40;

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

        private void SettingButton_Click(object sender, EventArgs e)
        {
            // 設定画面を表示
            SettingForm form2 = new SettingForm();
            form2.SettingWorkTime = SettingWorkTime;
            form2.SettingRestTime = SettingRestTime;
            form2.SettingFormBorderStyle = (int)this.FormBorderStyle;
            form2.ShowDialog();

            // 設定値を反映
            SettingWorkTime = form2.SettingWorkTime;
            SettingRestTime = form2.SettingRestTime;
            if (form2.SettingFormBorderStyle == 0) {
                this.FormBorderStyle = FormBorderStyle.None;
            }
            else {
                this.FormBorderStyle = FormBorderStyle.FixedSingle;
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
                if (spendTime.Minutes.ToString() != SettingWorkTime.ToString()) {
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
                }              
            }
            // 休憩時間になったら作業時間にする
            else if (DisplayStatusLabel.Text == "休憩中") {   
                if (spendTime.Minutes.ToString() != SettingRestTime.ToString()) {
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
                }
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
                SettingButton.Enabled = true;
                CloseButton.Enabled = true;
            }
            else if (nStatus == STATUS_START) {
                stopwatch.Restart();
                timer.Start();
                StartButton.Text = "ストップ";
                DisplayStatusLabel.Text = "作業中";
                DisplayTimeLabel.Text = "00:00";
                DisplayStatusLabel.ForeColor = Color.Red;
                SettingButton.Enabled = false;
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
