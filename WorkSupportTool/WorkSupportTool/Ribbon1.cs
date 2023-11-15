using Microsoft.Office.Tools.Ribbon;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.Office.Interop.Outlook;
using Microsoft.Toolkit.Uwp.Notifications;

namespace WorkSupportTool
{
    public partial class Ribbon1
    {
        CtrlOutlook ctrlOutlook = new CtrlOutlook();
        CtrlFile ctrlFile = new CtrlFile();

        System.Timers.Timer pomodoroTimer = new System.Timers.Timer(Macros.POMODORO_TIMER_INTERVAL);
        int remainingSeconds = 0;
        string pomodoroTimerStatus = Macros.STATUS_TIMER_STOP;

        System.Timers.Timer recordTimer = new System.Timers.Timer(Macros.RECORD_TIMER_INTERVAL);
        DateTime workStartTime = DateTime.Now;
        DateTime workEndTime = DateTime.Now;
        bool recordFlag = false;
        bool autoRecordFlag = false;
        

        private void Ribbon1_Load(object sender, RibbonUIEventArgs e)
        {
            RibbonDropDownItem item;

            // 予定表読込
            UpdateSubject();

            // 予定表チェックタイマー設定
            recordTimer.Elapsed += new System.Timers.ElapsedEventHandler(OnElapsed_recordTimer);
            recordTimer.Start();

            // ポモードロタイマー設定
            pomodoroTimer.Elapsed += new System.Timers.ElapsedEventHandler(OnElapsed_pomodoroTimer);

            // コンボボックスに値を追加
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
        }

        private void recordButton_Click(object sender, RibbonControlEventArgs e)
        {
            RecordWork();
        }

        private void scheduleButton_Click(object sender, RibbonControlEventArgs e)
        {
            ScheduleForm scheduleForm = new ScheduleForm();

            // 予定表表示
            scheduleForm.ShowDialog();

            // 予定表読込
            subjectComboBox.Items.Clear();
            UpdateSubject();
        }

        private void WorkButton_Click(object sender, RibbonControlEventArgs e)
        {
            ctrlOutlook.ChangeWorkStatus();
        }

