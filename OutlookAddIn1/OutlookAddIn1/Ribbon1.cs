using Microsoft.Office.Tools.Ribbon;
using System;
using System.Collections.Generic;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.Remoting.Messaging;
using System.Text;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.Window;

namespace OutlookAddIn1
{
    public partial class Ribbon1
    {
        // マクロ定義
        const int TIMER_INTERVAL    = 1000;
        const string WINDOW_TITLE   = "Outlook";
        const string STATUS_START   = "開始";
        const string STATUS_RESTART = "再開";
        const string STATUS_ABORT   = "中断";
        const string STATUS_STOP    = "停止";
        const string STATUS_WORK    = "作業中";
        const string STATUS_REST    = "休憩中";

        System.Timers.Timer timer = new System.Timers.Timer(TIMER_INTERVAL);
        int remainingSeconds = 0;
        string exStatus      = "";

        private void Ribbon1_Load(object sender, RibbonUIEventArgs e)
        {
            // コンボボックスに値を追加
            RibbonDropDownItem item;
            for (int i = 1; i <= 60; i++) {              
                item = Factory.CreateRibbonDropDownItem();
                item.Label = i.ToString();
                workMinutesList.Items.Add(item);
                item = Factory.CreateRibbonDropDownItem();
                item.Label = i.ToString();
                restMinutesList.Items.Add(item);
            }

            // 初期値を設定
            workMinutesList.SelectedItem = workMinutesList.Items[24];
            restMinutesList.SelectedItem = restMinutesList.Items[4];

            // タイマーの設定
            timer.Elapsed += new System.Timers.ElapsedEventHandler(OnElapsed);
        }

        private void StartButton_Click(object sender, RibbonControlEventArgs e)
        {
            DialogResult ret = DialogResult.None;
            string strBtn = StartBtn.Label;

            // ボタンの表示によって処理を分岐
            if (strBtn == STATUS_START) {
                ret = MessageBox.Show("タイマーを開始しますか？", WINDOW_TITLE, MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                if (ret == DialogResult.No) {
                    return;
                }
                InitStatus(STATUS_START);
            }
            else if (strBtn == STATUS_STOP) {
                timer.Stop();
                ret = MessageBox.Show("タイマーを停止しますか？", WINDOW_TITLE, MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                if (ret == DialogResult.No) {
                    timer.Start();
                    return;
                }
                InitStatus(STATUS_STOP);              
            }
        }

        private void timeStatusBtn_Click(object sender, RibbonControlEventArgs e)
        {
            DialogResult ret = DialogResult.None;
            string strBtn = StartBtn.Label;
            string status = timeStatusBtn.Label;

            if (strBtn == STATUS_START) {
                return;
            }

            status = status.Substring(0, status.IndexOf(" "));
            if (status == STATUS_ABORT) {
                ret = MessageBox.Show("タイマーを再開しますか？", WINDOW_TITLE, MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                if (ret == DialogResult.No) {
                    return;
                }
                InitStatus(STATUS_RESTART);
            }
            else {
                ret = MessageBox.Show("タイマーを一時停止しますか？", WINDOW_TITLE, MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                if (ret == DialogResult.No) {
                    return;
                }
                InitStatus(STATUS_ABORT);
            }
        }

        // タイマーのイベント
        private void OnElapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            string status = timeStatusBtn.Label;
            status = status.Substring(0, status.IndexOf(" "));

            // 残り時間を表示
            remainingSeconds--;
            int workMinutes = remainingSeconds / 60;
            int workSeconds = remainingSeconds % 60;
            timeStatusBtn.Label = exStatus + " " + workMinutes.ToString("00") + ":" + workSeconds.ToString("00");

            // 残り時間が0になったらタイマーを停止
            if (remainingSeconds != 0) {
                return;
            }
            timer.Stop();

            if (status == STATUS_WORK) {
                ShowMessageBox("休憩を開始します", MessageBoxButtons.OK, MessageBoxIcon.Information);
                InitStatus(STATUS_REST);
            }
            else if (status == STATUS_REST) {
                ShowMessageBox("作業を開始します", MessageBoxButtons.OK, MessageBoxIcon.Information);
                InitStatus(STATUS_START);
            }
        }

        private DialogResult ShowMessageBox(string message, MessageBoxButtons btn, MessageBoxIcon icon) {
            DialogResult ret = DialogResult.None;

            MessgeForm messageForm = new MessgeForm(message, btn, icon);
            messageForm.ShowDialog();
            ret = messageForm.ret;
            messageForm.Dispose();

            return ret;
        }

        private void workMinutesList_SelectionChanged(object sender, RibbonControlEventArgs e)
        {
            if (remainingSeconds == 0) {
                int workMinutes = int.Parse(workMinutesList.SelectedItem.Label);
                timeStatusBtn.Label = STATUS_STOP + " " + workMinutes.ToString("00") + ":00";
            }
        }

        private void InitStatus(string status)
        {
            int workMinutes = int.Parse(workMinutesList.SelectedItem.Label);
            int restMinutes = int.Parse(restMinutesList.SelectedItem.Label);

            if (status == STATUS_START) {
                remainingSeconds = workMinutes * 60;
                          
                StartBtn.Label = STATUS_STOP;
                StartBtn.Image = Properties.Resources.player_button04_teishi;
                timeStatusBtn.Image = Properties.Resources.player_button05_ichijiteishi;
                workMinutesList.Enabled = false;
                restMinutesList.Enabled = false;
                
                exStatus = STATUS_WORK;

                timer.Start();
            }
            else if (status == STATUS_RESTART) {
                timeStatusBtn.Label = timeStatusBtn.Label.Replace(STATUS_ABORT, exStatus);
                timeStatusBtn.Image = Properties.Resources.player_button05_ichijiteishi;

                timer.Start();
            }
            else if (status == STATUS_ABORT) {               
                timeStatusBtn.Label = timeStatusBtn.Label.Replace(exStatus, STATUS_ABORT);
                timeStatusBtn.Image = Properties.Resources.player_button06_tsugi;

                timer.Stop();
            }
            else if (status == STATUS_STOP) {
                StartBtn.Label = STATUS_START;
                StartBtn.Image = Properties.Resources.player_button01_saisei;
                timeStatusBtn.Label = STATUS_STOP + " " + workMinutes.ToString("00") + ":00";
                timeStatusBtn.Image = null;

                workMinutesList.Enabled = true;
                restMinutesList.Enabled = true;

                timer.Stop();
            }
            else if (status == STATUS_REST) {               
                remainingSeconds = restMinutes * 60;

                exStatus = STATUS_REST;

                timer.Start();
            }
        }
    }
}
