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
using System.Xml.Linq;
using OutlookAddIn1;

namespace WorkSupportTool
{
    public partial class Ribbon1
    {
        Function function = new Function();
        MessageForm msgForm = new MessageForm();
        CtrlOutlook ctrlOutlook = new CtrlOutlook();

        /****************************************************************************************************/
        // マクロ定義

        // 情報保存ファイル
        public string SCHEDULE_FILE = @"C:\Users\kobayauu\OneDrive - Brother\schedule.csv";

        // ポモードロタイマー
        public const int POMODORO_TIMER_INTERVAL = 1000;
        public const string STATUS_TIMER_WORK    = "作業";
        public const string STATUS_TIMER_REST    = "休憩";
        public const string STATUS_TIMER_STOP    = "停止";

        System.Timers.Timer pomodoroTimer = new System.Timers.Timer(POMODORO_TIMER_INTERVAL);
        int remainingSeconds = 0;
        string pomodoroTimerStatus = STATUS_TIMER_STOP;


        // 業務記録
        public const int RECORD_TIMER_INTERVAL  = 60000; // 1分毎
        public const string STATUS_RECORD_START = "記録開始";
        public const string STATUS_RECORD_STOP  = "停止・登録";
        public const int MAX_ROW                = 14;
        public const int SCHEDULE_ROW           = 2;
        public const int SUBJECT_COL            = 1;
        public const int CATEGORY_COL           = 4;
        public const int TIME_COL               = 5;
        public const string PLAN_STR            = "1";
        public const string ACHEIVE_STR         = "2";
        public const string AS_PLANED_STR       = "3";

        System.Timers.Timer recordTimer = new System.Timers.Timer(RECORD_TIMER_INTERVAL);
        DateTime workStartTime = DateTime.Now;
        DateTime workEndTime = DateTime.Now;
        bool recordFlag = false;
        bool autoRecordFlag = false;

        string[] arrSchedule = new string[0];
        string[] arrCategory = new string[0];
        /****************************************************************************************************/


        private void Ribbon1_Load(object sender, RibbonUIEventArgs e)
        {
            int n = 0;
            string[] lines = new string[0];
            RibbonDropDownItem item;

            // 予定表読込
            function.ReadCSVFile(SCHEDULE_FILE, ref lines);
            for (int i = SCHEDULE_ROW; i < MAX_ROW; i++) {
                string[] values = lines[i].Split(',');

                if (values[SUBJECT_COL] != "") {
                    item = Factory.CreateRibbonDropDownItem();
                    item.Label = values[SUBJECT_COL];
                    subjectComboBox.Items.Add(item);

                    Array.Resize(ref arrSchedule, n + 1);
                    arrSchedule[n] = values[SUBJECT_COL] + "," + values[CATEGORY_COL];
                    n++;
                }
            }

            // 分類設定
            item = Factory.CreateRibbonDropDownItem();
            item.Label = "";

            categoryList.Items.Add(item);
            ctrlOutlook.GetCategory(ref arrCategory);
            for (int i = 0; i < arrCategory.Length; i++) {
                item = Factory.CreateRibbonDropDownItem();
                item.Label = arrCategory[i];
                categoryList.Items.Add(item);
            }

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
            int n = 0;
            ScheduleForm scheduleForm = new ScheduleForm();
            string[] lines = new string[0];
            RibbonDropDownItem item;

            // 予定表表示
            scheduleForm.ShowDialog();

            // 予定表読込
            subjectComboBox.Items.Clear();

            function.ReadCSVFile(SCHEDULE_FILE, ref lines);
            for (int i = SCHEDULE_ROW; i < MAX_ROW; i++) {
                string[] values = lines[i].Split(',');

                if (values[SUBJECT_COL] != "") {
                    item = Factory.CreateRibbonDropDownItem();
                    item.Label = values[SUBJECT_COL];
                    subjectComboBox.Items.Add(item);

                    Array.Resize(ref arrSchedule, n + 1);
                    arrSchedule[n] = values[SUBJECT_COL] + "," + values[CATEGORY_COL];
                    n++;
                }
            }
        }

