using System;
using System.Collections.Generic;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.Office.Interop.Outlook;

namespace WorkSupportTool
{
    public partial class MainForm : Form
    {
        delegate void PomodoroTimerDelegate();

        // 予定表チェックタイマー
        System.Timers.Timer recordTimer = new System.Timers.Timer(WorkSupportTool.Properties.Settings.Default.timerSpan);
        int recording                   = 0x00; // 0bit目：記録中フラグ、1bit目：自動記録中フラグ
        DateTime startWorkTime          = DateTime.Now;
        DateTime endWorkTime            = DateTime.Now;

        // ポモードロタイマー
        System.Timers.Timer pomodoroTimer = new System.Timers.Timer(1000);
        int remainingSeconds              = 0;


        public MainForm() {
            InitializeComponent();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            // 画面の右下に表示
            this.Left = System.Windows.Forms.Screen.PrimaryScreen.Bounds.Width - this.Size.Width + 10;
            this.Top = System.Windows.Forms.Screen.PrimaryScreen.Bounds.Height - this.Size.Height - 32;

            // 予定表チェックタイマー設定
            recordTimer.Elapsed += new System.Timers.ElapsedEventHandler(OnElapsed_RecordTimer);

            // ポモードロタイマー設定
            pomodoroTimer.Elapsed += new System.Timers.ElapsedEventHandler(OnElapsed_PomodoroTimer);

            // 件名リスト読込
            UpdateSubject();

            // 記録用タイマー開始
            recordTimer.Start();
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
        }

        private void ScheduleButton_Click(object sender, EventArgs e)
        {
            // 予定表表示
            ScheduleForm scheduleForm = new ScheduleForm();
            scheduleForm.ShowDialog();

            // 件名リスト更新
            SubjectComboBox.Items.Clear();
            UpdateSubject();
        }

        private void RecordButton_Click(object sender, EventArgs e)
        {
            if ((recording & 0x01) == 0x00) {
                StartRecord();
            }
            else if ((recording & 0x01) == 0x01) {
                StopRecord();
            }
        }