        private void homeWorkButton_Click(object sender, RibbonControlEventArgs e)
        {
            bool ishomeFlag = false;
            bool changeFlag = false;
            string todayDate = DateTime.Today.ToString("yyyy/MM/dd");
            string doingHomeWork = "在宅(勤務中)";
            string planHomeWork = "在宅(予定)";
            string startHomeWork = "在宅(開始)";
            string endHomeWork = "在宅(終了)";
            string msgID = "";
            CtrlOutlook.scheduleSetting settingSchedule = new CtrlOutlook.scheduleSetting();
            CtrlOutlook.scheduleSetting[] gettingSchedule = new CtrlOutlook.scheduleSetting[0];

            // 初期化
            settingSchedule.start = DateTime.Now;
            settingSchedule.end = DateTime.Now;
            settingSchedule.allDayEvent = true;
            settingSchedule.busyStatus = OlBusyStatus.olWorkingElsewhere;
            settingSchedule.importance = OlImportance.olImportanceNormal;

            // 
            ctrlOutlook.GetSchedule(todayDate, ref gettingSchedule);
            for (int i = 0; i < gettingSchedule.Length; i++) {
                if (gettingSchedule[i].subject == planHomeWork) {
                    changeFlag = true;
                    break;
                }

                if (gettingSchedule[i].subject == doingHomeWork) {
                    msgID = gettingSchedule[i].location;
                    ishomeFlag = true;
                    break;
                }
            }

            if (ishomeFlag) {
                if (MessageBox.Show("在宅を終了しますか？", "", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes) {
                    settingSchedule.subject = endHomeWork;
                    settingSchedule.location = msgID;
                    ctrlOutlook.ChangeSchedule(todayDate, doingHomeWork, settingSchedule);
                }
            }
            else {
                if (MessageBox.Show("在宅を開始しますか？", "", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes) {
                    settingSchedule.subject = startHomeWork;

                    if (changeFlag) {
                        ctrlOutlook.ChangeSchedule(todayDate, planHomeWork, settingSchedule);
                    }
                    else {
                        ctrlOutlook.SetSchedule(settingSchedule, "");
                    }
                }
            }
        }

        private void pomodoroTimerButton_Click(object sender, RibbonControlEventArgs e)
        {
            if (pomodoroTimerStatus == Macros.STATUS_TIMER_STOP) {
                InitPomodoroStatus(Macros.STATUS_TIMER_WORK);
            }
            else {
                pomodoroTimer.Stop();
                if (MessageBox.Show("タイマーを停止しますか？", "", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes) {
                    InitPomodoroStatus(Macros.STATUS_TIMER_STOP);
                    return;
                }
                pomodoroTimer.Start();
            }
        }

        // 業務記録タイマーのイベント
        private void OnElapsed_recordTimer(object sender, System.Timers.ElapsedEventArgs e)
        {
            string todayDate = DateTime.Today.ToString("yyyy/MM/dd");
            string currentTime = DateTime.Now.ToString("yyyy/MM/dd HH:mm");
            string nowTime = DateTime.Now.ToString("H:mm");
            CtrlOutlook.scheduleSetting[] gettingSchedule = new CtrlOutlook.scheduleSetting[0];

            if (!autoRecordFlag) {
                ctrlOutlook.GetSchedule(todayDate, ref gettingSchedule);

                for (int i = 0; i < gettingSchedule.Length; i++) {
                    if ((currentTime != gettingSchedule[i].start.ToString("yyyy/MM/dd HH:mm")) || (gettingSchedule[i].categories == "その他") ) {
                        continue;
                    }

                    // 記録中なら強制的に停止・記録
                    if (recordFlag) {
                        RecordWork(); // 停止・記録
                    }

                    autoRecordFlag = true;
                    subjectComboBox.Text = gettingSchedule[i].subject;
                    workEndTime = gettingSchedule[i].end;
                    RecordWork(); // 開始
                    break;
                }
            }
            else {
                if (currentTime == workEndTime.ToString("yyyy/MM/dd HH:mm")) {
                    autoRecordFlag = false;
                    RecordWork(); // 停止・記録
                }
            }

            // 記録中に休憩時間になったら強制的に停止・記録
            if (recordFlag) {
                string[] lines = new string[0];
                ctrlFile.ReadCSVFile(OutlookAddIn1.Properties.Settings.Default.SETTING_FILE, ref lines);
                for (int i = 0; i < lines.Length; i++) {
                    string[] values = lines[i].Split(',');

                    if (values[0] == "休み時間") {
                        for (int j = 1; j < values.Length; j++) {
                            if (nowTime == values[j]) {
                                autoRecordFlag = false;
                                RecordWork(); // 停止・記録
                            }
                        }
                        break;
                    }
                }
            }
        }

        // ポモードロタイマーのイベント
        private void OnElapsed_pomodoroTimer(object sender, System.Timers.ElapsedEventArgs e)
        {
            string nextStatus = "";

            // 残り時間を表示
            remainingSeconds--;
            int workMinutes = remainingSeconds / 60;
            int workSeconds = remainingSeconds % 60;
            pomodoroTimerButton.Label = pomodoroTimerStatus + "中 " + workMinutes.ToString("00") + ":" + workSeconds.ToString("00");

            // 残り時間が0になったらタイマーを停止
            if (remainingSeconds != 0) {
                return;
            }

            pomodoroTimer.Stop();

            // 休憩時間にする
            if (pomodoroTimerStatus == Macros.STATUS_TIMER_WORK) {
                nextStatus = Macros.STATUS_TIMER_REST;
            }
            // 作業時間にする
            else if (pomodoroTimerStatus == Macros.STATUS_TIMER_REST) {
                nextStatus = Macros.STATUS_TIMER_WORK;
            }

            new ToastContentBuilder().AddArgument("action", "viewConversation").AddArgument("conversationId", 9813).AddText(nextStatus + "を開始してください").Show();
            //if (MessageBox.Show(nextStatus + "開始です", "", MessageBoxButtons.OKCancel, MessageBoxIcon.Information) != DialogResult.Cancel) {
            //    nextStatus = Macros.STATUS_TIMER_STOP;
            //}

            InitPomodoroStatus(nextStatus);
        }

        // 記録開始
        private void RecordWork() {
            string status = recordButton.Label;
            string[] lines = new string[0];
            int writeRow = 0;
            int startCol = 0;
            int endCol = 48;

            if (subjectComboBox.Text == "") {
                MessageBox.Show("件名を入力してください", "", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            if (status == Macros.STATUS_RECORD_START) {
                recordFlag = true;
                workStartTime = DateTime.Now;
                recordButton.Label = Macros.STATUS_RECORD_STOP;
                recordButton.Image = OutlookAddIn1.Properties.Resources.record;
                subjectComboBox.Enabled = false;
                return;
            }
            else {
                recordFlag = false;
                recordButton.Label = Macros.STATUS_RECORD_START;
                recordButton.Image = OutlookAddIn1.Properties.Resources.startRecord;
                subjectComboBox.Enabled = true;

                // ファイル読込
                ctrlFile.ReadCSVFile(OutlookAddIn1.Properties.Settings.Default.SCHEDULE_FILE, ref lines);
                string[] hours = lines[0].Split(',');
                string[] minutes = lines[1].Split(',');


                // 件名が同じものがあるか判定
                for (int i = Macros.SCHEDULE_ROW; i < Macros.MAX_ROW; i++) {
                    string[] values = lines[i].Split(',');
                    if (values[Macros.CSV_SUBJECT_COL] == subjectComboBox.Text) {
                        writeRow = i;
                        break;
                    }
                }

                // 予定表になければ追加
                if (writeRow == 0) {
                    for (int i = Macros.SCHEDULE_ROW; i < Macros.MAX_ROW; i++) {
                        string[] values = lines[i].Split(',');
                        if (values[Macros.CSV_SUBJECT_COL] == "") {
                            writeRow = i;
                            values[Macros.CSV_SUBJECT_COL] = subjectComboBox.Text;

                            for (int j = 0; j < values.Length; j++) {
                                if (j == 0) {
                                    lines[i] = values[j];
                                }
                                else {
                                    lines[i] = lines[i] + "," + values[j];
                                }
                            }
                            break;
                        }
                    }
                }

                // 開始時間と終了時間の列を取得
                for (int i = Macros.CSV_TIME_COL; i < hours.Length; i++) {
                    if (ctrlFile.RoundTime(workStartTime) == hours[i] + ":" + minutes[i]) {
                        startCol = i;
                    }

                    if (ctrlFile.RoundTime(DateTime.Now) == hours[i] + ":" + minutes[i]) {
                        endCol = i;
                        break;
                    }
                }

                // 予定表の計画・実績フラグ書換
                string[] changeValues = lines[writeRow].Split(',');
                for (int i = startCol; i < endCol; i++) {
                    if (changeValues[i] == "") {
                        changeValues[i] = Macros.ACHEIVE_STR;
                    }
                    else if (changeValues[i] == Macros.PLAN_STR) {
                        changeValues[i] = Macros.AS_PLANED_STR;
                    }
                }
                if (startCol == endCol) {
                    if (changeValues[startCol] == "") {
                        changeValues[startCol] = Macros.ACHEIVE_STR;
                    }
                    else if (changeValues[startCol] == Macros.PLAN_STR) {
                        changeValues[startCol] = Macros.AS_PLANED_STR;
                    }
                }
                if (endCol == 48) {
                    if (changeValues[endCol] == "") {
                        changeValues[endCol] = Macros.ACHEIVE_STR;
                    }
                    else if (changeValues[endCol] == Macros.PLAN_STR) {
                        changeValues[endCol] = Macros.AS_PLANED_STR;
                    }
                }

                // 元に戻す
                for (int i = 0; i < changeValues.Length; i++) {
                    if (i == 0) {
                        lines[writeRow] = changeValues[i];
                    }
                    else {
                        lines[writeRow] = lines[writeRow] + "," + changeValues[i];
                    }
                }

                ctrlFile.WriteCSVFile(OutlookAddIn1.Properties.Settings.Default.SCHEDULE_FILE, lines);
            }
        }

        // ステータスの初期化
        private void InitPomodoroStatus(string status) {
            if (status == "") {
                return;
            }
            pomodoroTimerStatus = status;

            switch (pomodoroTimerStatus) {
                case Macros.STATUS_TIMER_WORK:
                    remainingSeconds = int.Parse(workMinutesList.SelectedItem.Label) * 60;
                    pomodoroTimerButton.Image = OutlookAddIn1.Properties.Resources.stop;
                    workMinutesList.Enabled = false;
                    restMinutesList.Enabled = false;
                    pomodoroTimer.Start();
                    break;

                case Macros.STATUS_TIMER_STOP:
                    pomodoroTimer.Stop();
                    pomodoroTimerButton.Label = "タイマー開始";
                    pomodoroTimerButton.Image = OutlookAddIn1.Properties.Resources.startTimer;
                    workMinutesList.Enabled = true;
                    restMinutesList.Enabled = true;
                    break;

                case Macros.STATUS_TIMER_REST:
                    remainingSeconds = int.Parse(restMinutesList.SelectedItem.Label) * 60;
                    pomodoroTimerButton.Image = OutlookAddIn1.Properties.Resources.stop;
                    workMinutesList.Enabled = false;
                    restMinutesList.Enabled = false;
                    pomodoroTimer.Start();
                    break;
            }
        }

        // 件名コンボボックスのリスト更新
        private void UpdateSubject()
        {
            string[] lines = new string[0];
            RibbonDropDownItem item;

            // 予定表読込
            ctrlFile.ReadCSVFile(OutlookAddIn1.Properties.Settings.Default.SCHEDULE_FILE, ref lines);
            for (int i = Macros.SCHEDULE_ROW; i < Macros.MAX_ROW; i++) {
                string[] values = lines[i].Split(',');

                if (values[Macros.CSV_SUBJECT_COL] != "") {
                    if (values[Macros.CSV_SUBJECT_COL] == "以下MTG") {
                        continue;
                    }

                    item = Factory.CreateRibbonDropDownItem();
                    item.Label = values[Macros.CSV_SUBJECT_COL];
                    subjectComboBox.Items.Add(item);
                }
            }
        }
    }
}
