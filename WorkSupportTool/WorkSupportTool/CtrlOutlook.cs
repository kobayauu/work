using Microsoft.Office.Interop.Outlook;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WorkSupportTool
{
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
                this.allDayEvent = false;
                this.busyStatus = OlBusyStatus.olFree;
                this.reminderSet = false;
                this.importance = OlImportance.olImportanceNormal;
            }
        }
        /****************************************************************************************************/


        private int ConnectOutlook()
        {
            app = new Microsoft.Office.Interop.Outlook.Application();
            oNamespase = app.GetNamespace("MAPI");
            oNamespase.Logon(null, null, true, true);

            isConnect = true;
            return 0;
        }

        private void DisconnectOutlook()
        {
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
        public int SetSchedule(scheduleSetting schedule, string folderName)
        {
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
        public int GetSchedule(string date, ref scheduleSetting[] schedule)
        {
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
        public int ChangeSchedule(string date, string subject, scheduleSetting schedule)
        {
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
        public int GetCategory(ref string[] arrCategory)
        {
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

            // 接続解除
            DisconnectOutlook();

            return 0;
        }
    }
}
