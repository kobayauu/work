using Microsoft.Office.Interop.Outlook;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Net.Mime.MediaTypeNames;
using Microsoft.VisualBasic;

namespace OutlookAddIn1
{
    public partial class ScheduleForm : Form
    {
        public System.Drawing.Color CELL_COLOR = Color.LightGreen;

        public ScheduleForm() {
            InitializeComponent();
        }

        private void ScheduleForm_Load(object sender, EventArgs e)
        {
            int m = 0;
            int row = 0;
            int col = 0;

            // データグリッドビューの設定
            // 行追加 
            for (int i = 0; i < 14; i++) {
                dataGridView1.Rows.Add();
            }

            // 編集不可
            dataGridView1.Rows[0].ReadOnly = true;
            dataGridView1.Rows[1].ReadOnly = true;
            dataGridView1.Rows[7].ReadOnly = true;
            dataGridView1.Rows[8].ReadOnly = true;
            for (int i = 4; i < 48; i++) {
                dataGridView1.Columns[i].ReadOnly = true;
            }

            // ヘッダーの背景色設定
            dataGridView1.Rows[0].DefaultCellStyle.BackColor = Color.LightCyan;
            dataGridView1.Rows[1].DefaultCellStyle.BackColor = Color.LightCyan;

            // ファイル読込
            StreamReader sr = new StreamReader(@"C:\Users\kobayauu\OneDrive - Brother\test.csv", Encoding.GetEncoding("Shift_JIS"));
            while (!sr.EndOfStream) {
                string line = sr.ReadLine();
                string[] values = line.Split(',');
                m = 0;
                col= 0;
                foreach (string value in values) {
                    if (m == 0) {
                        m++;
                        continue;
                    }

                    if (col < 4) {
                        dataGridView1[col, row].Value = value;
                    }
                    else {
                        if (row < 2) {
                            dataGridView1[col, row].Value = value;
                        }
                        else {
                            if (value == "1") {
                                dataGridView1[col, row].Style.BackColor = CELL_COLOR;
                            }
                        }
                    }
                    col++;
                }
                row++;

                if (row == 14) {
                    break;
                }
            }
            sr.Close();
        }


        private void ScheduleForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            int n = 1;
            int cycle = 0;
            StreamWriter sw = new StreamWriter(@"C:\Users\kobayauu\OneDrive - Brother\test.csv", false, Encoding.GetEncoding("Shift_JIS"));

            string startTime = dataGridView1[4, 0].Value.ToString();

            string str = "0,やること(やったこと),メモ,成果物,PJ No";
            for (int i = 4; i < 48; i++) {
                if (cycle == 4) {
                    startTime = (int.Parse(startTime) + 1).ToString();
                    cycle = 0;
                }
                str = str + "," + startTime;
                cycle++;
            }

            sw.WriteLine(str);
            str = "0,やること(やったこと),メモ,成果物,PJ No,0,15,30,45,0,15,30,45,0,15,30,45,0,15,30,45,0,15,30,45,0,15,30,45,0,15,30,45,0,15,30,45,0,15,30,45,0,15,30,45,0,15,30,45";
            sw.WriteLine(str);
            for (int i = 2; i < 14; i++) {
                str = n.ToString() + ",";
                n++;

                for (int j = 0; j < 48; j++) {
                    if (j < 4) {
                        if (dataGridView1[j, i].Value != null) {
                            str = str + dataGridView1[j, i].Value.ToString() + ",";
                        }
                        else {
                            str = str + "" + ",";
                        }
                    }
                    else {
                        if (dataGridView1[j, i].Style.BackColor == CELL_COLOR) {
                            str = str + "1" + ",";
                        }
                        else {
                            str = str + "" + ",";
                        }
                    }
                }
                sw.WriteLine(str);
            }
            sw.Close();

        }