        private void StartRecord()
        {
            if (SubjectComboBox.Text == "") {
                MessageBox.Show(this, "件名を入力してください", "WorkSupportTool", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            recording              |= 0x01;
            startWorkTime           = DateTime.Now;
            RecordButton.Text       = "停止・登録";
            RecordButton.ForeColor  = Color.White;
            RecordButton.BackColor  = Color.Red;
            SubjectComboBox.Enabled = false;
        }

        private void StopRecord()
        {
            string[] lines = new string[0];
            int writeRow   = 0;
            int startCol   = 0;
            int endCol     = 0;

            // ファイル読込
            Common.ctrlFile.ReadCSVFile(WorkSupportTool.Properties.Settings.Default.shcheduleFile, ref lines);
            string[] hours   = lines[0].Split(',');
            string[] minutes = lines[1].Split(',');

            // 件名が同じものがあるか判定
            for (int i = Common.FIRST_SCHEDULE_ROW; i < Common.MAX_ROW; i++) {
                string[] values = lines[i].Split(',');
                if (values[Common.CSV_SUBJECT_COL] == SubjectComboBox.Text) {
                    writeRow = i;
                    break;
                }
            }

            // 予定表になければ追加
            if (writeRow == 0) {
                for (int i = Common.FIRST_SCHEDULE_ROW; i < Common.MAX_ROW; i++) {
                    string[] values = lines[i].Split(',');
                    if (values[Common.CSV_SUBJECT_COL] == "") {
                        writeRow = i;
                        values[Common.CSV_SUBJECT_COL] = SubjectComboBox.Text;

                        // linesに格納
                        lines[i] = values[0];
                        for (int j = 1; j < values.Length; j++) {
                            lines[i] = lines[i] + "," + values[j];
                        }
                        break;
                    }
                }
            }

            // 開始時間と終了時間の列を取得
            for (int i = Common.CSV_FIRST_TIME_COL; i < hours.Length; i++) {
                if (Common.RoundTime(startWorkTime) == hours[i] + ":" + minutes[i]) {
                    startCol = i;
                }

                if (Common.RoundTime(DateTime.Now) == hours[i] + ":" + minutes[i]) {
                    endCol = i;
                    break;
                }
            }

            // 予定表の計画・実績フラグ書換
            string[] changeValues = lines[writeRow].Split(',');
            if ((startCol != 0) && (endCol != 0)) {
                for (int i = startCol; i < endCol; i++) {
                    if (changeValues[i] == "") {
                        changeValues[i] = Common.ACHEIVE_NUM;
                    }
                    else if (changeValues[i] == Common.PLAN_NUM) {
                        changeValues[i] = Common.AS_PLANED_NUM;
                    }
                }
                if (startCol == endCol) {
                    if (changeValues[startCol] == "") {
                        changeValues[startCol] = Common.ACHEIVE_NUM;
                    }
                    else if (changeValues[startCol] == Common.PLAN_NUM) {
                        changeValues[startCol] = Common.AS_PLANED_NUM;
                    }
                }
                if (endCol == 48) {
                    if (changeValues[endCol] == "") {
                        changeValues[endCol] = Common.ACHEIVE_NUM;
                    }
                    else if (changeValues[endCol] == Common.PLAN_NUM) {
                        changeValues[endCol] = Common.AS_PLANED_NUM;
                    }
                }

                // 元に戻す
                lines[writeRow] = changeValues[0];
                for (int i = 1; i < changeValues.Length; i++) {
                    lines[writeRow] = lines[writeRow] + "," + changeValues[i];
                }
                Common.ctrlFile.WriteCSVFile(WorkSupportTool.Properties.Settings.Default.shcheduleFile, lines);
            }

            recording               = 0x00;
            RecordButton.Text       = "記録開始";
            RecordButton.ForeColor  = default;
            RecordButton.BackColor  = default;
            SubjectComboBox.Enabled = true;
        }

        private void OnElapsed_RecordTimer(object sender, System.Timers.ElapsedEventArgs e) {
            string currentTime = DateTime.Now.ToString("yyyy/MM/dd HH:mm");
            CtrlOutlook.SCHEDULEOPTION[] gettingSchedule = new CtrlOutlook.SCHEDULEOPTION[0];

            // 予定表より自動記録開始
            if ((recording & 0x10) == 0x00) {
                Common.ctrlOutlook.GetSchedule(ref gettingSchedule);
                for (int i = 0; i < gettingSchedule.Length; i++) {
                    if ((currentTime != gettingSchedule[i].start.ToString("yyyy/MM/dd HH:mm")) || (gettingSchedule[i].categories == "その他")) {
                        continue;
                    }

                    // 記録中なら強制的に停止・記録
                    if ((recording & 0x01) == 0x01) {
                        StopRecord();
                    }

                    // 記録開始
                    SubjectComboBox.Text = gettingSchedule[i].subject;
                    endWorkTime = gettingSchedule[i].end;
                    StartRecord();
                    recording |= 0x10;
                    break;
                }
            }
            else {
                if (currentTime == endWorkTime.ToString("yyyy/MM/dd HH:mm")) {
                    StopRecord();
                }
            }

            // 記録中に休憩時間になったら強制的に停止・記録
            if ((recording & 0x01) == 0x01) {
                string restTimes = WorkSupportTool.Properties.Settings.Default.restTime;
                string[] values = restTimes.Split(',');

                for (int i = 0; i < values.Length; i++) {
                    if (currentTime == DateTime.Now.ToString("yyyy/MM/dd ") + values[i]) {
                        StopRecord();
                        break;
                    }
                }
            }
        }

        private void PomodoroTimerButton_Click(object sender, EventArgs e)
        {
            string status = PomodoroTimerButton.Text;

            if (status.Contains("タイマー開始")) {
                pomodoroTimer.Start();
            }
            else {
                if (MessageBox.Show(this, "タイマーを停止しますか？", "WorkSupportTool", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes) {
                    pomodoroTimer.Stop();
                    remainingSeconds = 0;
                    PomodoroTimerButton.Text = "タイマー開始";
                    PomodoroTimerButton.ForeColor = default;
                    PomodoroTimerButton.BackColor = default;
                }
            }
        }

        private void OnElapsed_PomodoroTimer(object sender, System.Timers.ElapsedEventArgs e)
        {
            Invoke(new PomodoroTimerDelegate(ProcessingPomodoroTimer));
        }

        private void ProcessingPomodoroTimer()
        {
            string[] status = PomodoroTimerButton.Text.Split(' ');
            bool startFlag = false;

            // 残り時間が0になったらタイマー停止
            if (remainingSeconds == 0) {
                PomodoroTimerButton.ForeColor = Color.White;

                // 作業時間にする
                if ((status[0] == "タイマー開始") || (status[0] == "休憩中")) {
                    if (status[0] == "タイマー開始") {
                        startFlag = true;
                    }
                    remainingSeconds = WorkSupportTool.Properties.Settings.Default.workMinutes * 60;
                    status[0] = "作業中";
                    PomodoroTimerButton.BackColor = Color.Red;
                }
                // 休憩時間にする
                else {
                    remainingSeconds = WorkSupportTool.Properties.Settings.Default.restMinutes * 60;
                    status[0] = "休憩中";
                    PomodoroTimerButton.BackColor = Color.LimeGreen;
                }

                // 作業⇔休憩の切替時にメッセージボックス表示
                if (!startFlag) {
                    pomodoroTimer.Stop();
                    MessageBox.Show(this, status[0] + "を開始してください", "WorkSupportTool", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    pomodoroTimer.Start();
                }
            }

            // 残り時間等を表示
            remainingSeconds--;
            int workMinutes = remainingSeconds / 60;
            int workSeconds = remainingSeconds % 60;

            PomodoroTimerButton.Text = status[0] + " " + workMinutes.ToString("00") + ":" + workSeconds.ToString("00");
        }

        private void WorkButton_Click(object sender, EventArgs e)
        {
            bool working         = false;
            string doingWork     = "出社(勤務中)";
            string endWork       = "退勤";
            string planHomeWork  = "在宅(予定)";
            string startHomeWork = "在宅(開始)";
            string doingHomeWork = "在宅(勤務中)";
            string endHomeWork   = "在宅(終了)";
            string chatID        = "";
            string deleteSubject = "";
            string msg           = "";

            CtrlOutlook.SCHEDULEOPTION settingWork = new CtrlOutlook.SCHEDULEOPTION();
            CtrlOutlook.SCHEDULEOPTION[] gettingSchedule = new CtrlOutlook.SCHEDULEOPTION[0];

            // 予定初期化
            settingWork.start       = DateTime.Now;
            settingWork.end         = DateTime.Now;
            settingWork.allDayEvent = true;
            settingWork.busyStatus  = OlBusyStatus.olFree;
            settingWork.sensitivity = OlSensitivity.olNormal;
            settingWork.importance  = OlImportance.olImportanceNormal;

            Common.ctrlOutlook.GetSchedule(ref gettingSchedule);
          
            if (MessageBox.Show(this, "出社していますか？", "WorkSupportTool", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes) {
                // 出社勤務
                // 既に出社の予定があるかチェック              
                for (int i = 0; i < gettingSchedule.Length; i++) {
                    if (gettingSchedule[i].subject == doingWork) {
                        working = true;
                        break;
                    }
                }

                if (!working) {
                    msg                  = "出勤しますか？";
                    settingWork.subject  = doingWork;
                    settingWork.location = "GTハードソフト研(第1-2F)";
                    deleteSubject        = endWork;
                }
                else {
                    msg                 = "退勤しますか？";
                    settingWork.subject = endWork;
                    deleteSubject       = doingWork;
                }
            }
            else {
                // 在宅勤務
                // 既に在宅の予定があるかチェック
                for (int i = 0; i < gettingSchedule.Length; i++) {
                    if (gettingSchedule[i].subject == doingHomeWork) {
                        chatID = gettingSchedule[i].location;
                        working = true;
                        break;
                    }
                }

                if (!working) {
                    msg                 = "在宅を開始しますか？";
                    settingWork.subject = startHomeWork;
                    deleteSubject       = planHomeWork;
                }
                else {
                    msg                  = "在宅を終了しますか？";
                    settingWork.subject  = endHomeWork;
                    settingWork.location = chatID;
                    deleteSubject        = doingHomeWork;
                }
            }

            if (MessageBox.Show(this, msg, "WorkSupportTool", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes) {
                return;
            }

            // 予定追加
            Common.ctrlOutlook.DeleteSchedule(deleteSubject);
            Common.ctrlOutlook.SetSchedule(settingWork);
        }

        // 件名コンボボックスのリスト更新
        private void UpdateSubject() {
            string[] lines = new string[0];

            // 予定表読込
            Common.ctrlFile.ReadCSVFile(WorkSupportTool.Properties.Settings.Default.shcheduleFile, ref lines);
            for (int i = Common.FIRST_SCHEDULE_ROW; i < Common.MAX_ROW; i++) {
                string[] values = lines[i].Split(',');

                if ((values[Common.CSV_SUBJECT_COL] == "") || (values[Common.CSV_SUBJECT_COL] == "以下MTG")) {
                    continue;
                }

                SubjectComboBox.Items.Add(values[Common.CSV_SUBJECT_COL]);
            }
        }
    }
}
