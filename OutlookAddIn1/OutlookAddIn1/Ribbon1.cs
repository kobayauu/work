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
using System.Runtime.InteropServices;
using Microsoft.Office.Interop;
using Microsoft.Office.Interop.Outlook;

namespace OutlookAddIn1
{
    public partial class Ribbon1
    {
        // マクロ定義
        const int TIMER_INTERVAL       = 1000;
        const string WINDOW_TITLE      = "Outlook";
        const string STATUS_START      = "開始";
        const string STATUS_RESTART    = "再開";
        const string STATUS_ABORT      = "中断";
        const string STATUS_STOP       = "停止";
        const string STATUS_WORK       = "作業中";
        const string STATUS_REST       = "休憩中";
        const string STATUS_HOME_START = "在宅開始";
        const string STATUS_HOME_END   = "在宅停止";

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
            }
            else if (strBtn == STATUS_STOP) {
                timer.Stop();
                ret = MessageBox.Show("タイマーを停止しますか？", WINDOW_TITLE, MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                if (ret == DialogResult.No) {
                    timer.Start();
                    return;
                }          
            }

            if (ret == DialogResult.Yes) {
                InitStatus(strBtn);
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
                timer.Stop();
                ret = MessageBox.Show("タイマーを一時停止しますか？", WINDOW_TITLE, MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                if (ret == DialogResult.No) {
                    timer.Start();
                    return;
                }
                InitStatus(STATUS_ABORT);
            }
        }

        private void HomeWorkBtn_Click(object sender, RibbonControlEventArgs e)
        {
            DialogResult ret = DialogResult.None;
            string status = homeWorkBtn.Label;

            if (status == STATUS_HOME_START) {
                ret = MessageBox.Show("在宅を開始しますか？", WINDOW_TITLE, MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                if (ret == DialogResult.No) {
                    return;
                }
            }
            else if (status == STATUS_HOME_END) {
                ret = MessageBox.Show("在宅を終了しますか？", WINDOW_TITLE, MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                if (ret == DialogResult.No) {
                    return;
                }               
            }

            if (ret == DialogResult.Yes) {
                InitHomeWork(status);
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

        private void InitHomeWork(string status)
        {
            Microsoft.Office.Interop.Outlook.Application app = new Microsoft.Office.Interop.Outlook.Application();
            NameSpace oNamespase = app.GetNamespace("MAPI");

            oNamespase.Logon(null, null, true, true);

            if (status == STATUS_HOME_START) {
                homeWorkBtn.Label = STATUS_HOME_END;

                _AppointmentItem appItem = appItem = (_AppointmentItem)app.CreateItem(OlItemType.olAppointmentItem);

                appItem.Subject = "在宅(勤務中)";
                appItem.AllDayEvent = true;
                appItem.BusyStatus = OlBusyStatus.olWorkingElsewhere;
                appItem.ReminderSet = false;
                appItem.Importance = OlImportance.olImportanceNormal;
                appItem.Close(OlInspectorClose.olSave);

                Marshal.ReleaseComObject(appItem);
            }
            else if (status == STATUS_HOME_END) {
                homeWorkBtn.Label = STATUS_HOME_START;

                MAPIFolder folder = oNamespase.GetDefaultFolder(OlDefaultFolders.olFolderCalendar);
                Items AllItems = folder.Items;

                AllItems.IncludeRecurrences = true;
                AllItems.Sort("[Start]", Type.Missing);
                string startDate = DateTime.Today.ToString("yyyy/MM/dd");
                string filter = "[Start] >= '" + startDate + " 00:00' AND [Start] <= '" + startDate + " 23:59'";
                Items items = AllItems.Restrict(filter);

                foreach (_AppointmentItem item in items) {
                    if (item.Subject == "在宅(勤務中)") {
                        item.Subject = "在宅(退勤)";
                        item.Save();
                        break;
                    }
                }

                Marshal.ReleaseComObject(items);
                Marshal.ReleaseComObject(AllItems);
                Marshal.ReleaseComObject(folder);
            }

            oNamespase.Logoff();

            Marshal.ReleaseComObject(oNamespase);
            Marshal.ReleaseComObject(app);
        }
    }
}