        private void ClearButton_Click(object sender, EventArgs e)
        {
            int n = 9;
            bool startFlag = false;
            string hours = "";
            string minutes = "";
            int startCol = 0;
            int endCol = 47;

            if (MessageBox.Show("クリアしますか？", "予定表", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.No) {
                return;
            }

            string inputText;
            int cycle = 0;

            // 数値を入力するメッセージボックスを表示する
            this.TopMost = false;
            inputText = Interaction.InputBox("開始時間を入力してください", "予定表", "9", 0, 0);
            this.TopMost = true;

            if (inputText == "") {
                return;
            }

            for (int i = 4; i < 48; i++) {
                if (cycle == 4) {
                    inputText = (int.Parse(inputText) + 1).ToString();
                    cycle = 0;
                }
                dataGridView1[i, 0].Value = inputText;
                cycle++;
            }
            for (int i = 2; i < 14; i++) {
                dataGridView1[0, i].Value = "";
                dataGridView1[1, i].Value = "";
                dataGridView1[2, i].Value = "";
                dataGridView1[3, i].Value = "";

                for (int j = 4; j < 48; j++) {
                    dataGridView1[j, i].Style.BackColor = default;
                }
            }

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

            dataGridView1[0, 8].Value = "以下MTG";
            foreach (_AppointmentItem item in items) {
                if (item.Categories != "その他" && item.AllDayEvent != true) {
                    dataGridView1[0, n].Value = item.Subject;

                    startFlag = false;
                    startCol = 0;
                    endCol = 47;
                    for (int i = 4; i < 48; i++) {
                        if (dataGridView1[i, 0].Value.ToString() != "") {
                            hours = dataGridView1[i, 0].Value.ToString();
                        }
                        minutes = dataGridView1[i, 1].Value.ToString();

                        if (!startFlag) {
                            if (ConvertTime(item.Start) == hours + ":" + minutes) {
                                startCol = i;
                                startFlag = true;
                            }
                        }
                        else {
                            if (ConvertTime(item.End) == hours + ":" + minutes) {
                                endCol = i;
                                startFlag = false;
                                break;
                            }
                        }
                    }

                    if (startCol == 0) {
                        continue;
                    }

                    for (int i = startCol; i < endCol; i++) {
                        dataGridView1[i, n].Style.BackColor = CELL_COLOR;
                    }

                    if (endCol == 47) {
                        dataGridView1[47, n].Style.BackColor = CELL_COLOR;
                    }

                    n++;
                    if (n == 14) {
                        break;
                    }
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

        private string ConvertTime(DateTime time)
        {
            string tmpTime = "";
            string stMinutes = "";
            string[] tmp;
            int minutes = 0;

            stMinutes = time.ToString("H:mm");
            tmp = stMinutes.Split(':');
            minutes = int.Parse(tmp[1]);

            if (minutes < 15) {
                minutes = 0;
            }
            else if ( (minutes >= 15) && (minutes < 30) ) {
                minutes = 15;
            }
            else if ((minutes >= 30) && (minutes < 45)) {
                minutes = 30;
            }
            else if (minutes >= 45) {
                minutes = 45;
            }

            tmpTime = tmp[0] + ":" + minutes.ToString();

            return tmpTime;
        }

        private void CpolyButton_Click(object sender, EventArgs e)
        {
            string str = "";

            for (int i = 2; i < 14; i++) {
                for (int j = 0; j < 3; j++) {
                    if (dataGridView1[j, i].Value != null) {
                        str = str + dataGridView1[j, i].Value.ToString() + "\t";
                    }
                    else {
                        str = str + "" + "\t";
                    }
                }
                str = str + "\r\n";
            }

            // Excelにコピー
            Clipboard.SetText(str);
            MessageBox.Show("クリップボードにコピーしました", "予定表", MessageBoxButtons.OK, MessageBoxIcon.Information);

        }

        private void dataGridView1_CellDoubleClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex < 2) {
                return;
            }

            if (e.ColumnIndex < 4) {
                return;
            }

            if (dataGridView1[e.ColumnIndex, e.RowIndex].Style.BackColor != CELL_COLOR) {
                dataGridView1[e.ColumnIndex, e.RowIndex].Style.BackColor = CELL_COLOR;
            }
            else {
                dataGridView1[e.ColumnIndex, e.RowIndex].Style.BackColor = default;
            }
        }

        // 指定したセルと1つ上のセルの値を比較
        bool IsTheSameCellValue(int column, int row) {

            DataGridViewCell cell1 = dataGridView1[column, row];
            DataGridViewCell cell2 = dataGridView1[column, row - 1];

            if (cell1.Value == null || cell2.Value == null) {
                return false;
            }

            // ここでは文字列としてセルの値を比較
            if (cell1.Value.ToString() == cell2.Value.ToString()) {
                return true;
            }
            else {
                return false;
            }
        }

        // 指定したセルと1つ上のセルの値を比較
        bool IsTheSameCellValue2(int column, int row) {

            DataGridViewCell cell1 = dataGridView1[column, row];
            DataGridViewCell cell2 = dataGridView1[column - 1, row];

            if (cell1.Value == null || cell2.Value == null) {
                return false;
            }

            // ここでは文字列としてセルの値を比較
            if (cell1.Value.ToString() == cell2.Value.ToString()) {
                return true;
            }
            else {
                return false;
            }
        }

        private void dataGridView1_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            // 1行目については何もしない
            if (e.RowIndex == 0 && e.ColumnIndex < 4) {
                return;
            }

            if (e.RowIndex < 2 && e.ColumnIndex < 4) {
                if (IsTheSameCellValue(e.ColumnIndex, e.RowIndex)) {
                    e.Value = "";
                    e.FormattingApplied = true; // 以降の書式設定は不要
                }
            }

            if (e.RowIndex < 2 && e.ColumnIndex > 3) {
                if (IsTheSameCellValue2(e.ColumnIndex, e.RowIndex)) {
                    e.Value = "";
                    e.FormattingApplied = true; // 以降の書式設定は不要
                }
            }
        }

        private void dataGridView1_CellPainting(object sender, DataGridViewCellPaintingEventArgs e)
        {
            // セルの下側・右側の境界線を「境界線なし」に設定
            if (e.RowIndex < 1 && e.ColumnIndex < 4) {
                e.AdvancedBorderStyle.Bottom = DataGridViewAdvancedCellBorderStyle.None;
            }
            if (e.RowIndex < 1 && e.ColumnIndex > 3) {
                e.AdvancedBorderStyle.Right = DataGridViewAdvancedCellBorderStyle.None;
            }

            // 1行目や列ヘッダ、行ヘッダの場合は何もしない
            if (e.RowIndex == 0 && e.ColumnIndex < 4) {
                return;
            }

            if (e.RowIndex < 1 && e.ColumnIndex < 4) {
                if (IsTheSameCellValue(e.ColumnIndex, e.RowIndex)) {
                    // セルの上側の境界線を「境界線なし」に設定
                    e.AdvancedBorderStyle.Top = DataGridViewAdvancedCellBorderStyle.None;
                }
                else {
                    // セルの上側の境界線を既定の境界線に設定
                    e.AdvancedBorderStyle.Top = dataGridView1.AdvancedCellBorderStyle.Top;
                }
            }

            if (e.RowIndex < 1 && e.ColumnIndex > 4) {
                if (IsTheSameCellValue2(e.ColumnIndex, e.RowIndex)) {
                    // セルの上側の境界線を「境界線なし」に設定
                    e.AdvancedBorderStyle.Left = DataGridViewAdvancedCellBorderStyle.None;
                }
                else {
                    // セルの上側の境界線を既定の境界線に設定
                    e.AdvancedBorderStyle.Left = dataGridView1.AdvancedCellBorderStyle.Left;
                }
            }
        }
    }
}
