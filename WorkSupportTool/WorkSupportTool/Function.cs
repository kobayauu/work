using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Drawing;
using System.Runtime.InteropServices;
using Microsoft.Office.Interop.Outlook;
using System.Windows.Forms;

namespace WorkSupportTool
{
    // マクロ定義
    static class Macros
    {
        // 業務記録
        public const int RECORD_TIMER_INTERVAL  = 60000; // 1分毎
        public const string STATUS_RECORD_START = "記録開始";
        public const string STATUS_RECORD_STOP  = "停止・登録";
        public const int CSV_SUBJECT_COL        = 1;
        public const int CSV_CATEGORY_COL       = 4;
        public const int CSV_TIME_COL           = 5;

        // ポモードロタイマー
        public const int POMODORO_TIMER_INTERVAL = 1000;
        public const string STATUS_TIMER_WORK    = "作業";
        public const string STATUS_TIMER_REST    = "休憩";
        public const string STATUS_TIMER_STOP    = "停止";

        // 表の行列番号識別
        public const int MAX_ROW      = 14;
        public const int HEADER_ROW1  = 0;
        public const int HEADER_ROW2  = 1;
        public const int SCHEDULE_ROW = 2;
        public const int SPLIT_ROW    = 7;
        public const int MTG_ROW      = 8;
        public const int SUBJECT_COL  = 0;
        public const int MEMO_COL     = 1;
        public const int ACHIEVE_COL  = 2;
        public const int CATEGORY_COL = 3;
        public const int TIME_COL     = 4;

        // 予定・実績
        public const string PLAN_BTN                    = "計画";
        public const string ACHIEVE_BTN                 = "実績";
        public const string RESULT_FOLDER_NAME          = "実績";
        public static System.Drawing.Color RESULT_COLOR = Color.LightGreen;
        public static System.Drawing.Color REST_COLOR   = Color.Gray;
        public const string PLAN_MARK                   = "→";
        public const string PLAN_STR                    = "1";
        public const string ACHEIVE_STR                 = "2";
        public const string AS_PLANED_STR               = "3";
        public const string REST_STR                    = "4";

        //
        public const int MODE_ROW = 0;
        public const int MODE_COL = 1;

        // 勤務
        public static string WORK_START = "出勤";
        public static string WORK_END   = "退勤";
    }

    internal class CtrlFile
    {
        // csvファイル読込
        public int ReadCSVFile(string filePath, ref string[] lines)
        {
            int i = 0;
            StreamReader sr = new StreamReader(filePath, Encoding.GetEncoding("Shift_JIS"));

            while (!sr.EndOfStream) {
                string line = sr.ReadLine();

                Array.Resize(ref lines, i + 1);
                lines[i] = line;
                i++;
            }
            sr.Close();

            return 0;
        }

        // csvファイル書込
        public int WriteCSVFile(string filePath, string[] lines)
        {
            StreamWriter sw = new StreamWriter(filePath, false, Encoding.GetEncoding("Shift_JIS"));
            
            for (int i = 0; i < lines.Length; i++) {
                sw.WriteLine(lines[i]);
            }
            sw.Close();
            return 0;
        }

        // 時間の四捨五入
        public string RoundTime(DateTime time) {
            string tmpTime = "";
            int hour = 0;
            int minutes = 0;
            string[] tmp;

            tmpTime = time.ToString("H:m");
            tmp = tmpTime.Split(':');
            hour = int.Parse(tmp[0]);
            minutes = int.Parse(tmp[1]);

            if (minutes < 15) {
                minutes = 0;
            }
            else if ((minutes >= 15) && (minutes < 30)) {
                minutes = 15;
            }
            else if ((minutes >= 30) && (minutes < 45)) {
                minutes = 30;
            }
            else {
                minutes = 45;
            }

            return hour.ToString() + ":" + minutes.ToString();
        }
    }

    internal class CtrlOutlook
    {
        /****************************************************************************************************/
        bool isConnect = false;

        Microsoft.Office.Interop.Outlook.Application app;
        NameSpace oNamespase;
        AppointmentItem appItem;
        MAPIFolder folder;
        Items AllItems;
        Items items;

