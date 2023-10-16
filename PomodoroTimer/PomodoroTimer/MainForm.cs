using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Net.NetworkInformation;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Net.Mime.MediaTypeNames;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace PomodoroTimer
{
    public partial class MainForm : Form
    {
        // マクロ定義
        public const int STATUS_STOP    = 0;
        public const int STATUS_START   = 1;
        public const int STATUS_REST    = 2;
        public const int STATUS_RESTART = 3;
        public const string WINDOW_TITLE = "Pomodoro Timer";

        delegate void UpdateDisplayTimeLabelDelegate();
        System.Timers.Timer timer = new System.Timers.Timer(1000);
        int remainingSeconds   = 0;
        int exStatus           = STATUS_STOP;

        public MainForm()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // 画面の右下に表示
            this.Left = System.Windows.Forms.Screen.PrimaryScreen.Bounds.Width - this.Size.Width;
            this.Top = System.Windows.Forms.Screen.PrimaryScreen.Bounds.Height - this.Size.Height * 2;

            // タイマーの設定
            timer.Elapsed += new System.Timers.ElapsedEventHandler(OnElapsed);

            // コンボボックスに値を追加
            for (int i = 1; i <= 60; i++) {
                WorkTimeComboBox.Items.Add(i);
                RestTimeComboBox.Items.Add(i);
            }

            // 初期値を設定
            WorkTimeComboBox.SelectedIndex = WorkTimeComboBox.Items.IndexOf(25);
            RestTimeComboBox.SelectedIndex = WorkTimeComboBox.Items.IndexOf(5);
        }

        private void StartButton_Click(object sender, EventArgs e)
        {
            DialogResult ret;

            if (StartButton.Text == "開始") {
                ret = MessageBox.Show(this, "タイマーを開始しますか？", MainForm.WINDOW_TITLE, MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                if (ret == DialogResult.Yes) {
                    if (remainingSeconds == 0) {
                        InitStatus(STATUS_START);
                    }
                    else {
                        ret = MessageBox.Show(this, "タイマーを再開しますか？", MainForm.WINDOW_TITLE, MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                        if (ret == DialogResult.Yes) {
                            InitStatus(STATUS_RESTART);
                        }
                        else {
                            InitStatus(STATUS_START);
                        }
                    }
                }
            }
            else if (StartButton.Text == "停止") {
                ret = MessageBox.Show(this, "タイマーを停止しますか？", MainForm.WINDOW_TITLE, MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                if (ret == DialogResult.Yes) {
                    InitStatus(STATUS_STOP);
                }     
            }
        }

        private void SettingButton_Click(object sender, EventArgs e)
        {
            if (SettingButton.Text == "▼") {
                SettingButton.Text = "▲";
                this.FormBorderStyle = FormBorderStyle.FixedSingle;
                Size = new Size(this.Size.Width, 120);
                this.Top = this.Top - this.Size.Height + 48;
                
            }
            else if (SettingButton.Text == "▲") {
                SettingButton.Text = "▼";
                this.FormBorderStyle = FormBorderStyle.None;
                Size = new Size(this.Size.Width, 40);
                this.Top = this.Top + this.Size.Height * 2 - 8;
            }
        }

        private void CloseButton_Click(object sender, EventArgs e)
        {
            DialogResult ret;

            ret = MessageBox.Show(this, "アプリを終了しますか？", MainForm.WINDOW_TITLE, MessageBoxButtons.YesNo, MessageBoxIcon.Question);
            if (ret == DialogResult.Yes) {
                this.Close();
            }
        }

        // 作業時間のコンボボックスの値が変更されたとき
        private void WorkTimeComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (remainingSeconds == 0) {
                int workMinutes = (int)WorkTimeComboBox.SelectedItem;
                DisplayTimeLabel.Text = workMinutes.ToString("00") + ":00";
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

            // 残り時間を表示
            remainingSeconds--;
            int workMinutes = remainingSeconds / 60;
            int workSeconds = remainingSeconds % 60;
            DisplayTimeLabel.Text = workMinutes.ToString("00") +  ":" + workSeconds.ToString("00");

            // 残り時間が0になったらタイマーを停止
            if (remainingSeconds == 0) {
                timer.Stop();

                // 休憩時間にする
                if (DisplayStatusLabel.Text == "作業中") {
                    ret = MessageBox.Show(this, "休憩を開始します", MainForm.WINDOW_TITLE, MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
                    if (ret == DialogResult.OK) {
                        InitStatus(STATUS_REST);
                    }
                    else {
                        InitStatus(STATUS_STOP);
                    }              
                }
                // 作業時間にする
                else if (DisplayStatusLabel.Text == "休憩中") {
                    ret = MessageBox.Show(this, "作業を開始します", MainForm.WINDOW_TITLE, MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
                    if (ret == DialogResult.OK) {
                        InitStatus(STATUS_START);
                    }
                    else {
                        InitStatus(STATUS_STOP);
                    }
                }
            }
        }

        private void InitStatus(int nStatus)
        {
            if (nStatus == STATUS_STOP) {
                timer.Stop();
                StartButton.Text = "開始";
                DisplayStatusLabel.Text = "停止";
                DisplayStatusLabel.ForeColor = default;
                WorkTimeComboBox.Enabled = true;
                RestTimeComboBox.Enabled = true;
                CloseButton.Enabled = true; 
            }
            else if (nStatus == STATUS_START) {
                int workMinutes = (int)WorkTimeComboBox.SelectedItem;

                exStatus = STATUS_START;
                remainingSeconds = workMinutes * 60;
                timer.Start();
                StartButton.Text = "停止";
                DisplayStatusLabel.Text = "作業中";
                DisplayTimeLabel.Text = workMinutes.ToString("00") + ":00";
                DisplayStatusLabel.ForeColor = Color.Red;
                WorkTimeComboBox.Enabled = false;
                RestTimeComboBox.Enabled = false;
                CloseButton.Enabled = false;
            }
            else if (nStatus == STATUS_REST) {
                int restMinutes = (int)RestTimeComboBox.SelectedItem;

                exStatus = STATUS_REST;
                remainingSeconds = restMinutes * 60;
                timer.Start();
                DisplayStatusLabel.Text = "休憩中";
                DisplayTimeLabel.Text = restMinutes.ToString("00") + ":00";
                DisplayStatusLabel.ForeColor = Color.Lime;
            }
            else if (nStatus == STATUS_RESTART) {
                timer.Start();
                StartButton.Text = "停止";

                if (exStatus == STATUS_START) {
                    DisplayStatusLabel.Text = "作業中";
                    DisplayStatusLabel.ForeColor = Color.Red;
                }
                else if (exStatus == STATUS_REST) {
                    DisplayStatusLabel.Text = "休憩中";
                    DisplayStatusLabel.ForeColor = Color.Lime;
                }

                WorkTimeComboBox.Enabled = false;
                RestTimeComboBox.Enabled = false;
                CloseButton.Enabled = false;
            }
        }

    }
}
