using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.Window;
using System.Runtime.InteropServices;
using Microsoft.Office.Interop;
using Microsoft.Office.Interop.Outlook;
using System.Xml.Linq;

namespace OutlookAddIn1
{
    public partial class MainForm : Form
    {
        /****************************************************************************************************/
        // マクロ定義
        public const string WINDOW_TITLE = "業務補助ツール";

        // ポモードロタイマー
        public const int POMODORO_TIMER_INTERVAL = 1000;
        public const int POMODORO_WORK_MINUTES   = 25;
        public const int POMODORO_REST_MINUTES   = 5;
        public const string STATUS_TIMER_WORK    = "作業";
        public const string STATUS_TIMER_REST    = "休憩";
        public const string STATUS_TIMER_STOP    = "停止";

        System.Timers.Timer pomodoroTimer = new System.Timers.Timer(POMODORO_TIMER_INTERVAL);
        delegate void UpdatePomodoroTimerDelegate();
        int remainingSeconds = 25;
        string pomodoroTimerStatus = STATUS_TIMER_STOP;


        // 業務記録
        public const int RECORD_TIMER_INTERVAL  = 60000; // 1分毎
        public const string STATUS_RECORD_START = "記録開始";
        public const string STATUS_RECORD_STOP  = "停止・登録";
        public const string RESULT_FOLDER_NAME  = "実績";

        System.Timers.Timer recordTimer = new System.Timers.Timer(RECORD_TIMER_INTERVAL);
        delegate void UpdateRecordTimerDelegate();
        DateTime workStartTime = DateTime.Now;
        DateTime workEndTime = DateTime.Now;
        string[] arrCategories = new string[1];
        bool recordFlag = false;
        bool autoRecordFlag = false;
        /****************************************************************************************************/

        public MainForm() {
            InitializeComponent();
        }

        private void MainForm_Load(object sender, EventArgs e) {
            // 画面の右下に表示
            this.Left = System.Windows.Forms.Screen.PrimaryScreen.Bounds.Width - this.Size.Width;
            this.Top = System.Windows.Forms.Screen.PrimaryScreen.Bounds.Height - this.Size.Height * 2;

            // ポモードロタイマーの設定
            pomodoroTimer.Elapsed += new System.Timers.ElapsedEventHandler(OnElapsed_pomodoroTimer);

            // 予定表チェックタイマーの設定
            recordTimer.Elapsed += new System.Timers.ElapsedEventHandler(OnElapsed_recordTimer);
            recordTimer.Start();

            // PJ No.の設定
            categoryComboBox.Items.Add("");
            for (int i = 0; i < arrCategories.Length; i++) {
                if ( (arrCategories[i] != "その他") && (arrCategories[i] != "休日") && (arrCategories[i] != "重要") ) {
                    categoryComboBox.Items.Add(arrCategories[i]);
                }
            }
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            recordTimer.Stop();
        }

        private void MainForm_MouseEnter(object sender, EventArgs e)
        {
            this.Opacity = 1.0;
        }

        private void MainForm_MouseLeave(object sender, EventArgs e)
        {
            this.Opacity = 0.6;
        }

        private void recordButton_MouseEnter(object sender, EventArgs e)
        {
            this.Opacity = 1.0;
        }

        private void recordButton_MouseLeave(object sender, EventArgs e)
        {
            this.Opacity = 0.6;
        }

        private void pomodoroTimerButton_MouseEnter(object sender, EventArgs e)
        {
            this.Opacity = 1.0;
        }

        private void pomodoroTimerButton_MouseLeave(object sender, EventArgs e)
        {
            this.Opacity = 0.6;
        }

        private void scheduleButton_MouseEnter(object sender, EventArgs e)
        {
            this.Opacity = 1.0;
        }

        private void scheduleButton_MouseLeave(object sender, EventArgs e)
        {
            this.Opacity = 0.6;
        }

        private void subjectComboBox_MouseEnter(object sender, EventArgs e)
        {
            this.Opacity = 1.0;
        }

        private void subjectComboBox_MouseLeave(object sender, EventArgs e)
        {
            this.Opacity = 0.6;
        }

        private void categoryComboBox_MouseEnter(object sender, EventArgs e)
        {
            this.Opacity = 1.0;
        }

