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

namespace OutlookAddIn1
{
    public partial class Ribbon1
    {
        MainForm mainForm = new MainForm();

        private void Ribbon1_Load(object sender, RibbonUIEventArgs e)
        {
            int n = 0;
            string[] arrCategories = new string[1];

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

            // 分類取得
            Microsoft.Office.Interop.Outlook.Application app = new Microsoft.Office.Interop.Outlook.Application();
            NameSpace oNamespase = app.GetNamespace("MAPI");
            _AppointmentItem appItem = appItem = (_AppointmentItem)app.CreateItem(OlItemType.olAppointmentItem);
            oNamespase.Logon(null, null, true, true);
            foreach (Microsoft.Office.Interop.Outlook.Category caterory in oNamespase.Categories) {
                Array.Resize(ref arrCategories, n + 1);
                arrCategories[n] = caterory.Name;
                n++;
            }

            // メインフォーム表示
            mainForm.SetCategory(arrCategories);
            mainForm.Show();
        }

        private void homeWorkButton_Click(object sender, RibbonControlEventArgs e) {
            bool ishomeFlag = false;
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

            foreach (_AppointmentItem item in items) {
                if (item.Subject == "在宅(勤務中)") {
                    ishomeFlag = true;
                    if (MessageBox.Show("在宅を終了しますか？", "確認", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes) {
                        item.Subject = "在宅(退勤)";
                        item.Save();
                    }
                    break;
                }
            }

            if (!ishomeFlag) {
                if (MessageBox.Show("在宅を開始しますか？", "確認", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes) {
                    appItem.Subject = "在宅(勤務中)";
                    appItem.AllDayEvent = true;
                    appItem.BusyStatus = OlBusyStatus.olWorkingElsewhere;
                    appItem.ReminderSet = false;
                    appItem.Importance = OlImportance.olImportanceNormal;
                    appItem.Close(OlInspectorClose.olSave);
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
    }
}