        // 構造体
        public struct scheduleSetting
        {
            public string subject;
            public string body;
            public string categories;
            public DateTime start;
            public DateTime end;
            public string location;
            public bool allDayEvent;
            public OlBusyStatus busyStatus;
            public bool reminderSet;
            public OlImportance importance;

            public scheduleSetting(string subject) {
                this.subject = subject;
                this.body = "";
                this.categories = "";
                this.start = DateTime.Now;
                this.end = DateTime.Now;
                this.location = "";
                this.allDayEvent = false;
                this.busyStatus = OlBusyStatus.olFree;
                this.reminderSet = false;
                this.importance = OlImportance.olImportanceNormal;
            }
        }
        /****************************************************************************************************/


        private int ConnectOutlook() {
            app = new Microsoft.Office.Interop.Outlook.Application();
            oNamespase = app.GetNamespace("MAPI");
            oNamespase.Logon(null, null, true, true);

            isConnect = true;
            return 0;
        }

        private void DisconnectOutlook() {
            //プロセス解放
            if (isConnect) {
                oNamespase.Logoff();

                if (items != null) {
                    Marshal.ReleaseComObject(items);
                }
                if (AllItems != null) {
                    Marshal.ReleaseComObject(AllItems);
                }
                if (folder != null) {
                    Marshal.ReleaseComObject(folder);
                }
                if (appItem != null) {
                    Marshal.ReleaseComObject(appItem);
                }
                if (oNamespase != null) {
                    Marshal.ReleaseComObject(oNamespase);
                }
                if (app != null) {
                    Marshal.ReleaseComObject(app);
                }

                isConnect = false;
            }
        }

        // 予定設定
        public int SetSchedule(scheduleSetting schedule, string folderName) {
            // 接続
            if (ConnectOutlook() != 0) {
                return -1;
            }

            appItem = app.CreateItem(OlItemType.olAppointmentItem);
            appItem.Subject = schedule.subject;
            appItem.Body = schedule.body;
            appItem.Categories = schedule.categories;
            appItem.Start = schedule.start;
            appItem.End = schedule.end;
            appItem.Location = schedule.location;
            appItem.AllDayEvent = schedule.allDayEvent;
            appItem.BusyStatus = schedule.busyStatus;
            appItem.ReminderSet = schedule.reminderSet;
            appItem.Importance = schedule.importance;
            appItem.Close(OlInspectorClose.olSave);

            // フォルダ移動(あれば)
            if (folderName != "") {
                foreach (MAPIFolder folder in oNamespase.GetDefaultFolder(OlDefaultFolders.olFolderCalendar).Folders) {
                    if (folder.Name == folderName) {
                        appItem.Move(folder);
                        break;
                    }
                }
            }

            // 接続解除
            DisconnectOutlook();

            return 0;
        }

        // 指定日の予定取得
        public int GetSchedule(string date, ref scheduleSetting[] schedule) {
            int i = 0;
            // 接続
            if (ConnectOutlook() != 0) {
                return -1;
            }

            folder = oNamespase.GetDefaultFolder(OlDefaultFolders.olFolderCalendar);
            AllItems = folder.Items;
            AllItems.IncludeRecurrences = true;
            AllItems.Sort("[Start]", Type.Missing);
            string filter = "[Start] >= '" + date + " 00:00' AND [Start] <= '" + date + " 23:59'";
            items = AllItems.Restrict(filter);

            foreach (_AppointmentItem item in items) {
                Array.Resize(ref schedule, i + 1);
                schedule[i].subject = item.Subject;
                schedule[i].body = item.Body;
                schedule[i].categories = item.Categories;
                schedule[i].start = item.Start;
                schedule[i].end = item.End;
                schedule[i].location = item.Location;
                schedule[i].allDayEvent = item.AllDayEvent;
                schedule[i].busyStatus = item.BusyStatus;
                schedule[i].reminderSet = item.ReminderSet;
                schedule[i].importance = item.Importance;
                i++;
            }

            // 接続解除
            DisconnectOutlook();

            return 0;
        }