        private void categoryComboBox_MouseLeave(object sender, EventArgs e)
        {
            this.Opacity = 0.6;
        }

        private void label3_MouseEnter(object sender, EventArgs e)
        {
            this.Opacity = 1.0;
        }

        private void label3_MouseLeave(object sender, EventArgs e)
        {
            this.Opacity = 0.6;
        }

        private void label4_MouseEnter(object sender, EventArgs e)
        {
            this.Opacity = 1.0;
        }

        private void label4_MouseLeave(object sender, EventArgs e)
        {
            this.Opacity = 0.6;
        }

        // ポモードロタイマーのボタンが押されたとき
        private void pomodoroTimerButton_Click(object sender, EventArgs e)
        {
            if (pomodoroTimerStatus == STATUS_TIMER_STOP) {
                InitPomodoroStatus(STATUS_TIMER_WORK);
            }
            else {
                pomodoroTimer.Stop();
                if (MessageBox.Show(this, "タイマーを停止しますか？", MainForm.WINDOW_TITLE, MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes) {
                    InitPomodoroStatus(STATUS_TIMER_STOP);
                    return;
                }
                pomodoroTimer.Start();
            }
        }

        // 業務記録のボタンが押されたとき
        private void recordButton_Click(object sender, EventArgs e)
        {
            string status = recordButton.Text;

            //if (MessageBox.Show(status + "しますか？", WINDOW_TITLE, MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.No) {
            //    return;
            //}

            if (status == STATUS_RECORD_START) {
                recordFlag = true;
                workStartTime = DateTime.Now;
                recordButton.Text = STATUS_RECORD_STOP;
                recordButton.ForeColor = Color.White;
                recordButton.BackColor = Color.Red;
                return;
            }
            else {
                recordFlag = false;
                recordButton.Text = STATUS_RECORD_START;
                recordButton.ForeColor = default;
                recordButton.BackColor = default;

                Microsoft.Office.Interop.Outlook.Application app = new Microsoft.Office.Interop.Outlook.Application();
                NameSpace oNamespase = app.GetNamespace("MAPI");
                _AppointmentItem appItem = appItem = (_AppointmentItem)app.CreateItem(OlItemType.olAppointmentItem);
                oNamespase.Logon(null, null, true, true);

                appItem.Subject = subjectComboBox.Text;
                appItem.Categories = categoryComboBox.Text;
                appItem.Start = workStartTime;
                appItem.End = DateTime.Now;
                appItem.ReminderSet = false;
                appItem.Close(OlInspectorClose.olSave);

                foreach (MAPIFolder folder in oNamespase.GetDefaultFolder(OlDefaultFolders.olFolderCalendar).Folders) {
                    if (folder.Name == RESULT_FOLDER_NAME) {
                        appItem.Move(folder);
                        break;
                    }
                }

                oNamespase.Logoff();

                Marshal.ReleaseComObject(appItem);
                Marshal.ReleaseComObject(oNamespase);
                Marshal.ReleaseComObject(app);
            }
        }

        // 予定表のボタンが押されたとき
        private void scheduleButton_Click(object sender, EventArgs e)
        {
            ScheduleForm scheduleForm = new ScheduleForm();
            scheduleForm.Show();
        }

        // ポモードロタイマーのイベント
        private void OnElapsed_pomodoroTimer(object sender, System.Timers.ElapsedEventArgs e)
        {
            this.Invoke(new UpdatePomodoroTimerDelegate(this.UpdatePomodoroTimer));
        }

        private void UpdatePomodoroTimer()
        {
            string nextStatus = "";

            // 残り時間を表示
            remainingSeconds--;
            int workMinutes = remainingSeconds / 60;
            int workSeconds = remainingSeconds % 60;
            pomodoroTimerButton.Text = pomodoroTimerStatus + "中 " + workMinutes.ToString("00") + ":" + workSeconds.ToString("00");

            // 残り時間が0になったらタイマーを停止
            if (remainingSeconds == 0) {
                pomodoroTimer.Stop();

                // 休憩時間にする
                if (pomodoroTimerStatus == STATUS_TIMER_WORK) {
                    nextStatus = STATUS_TIMER_REST;
                }
                // 作業時間にする
                else if (pomodoroTimerStatus == STATUS_TIMER_REST) {
                    nextStatus = STATUS_TIMER_WORK;
                }

                if (MessageBox.Show(this, nextStatus + "を開始します", MainForm.WINDOW_TITLE, MessageBoxButtons.OKCancel, MessageBoxIcon.Information) == DialogResult.Cancel) {
                    nextStatus = STATUS_TIMER_STOP;
                }
            }

            if (nextStatus != "") {
                InitPomodoroStatus(nextStatus);
            }
        }

        // ステータスの初期化
        private void InitPomodoroStatus(string status)
        {
            pomodoroTimerStatus = status;
            switch (pomodoroTimerStatus) {
                case STATUS_TIMER_WORK:
                    remainingSeconds = POMODORO_WORK_MINUTES * 60;
                    pomodoroTimerButton.ForeColor = Color.White;
                    pomodoroTimerButton.BackColor = Color.Red;
                    pomodoroTimer.Start();
                    UpdatePomodoroTimer();
                    break;

                case STATUS_TIMER_STOP:
                    pomodoroTimer.Stop();
                    pomodoroTimerButton.Text = "タイマー開始";
                    pomodoroTimerButton.ForeColor = default;
                    pomodoroTimerButton.BackColor = default;
                    break;

                case STATUS_TIMER_REST:
                    remainingSeconds = POMODORO_REST_MINUTES * 60;
                    pomodoroTimerButton.ForeColor = Color.White;
                    pomodoroTimerButton.BackColor = Color.Blue;
                    pomodoroTimer.Start();
                    UpdatePomodoroTimer();
                    break;
            }
        }

        // 業務記録タイマーのイベント
        private void OnElapsed_recordTimer(object sender, System.Timers.ElapsedEventArgs e)
        {
            this.Invoke(new UpdateRecordTimerDelegate(this.UpdateRecordTimer));
        }

        private void UpdateRecordTimer()
        {
            Microsoft.Office.Interop.Outlook.Application app = new Microsoft.Office.Interop.Outlook.Application();
            NameSpace oNamespase = app.GetNamespace("MAPI");
            MAPIFolder folder = oNamespase.GetDefaultFolder(OlDefaultFolders.olFolderCalendar);
            Items AllItems = folder.Items;
            _AppointmentItem appItem = appItem = (_AppointmentItem)app.CreateItem(OlItemType.olAppointmentItem);
            oNamespase.Logon(null, null, true, true);

            AllItems.IncludeRecurrences = true;
            AllItems.Sort("[Start]", Type.Missing);
            string startDate = DateTime.Today.ToString("yyyy/MM/dd");
            string filter = "[Start] >= '" + startDate + " 00:00' AND [Start] <= '" + startDate + " 23:59'";
            Items items = AllItems.Restrict(filter);

            if (!autoRecordFlag) {
                foreach (_AppointmentItem item in items) {
                    if (item.Start.ToString("yyyy/MM/dd HH:mm") == DateTime.Now.ToString("yyyy/MM/dd HH:mm")) {
                        // 記録中なら強制的に停止・記録
                        if (recordFlag == true) {
                            recordButton.PerformClick();
                        }

                        autoRecordFlag = true;
                        subjectComboBox.Text = item.Subject;
                        workEndTime = item.End;
                        recordButton.PerformClick();
                        break;
                    }
                }
            }
            else {
                if (DateTime.Now.ToString("yyyy/MM/dd HH:mm") == workEndTime.ToString("yyyy/MM/dd HH:mm")) {
                    autoRecordFlag = false;
                    recordButton.PerformClick();
                }
            }

            //プロセス解放
            oNamespase.Logoff();
            Marshal.ReleaseComObject(appItem);
            Marshal.ReleaseComObject(items);
            Marshal.ReleaseComObject(AllItems);
            Marshal.ReleaseComObject(folder);
            Marshal.ReleaseComObject(oNamespase);
            Marshal.ReleaseComObject(app);
        }

        public void SetCategory(string[] categories)
        {
            Array.Resize(ref arrCategories, categories.Length); 
            for (int i = 0; i < arrCategories.Length; i++) {
                arrCategories[i] = categories[i];
            }
        }
    }
}
