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
    class Common {
        /****************************************************************************************************/
        // 業務記録
        internal const int CSV_SUBJECT_COL    = 1;
        internal const int CSV_FIRST_TIME_COL = 5;

        // 表の行列番号識別
        internal const int MAX_ROW            = 14;
        internal const int HOUR_ROW           = 0;
        internal const int MINUTE_ROW         = 1;
        internal const int FIRST_SCHEDULE_ROW = 2;
        internal const int SPLIT_ROW          = 7;
        internal const int FIRST_MTG_ROW      = 8;
        internal const int SUBJECT_COL        = 0;
        internal const int MEMO_COL           = 1;
        internal const int ACHIEVE_COL        = 2;
        internal const int CATEGORY_COL       = 3;
        internal const int FIRST_TIME_COL     = 4;

        // 予定・実績
        internal const string PLAN_MARK     = "→";
        internal const string PLAN_NUM      = "1";
        internal const string ACHEIVE_NUM   = "2";
        internal const string AS_PLANED_NUM = "3";
        internal const string REST_NUM      = "4";
        internal static System.Drawing.Color RESULT_COLOR  = Color.LightGreen;
        internal static System.Drawing.Color REST_COLOR    = Color.Gray;
        internal static System.Drawing.Color CURRENT_COLOR = Color.LightPink;

        // DataGridViewの縦横罫線を非表示にするためのモード切替設定値
        internal const int CHECK_ROW_MODE = 0;
        internal const int CHECK_COL_MODE = 1;
        /****************************************************************************************************/

        internal static readonly CtrlOutlook ctrlOutlook = new CtrlOutlook();
        internal static readonly CtrlFile ctrlFile = new CtrlFile();

        // 時間の四捨五入
        internal static string RoundTime(DateTime time)
        {
            string tmpTime = "";
            int hour       = 0;
            int minutes    = 0;
            string[] tmp;

            tmpTime = time.ToString("H:m");
            tmp     = tmpTime.Split(':');
            hour    = int.Parse(tmp[0]);
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

    internal class CtrlFile
    {
        // csvファイル読込
        public int ReadCSVFile(string filePath, ref string[] lines)
        {
            int i           = 0;
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
    }

    public class CtrlOutlook
    {
        /****************************************************************************************************/
        Microsoft.Office.Interop.Outlook.Application app;
        NameSpace oNamespase;
        AppointmentItem appItem;
        Items AllItems;
        Items items;

        bool bConnect = false;

        // 構造体
        public struct SCHEDULEOPTION
        {
            public string subject;
            public DateTime start;
            public DateTime end;
            public bool allDayEvent;
            public string location;
            public string body;
            public string categories;
            public OlBusyStatus busyStatus;
            public bool reminderSet;
            public OlSensitivity sensitivity;
            public OlImportance importance;

            public SCHEDULEOPTION(int dummy) {
                this.subject     = "";
                this.start       = DateTime.Now;
                this.end         = DateTime.Now;
                this.allDayEvent = false;
                this.location    = "";
                this.body        = "";
                this.categories  = "";
                this.busyStatus  = OlBusyStatus.olFree;
                this.reminderSet = false;
                this.sensitivity = OlSensitivity.olPrivate;
                this.importance  = OlImportance.olImportanceNormal;
            }
        }
        /****************************************************************************************************/

        private int ConnectOutlook()
        {
            try {
                app        = new Microsoft.Office.Interop.Outlook.Application();
                oNamespase = app.GetNamespace("MAPI");
                oNamespase.Logon(null, null, true, true);
                bConnect   = true;

                return 0;
            }
            catch(System.Exception e) {
                MessageBox.Show(e.Message);
                return -1;
            }
        }

        private void DisconnectOutlook()
        {
            try {
                if (bConnect) {
                    //プロセス解放
                    oNamespase.Logoff();

                    if (items != null) {
                        Marshal.ReleaseComObject(items);
                    }
                    if (AllItems != null) {
                        Marshal.ReleaseComObject(AllItems);
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

                    bConnect = false;
                }
            }
            catch (System.Exception e) {
                MessageBox.Show(e.Message);
            }
        }

        // 予定設定
        public int SetSchedule(SCHEDULEOPTION schedule, string folderName = "")
        {
            try {
                // 接続
                if (ConnectOutlook() != 0) {
                    return -1;
                }

                appItem             = app.CreateItem(OlItemType.olAppointmentItem);
                appItem.Subject     = schedule.subject;
                appItem.Start       = schedule.start;
                appItem.End         = schedule.end;
                appItem.AllDayEvent = schedule.allDayEvent;
                appItem.Location    = schedule.location;
                appItem.Body        = schedule.body;
                appItem.Categories  = schedule.categories;
                appItem.BusyStatus  = schedule.busyStatus;
                appItem.ReminderSet = schedule.reminderSet;
                appItem.Sensitivity = schedule.sensitivity;
                appItem.Importance  = schedule.importance;
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

                return 0;
            }
            catch (System.Exception e) {
                MessageBox.Show(e.Message);
                return -1;
            }
            finally {
                // 接続解除
                DisconnectOutlook();
            }
        }

        // 予定取得
        public int GetSchedule(ref SCHEDULEOPTION[] schedule, string dt = "")
        {
            try {
                int i = 0;
                string filter = "";

                // 接続
                if (ConnectOutlook() != 0) {
                    return -1;
                }

                if (dt == "") {
                    dt = DateTime.Now.ToString("yyyy/MM/dd");
                }

                filter = "[Start] >= '" + dt + " 00:00' AND [Start] <= '" + dt + " 23:59'";
                AllItems = oNamespase.GetDefaultFolder(OlDefaultFolders.olFolderCalendar).Items;
                AllItems.IncludeRecurrences = true;
                AllItems.Sort("[Start]", Type.Missing);
                items = AllItems.Restrict(filter);

                foreach (AppointmentItem item in items) {
                    Array.Resize(ref schedule, i + 1);

                    schedule[i].subject     = item.Subject;
                    schedule[i].start       = item.Start;
                    schedule[i].end         = item.End;
                    schedule[i].allDayEvent = item.AllDayEvent;
                    schedule[i].location    = item.Location;
                    schedule[i].body        = item.Body;
                    schedule[i].categories  = item.Categories;
                    schedule[i].busyStatus  = item.BusyStatus;
                    schedule[i].reminderSet = item.ReminderSet;
                    schedule[i].sensitivity = item.Sensitivity;
                    schedule[i].importance  = item.Importance;

                    i++;
                }

                return 0;
            }
            catch (System.Exception e) {
                MessageBox.Show(e.Message);
                return -1;
            }
            finally {
                // 接続解除
                DisconnectOutlook();
            }
        }

        // 指定の予定の内容変更
        public int DeleteSchedule(string subject, string dt = "") {
            try {
                string filter = "";

                // 接続
                if (ConnectOutlook() != 0) {
                    return -1;
                }

                if (dt == "") {
                    dt = DateTime.Now.ToString("yyyy/MM/dd");
                }

                filter = "[Start] >= '" + dt + " 00:00' AND [Start] <= '" + dt + " 23:59'";
                AllItems = oNamespase.GetDefaultFolder(OlDefaultFolders.olFolderCalendar).Items;
                AllItems.IncludeRecurrences = true;
                AllItems.Sort("[Start]", Type.Missing);               
                items = AllItems.Restrict(filter);

                foreach (_AppointmentItem item in items) {
                    if (item.Subject == subject) {
                        item.Delete();
                        break;
                    }
                }

                return 0;
            }
            catch (System.Exception e) {
                MessageBox.Show(e.Message);
                return -1;
            }
            finally {
                // 接続解除
                DisconnectOutlook();
            }
        }

        // 分類取得
        public int GetCategory(ref string[] arrCategory)
        {
            try {
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

                return 0;
            }
            catch (System.Exception e) {
                MessageBox.Show(e.Message);
                return -1;
            }
            finally {
                // 接続解除
                DisconnectOutlook();
            }

        }
    }
}