        private void homeWorkButton_Click(object sender, RibbonControlEventArgs e)
        {
            bool ishomeFlag = false;
            string todayDate = DateTime.Today.ToString("yyyy/MM/dd");
            string startHomeWork = "在宅(勤務中)";
            string endHomeWork = "在宅(退勤)";
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
                if (gettingSchedule[i].subject == startHomeWork) {
                    ishomeFlag = true;
                    break;
                }
            }

            if (ishomeFlag) {
                if (MessageBox.Show("在宅を終了しますか？", "", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes) {
                    settingSchedule.subject = endHomeWork;
                    ctrlOutlook.ChangeSchedule(todayDate, startHomeWork, settingSchedule);
                }
            }
            else {
                if (MessageBox.Show("在宅を開始しますか？", "", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes) {
                    settingSchedule.subject = startHomeWork;
                    ctrlOutlook.SetSchedule(settingSchedule, "");
                }
            }
        }

        private void pomodoroTimerButton_Click(object sender, RibbonControlEventArgs e)
        {
            if (pomodoroTimerStatus == STATUS_TIMER_STOP) {
                InitPomodoroStatus(STATUS_TIMER_WORK);
            }
            else {
                pomodoroTimer.Stop();
                if (MessageBox.Show("タイマーを停止しますか？", "", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes) {
                    InitPomodoroStatus(STATUS_TIMER_STOP);
                    return;
                }
                pomodoroTimer.Start();
            }
        }

        private void subjectComboBox_TextChanged(object sender, RibbonControlEventArgs e)
        {
            for (int i = 0; i < arrSchedule.Length; i++) {
                string[] values = arrSchedule[i].Split(',');
                if (subjectComboBox.Text == values[0]) {

                    for (int j = 0; j < categoryList.Items.Count; j++) {
                        if (categoryList.Items[j].Label == values[1]) {
                            categoryList.SelectedItemIndex = j;
                            break;
                        }
                    }
                    break;
                }
            }
        }

        // 業務記録タイマーのイベント
        private void OnElapsed_recordTimer(object sender, System.Timers.ElapsedEventArgs e)
        {
            string todayDate = DateTime.Today.ToString("yyyy/MM/dd");
            string todayTime = DateTime.Now.ToString("yyyy/MM/dd HH:mm");
            CtrlOutlook.scheduleSetting[] gettingSchedule = new CtrlOutlook.scheduleSetting[0];

            if (autoRecordFlag) {
                if (todayTime != workEndTime.ToString("yyyy/MM/dd HH:mm")) {
                    return;
                }

                autoRecordFlag = false;
                RecordWork();
            }
            else {
                ctrlOutlook.GetSchedule(todayDate, ref gettingSchedule);

                for (int i = 0; i < gettingSchedule.Length; i++) {
                    if (todayTime != gettingSchedule[i].start.ToString("yyyy/MM/dd HH:mm")) {
                        continue;
                    }

                    // 記録中なら強制的に停止・記録
                    if (recordFlag == true) {
                        RecordWork();
                        autoRecordFlag = true;
                        subjectComboBox.Text = gettingSchedule[i].subject;
                        workEndTime = gettingSchedule[i].end;
                        RecordWork();
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
            if (pomodoroTimerStatus == STATUS_TIMER_WORK) {
                nextStatus = STATUS_TIMER_REST;
            }
            // 作業時間にする
            else if (pomodoroTimerStatus == STATUS_TIMER_REST) {
                nextStatus = STATUS_TIMER_WORK;
            }

            msgForm.msg = nextStatus + "開始です";
            msgForm.ShowDialog();
            if (msgForm.status != 0) {
                nextStatus = STATUS_TIMER_STOP;
            }

            InitPomodoroStatus(nextStatus);
        }

        // 記録開始
        private void RecordWork() {
            string status = recordButton.Label;
            string[] lines = new string[0];
            int writeRow = 0;
            int startCol = 0;
            int endCol = 0;

            if (subjectComboBox.Text == "") {
                MessageBox.Show("件名を入力してください", "", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            if (status == STATUS_RECORD_START) {
                recordFlag = true;
                workStartTime = DateTime.Now;
                recordButton.Label = STATUS_RECORD_STOP;
                recordButton.Image = OutlookAddIn1.Properties.Resources.record;
                subjectComboBox.Enabled = false;
                return;
            }
            else {
                recordFlag = false;
                recordButton.Label = STATUS_RECORD_START;
                recordButton.Image = OutlookAddIn1.Properties.Resources.startRecord;
                subjectComboBox.Enabled = true;

                // ファイル読込
                function.ReadCSVFile(SCHEDULE_FILE, ref lines);
                string[] hours = lines[0].Split(',');
                string[] minutes = lines[1].Split(',');


                // 件名が同じものがあるか判定
                for (int i = SCHEDULE_ROW; i < MAX_ROW; i++) {
                    string[] values = lines[i].Split(',');
                    if (values[SUBJECT_COL] == subjectComboBox.Text) {
                        writeRow = i;
                        break;
                    }
                }

                // 予定表になければ追加
                if (writeRow == 0) {
                    for (int i = SCHEDULE_ROW; i < MAX_ROW; i++) {
                        string[] values = lines[i].Split(',');
                        if (values[SUBJECT_COL] == "") {
                            writeRow = i;
                            values[SUBJECT_COL] = subjectComboBox.Text;
                            values[CATEGORY_COL] = categoryList.SelectedItem.Label;

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
                for (int i = TIME_COL; i < hours.Length; i++) {
                    if (function.RoundTime(workStartTime) == hours[i] + ":" + minutes[i]) {
                        startCol = i;
                    }

                    if (function.RoundTime(DateTime.Now) == hours[i] + ":" + minutes[i]) {
                        endCol = i;
                        break;
                    }
                }

                // 予定表の計画・実績フラグ書換
                string[] changeValues = lines[writeRow].Split(',');
                for (int i = startCol; i <= endCol; i++) {
                    if (changeValues[i] == "") {
                        changeValues[i] = ACHEIVE_STR;
                    }
                    else if (changeValues[i] == PLAN_STR) {
                        changeValues[i] = AS_PLANED_STR;
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

                function.WriteCSVFile(SCHEDULE_FILE, lines);
            }
        }

        // ステータスの初期化
        private void InitPomodoroStatus(string status) {
            if (status == "") {
                return;
            }
            pomodoroTimerStatus = status;

            switch (pomodoroTimerStatus) {
                case STATUS_TIMER_WORK:
                    remainingSeconds = int.Parse(workMinutesList.SelectedItem.Label) * 60;
                    pomodoroTimerButton.Image = OutlookAddIn1.Properties.Resources.stop;
                    workMinutesList.Enabled = false;
                    restMinutesList.Enabled = false;
                    pomodoroTimer.Start();
                    break;

                case STATUS_TIMER_STOP:
                    pomodoroTimer.Stop();
                    pomodoroTimerButton.Label = "タイマー開始";
                    pomodoroTimerButton.Image = OutlookAddIn1.Properties.Resources.startTimer;
                    workMinutesList.Enabled = true;
                    restMinutesList.Enabled = true;
                    break;

                case STATUS_TIMER_REST:
                    remainingSeconds = int.Parse(restMinutesList.SelectedItem.Label) * 60;
                    pomodoroTimerButton.Image = OutlookAddIn1.Properties.Resources.stop;
                    workMinutesList.Enabled = false;
                    restMinutesList.Enabled = false;
                    pomodoroTimer.Start();
                    break;
            }
        }
    }
}