        // 指定の予定の内容変更
        public int ChangeSchedule(string date, string subject, scheduleSetting schedule) {
            // 接続
            if (ConnectOutlook() != 0) {
                return -1;
            }

            folder = oNamespase.GetDefaultFolder(OlDefaultFolders.olFolderCalendar);
            AllItems = folder.Items;
            AllItems.IncludeRecurrences = true;
            AllItems.Sort("[Start]", Type.Missing);
            string filter = "[Start] >= '" + date + " 00:00' AND [Start] <= '" + date + " 23:59'";
            items = AllItems.Restrict(filter);

            foreach (_AppointmentItem item in items) {
                if (item.Subject == subject) {
                    item.Subject = schedule.subject;
                    item.Body = schedule.body;
                    item.Categories = schedule.categories;
                    item.Start = schedule.start;
                    item.End = schedule.end;
                    item.Location = schedule.location;
                    item.AllDayEvent = schedule.allDayEvent;
                    item.BusyStatus = schedule.busyStatus;
                    item.ReminderSet = schedule.reminderSet;
                    item.Importance = schedule.importance;
                    item.Save();
                    break;
                }
            }

            // 接続解除
            DisconnectOutlook();

            return 0;
        }

        // 分類取得
        public int GetCategory(ref string[] arrCategory) {
            int i = 0;

            // 接続
            if (ConnectOutlook() != 0) {
                return -1;
            }

            foreach (Category caterory in oNamespase.Categories) {
                Array.Resize(ref arrCategory, i + 1);
                arrCategory[i] = caterory.Name;
                i++;
            }
            Array.Sort(arrCategory);

            // 接続解除
            DisconnectOutlook();

            return 0;
        }

        public int ChangeWorkStatus(string status)
        {
            bool isWorkFlag = false;
            bool isEndFlag = false;
            string todayDate = DateTime.Today.ToString("yyyy/MM/dd");
            string startWork = "出勤(勤務中)";
            string endWork = "退勤";
            CtrlOutlook.scheduleSetting settingSchedule = new CtrlOutlook.scheduleSetting();
            CtrlOutlook.scheduleSetting[] gettingSchedule = new CtrlOutlook.scheduleSetting[0];

            // 初期化
            settingSchedule.start = DateTime.Now;
            settingSchedule.end = DateTime.Now;
            settingSchedule.location = "GTハードソフト研(第1-2F)";
            settingSchedule.allDayEvent = true;
            settingSchedule.busyStatus = OlBusyStatus.olFree;
            settingSchedule.importance = OlImportance.olImportanceNormal;

            // 
            GetSchedule(todayDate, ref gettingSchedule);
            for (int i = 0; i < gettingSchedule.Length; i++) {
                if (gettingSchedule[i].subject == startWork) {
                    isWorkFlag = true;
                    //break;
                }
                if (gettingSchedule[i].subject == endWork) {
                    isEndFlag = true;
                    //break;
                }
            }

            if (status == Macros.WORK_START) {
                if (!isWorkFlag) {
                    //if (MessageBox.Show("出勤しますか？", "", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes) {
                        settingSchedule.subject = startWork;
                        SetSchedule(settingSchedule, "");
                    //}
                }
            }
            else if (status == Macros.WORK_END) {
                if (isWorkFlag) {
                    //if (MessageBox.Show("退勤しますか？", "", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes) {
                        settingSchedule.subject = endWork;
                        settingSchedule.location = "";
                        ChangeSchedule(todayDate, startWork, settingSchedule);
                    //}
                }
                else {
                    //if (MessageBox.Show("退勤しますか？", "", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes) {
                    if (isEndFlag) {
                        settingSchedule.subject = endWork;
                        settingSchedule.location = "";
                        SetSchedule(settingSchedule, "");
                    }
                    //}
                }
            }
            else {
                if (isWorkFlag) {
                    if (MessageBox.Show("退勤しますか？", "", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes) {
                        settingSchedule.subject = endWork;
                        settingSchedule.location = "";
                        ChangeSchedule(todayDate, startWork, settingSchedule);
                    }
                }
                else {
                    if (MessageBox.Show("出勤しますか？", "", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes) {
                        settingSchedule.subject = startWork;
                        SetSchedule(settingSchedule, "");
                    }
                }
            }

            return 0;
        }
    }
}
