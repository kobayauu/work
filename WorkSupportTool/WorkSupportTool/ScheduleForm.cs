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
using static System.Windows.Forms.VisualStyles.VisualStyleElement.TaskbarClock;

namespace WorkSupportTool
{
    public partial class ScheduleForm : Form
    {
        CtrlOutlook ctrlOutlook = new CtrlOutlook();
        Function function = new Function();

        string[] arrCategory = new string[0];


        public ScheduleForm() {
            InitializeComponent();
        }

        private void ScheduleForm_Load(object sender, EventArgs e)
        {
            // データグリッドビューの設定
            // 行追加 
            for (int i = 0; i < Macros.MAX_ROW; i++) {
                dataGridView1.Rows.Add();
            }

            // 編集不可行列設定
            dataGridView1.Rows[Macros.HEADER_ROW1].ReadOnly = true;
            dataGridView1.Rows[Macros.HEADER_ROW2].ReadOnly = true;
            dataGridView1.Rows[Macros.SPLIT_ROW].ReadOnly = true;
            dataGridView1.Rows[Macros.MTG_ROW].ReadOnly = true;
            for (int i = Macros.TIME_COL; i < dataGridView1.ColumnCount; i++) {
                dataGridView1.Columns[i].ReadOnly = true;
            }
            dataGridView1[Macros.CATEGORY_COL, Macros.HEADER_ROW2].ReadOnly = false;

            // ヘッダーの背景色設定
            dataGridView1.Rows[Macros.HEADER_ROW1].DefaultCellStyle.BackColor = Color.LightCyan;
            dataGridView1.Rows[Macros.HEADER_ROW2].DefaultCellStyle.BackColor = Color.LightCyan;

            // ファイル読込
            string[] lines = new string[0];
            function.ReadCSVFile(Macros.SCHEDULE_FILE, ref lines);

            for (int i = 0; i < Macros.MAX_ROW; i++) {
                string[] values = lines[i].Split(',');

                for (int j = 0; j <= dataGridView1.ColumnCount; j++) {
                    if (j == 0) {
                        continue;
                    }

                    if ( (i < Macros.SCHEDULE_ROW) || (j <= Macros.TIME_COL) ) {
                        dataGridView1[j - 1, i].Value = values[j];
                    }
                    else {
                        // 予定・実績表示
                        if (values[j] == Macros.PLAN_STR) {
                            dataGridView1[j - 1, i].Value = Macros.PLAN_MARK;
                        }
                        else if (values[j] == Macros.ACHEIVE_STR) {
                            dataGridView1[j - 1, i].Style.BackColor = Macros.RESULT_COLOR;
                        }
                        else if (values[j] == Macros.AS_PLANED_STR) {
                            dataGridView1[j - 1, i].Value = Macros.PLAN_MARK;
                            dataGridView1[j - 1, i].Style.BackColor = Macros.RESULT_COLOR;
                        }
                        else if (values[j] == Macros.REST_STR) {
                            dataGridView1[j - 1, i].Style.BackColor = Macros.REST_COLOR;
                        }
                    }
                }
            }

            ctrlOutlook.GetCategory(ref arrCategory);
            for (int i = 1; i < Macros.MAX_ROW;i++) {
                int selectIndex = 0;
                string tmp = dataGridView1[Macros.CATEGORY_COL, i].Value.ToString();

                //指定セルにデータコンボボックスを作成
                dataGridView1[Macros.CATEGORY_COL, i] = new DataGridViewComboBoxCell();

                //既に入っているテキストデータがエラーの原因となるため初期化
                dataGridView1[Macros.CATEGORY_COL, i].Value = null;

                if (i == 1) {
                    ((DataGridViewComboBoxCell)dataGridView1[Macros.CATEGORY_COL, i]).Items.Add(Macros.PLAN_BTN);
                    ((DataGridViewComboBoxCell)dataGridView1[Macros.CATEGORY_COL, i]).Items.Add(Macros.ACHIEVE_BTN);
                    dataGridView1[Macros.CATEGORY_COL, i].Value = ((DataGridViewComboBoxCell)dataGridView1[Macros.CATEGORY_COL, i]).Items[0];
                }
                else {
                    //データコンボボックスのリストの内容を追加
                    ((DataGridViewComboBoxCell)dataGridView1[Macros.CATEGORY_COL, i]).Items.Add("");
                    for (int j = 0; j < arrCategory.Length; j++) {
                        ((DataGridViewComboBoxCell)dataGridView1[Macros.CATEGORY_COL, i]).Items.Add(arrCategory[j]);

                        if (tmp == arrCategory[j]) {
                            selectIndex = j + 1;
                        }
                    }

                    //データコンボボックスの初期値を設定
                    dataGridView1[Macros.CATEGORY_COL, i].Value = ((DataGridViewComboBoxCell)dataGridView1[Macros.CATEGORY_COL, i]).Items[selectIndex];
                }
            }

        }

        private void ScheduleForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            string[] lines = new string[Macros.MAX_ROW];
            int time = int.Parse(dataGridView1[Macros.TIME_COL, 0].Value.ToString());
            string tmp = "";

            // 1行目
            for (int i = Macros.TIME_COL; i < dataGridView1.ColumnCount; i++) {
                if ( (i != Macros.TIME_COL) && (i % Macros.TIME_COL == 0) ) {
                    time++;
                }
                tmp = tmp + time.ToString() + ",";
            }
            lines[0] = "0,やること(やったこと),メモ,成果物,PJ No," + tmp;

            // 2行目
            lines[1] = "0,やること(やったこと),メモ,成果物,PJ No,0,15,30,45,0,15,30,45,0,15,30,45,0,15,30,45,0,15,30,45,0,15,30,45," +
                                                                "0,15,30,45,0,15,30,45,0,15,30,45,0,15,30,45,0,15,30,45";

            // 3行目～
            for (int i = Macros.SCHEDULE_ROW; i < Macros.MAX_ROW; i++) {
                tmp = (i - 1).ToString();

                for (int j = 0; j < dataGridView1.ColumnCount; j++) {
                    string cell = "";
                    if (dataGridView1[j, i].Value != null) {
                        cell = dataGridView1[j, i].Value.ToString();
                    }

                    if (j < Macros.TIME_COL) {
                        tmp = tmp + "," + cell;
                    }
                    else {
                        if ( (cell == Macros.PLAN_MARK) && (dataGridView1[j, i].Style.BackColor == Macros.RESULT_COLOR) ) {
                            tmp = tmp + "," + Macros.AS_PLANED_STR;
                        }
                        else if ( (cell == "") && (dataGridView1[j, i].Style.BackColor == Macros.RESULT_COLOR) ) {
                            tmp = tmp + "," + Macros.ACHEIVE_STR;
                        }
                        else if ( (cell == Macros.PLAN_MARK) && (dataGridView1[j, i].Style.BackColor == default) ) {
                            tmp = tmp + "," + Macros.PLAN_STR;
                        }
                        else if (dataGridView1[j, i].Style.BackColor == Macros.REST_COLOR) {
                            tmp = tmp + "," + Macros.REST_STR;
                        }
                        else {
                            tmp = tmp + ",";
                        }
                    }
                }
                lines[i] = tmp;
            }

            function.WriteCSVFile(Macros.SCHEDULE_FILE, lines);
        }

        private void ClearButton_Click(object sender, EventArgs e)
        {
            CtrlOutlook.scheduleSetting[] gettingSchedule = new CtrlOutlook.scheduleSetting[0];
            string date = DateTime.Today.ToString("yyyy/MM/dd");
            int n = Macros.MTG_ROW + 1;
            string hours = "";
            string minutes = "";

            if (MessageBox.Show("クリアしますか？", "", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.No) {
                return;
            }

            // クリア
            for (int i = Macros.SCHEDULE_ROW; i < Macros.MAX_ROW; i++) {
                dataGridView1[Macros.SUBJECT_COL, i].Value = "";
                dataGridView1[Macros.MEMO_COL, i].Value = "";
                dataGridView1[Macros.ACHIEVE_COL, i].Value = "";
                dataGridView1[Macros.CATEGORY_COL, i].Value = "";
                dataGridView1[Macros.SUBJECT_COL, Macros.MTG_ROW].Value = "以下MTG";

                for (int j = Macros.TIME_COL; j < dataGridView1.ColumnCount; j++) {
                    dataGridView1[j, i].Value = "";
                    dataGridView1[j, i].Style.BackColor = default;
                }
            }

            // 予定表読込
            ctrlOutlook.GetSchedule(date, ref gettingSchedule);
            for (int i = 0; i < gettingSchedule.Length; i++) {
                if (gettingSchedule[i].categories != "その他" && gettingSchedule[i].allDayEvent != true) {
                    if (n == Macros.MAX_ROW) {
                        break;
                    }

                    // 件名
                    dataGridView1[0, n].Value = gettingSchedule[i].subject;
                    if (gettingSchedule[i].subject == "朝会") {
                        dataGridView1[1, n].Value = "進捗:、予定:";
                    }

                    bool startFlag = false;
                    int startCol = 0;
                    int endCol = dataGridView1.ColumnCount - 1;

                    // 予定
                    for (int j = Macros.TIME_COL; j < dataGridView1.ColumnCount; j++) {
                        if (dataGridView1[j, 0].Value != null) {
                            hours = dataGridView1[j, 0].Value.ToString();
                        }
                        minutes = dataGridView1[j, 1].Value.ToString();

                        if (startFlag) {
                            if (function.RoundTime(gettingSchedule[i].end, true) == hours + ":" + minutes) {
                                endCol = j;
                                startFlag = false;
                                break;
                            }
                        }
                        else {
                            if (function.RoundTime(gettingSchedule[i].start, false) == hours + ":" + minutes) {
                                startCol = j;
                                startFlag = true;
                            }
                        }
                    }

                    // なければスキップ
                    if (startCol == 0) {
                        continue;
                    }

                    // MTG予定を入力
                    for (int j = startCol; j < endCol; j++) {
                        dataGridView1[j, n].Value = Macros.PLAN_MARK;
                    }
                    if (endCol == dataGridView1.ColumnCount - 1) {
                        dataGridView1[endCol, n].Value = Macros.PLAN_MARK;
                    }
                    n++;
                }
            }

            // 休憩時間
            // ファイル読込
            string[] lines = new string[0];
            function.ReadCSVFile(Macros.SETTING_FILE, ref lines);
            for (int i = 0; i < lines.Length; i++) {
                string[] values = lines[i].Split(',');

                if (values[0] == "休み時間") {
                    for (int j = 1; j < values.Length; j++) {
                        for (int k = Macros.TIME_COL; k < dataGridView1.ColumnCount; k++) {
                            if (dataGridView1[k, 0].Value != null) {
                                hours = dataGridView1[k, 0].Value.ToString();
                            }
                            minutes = dataGridView1[k, 1].Value.ToString();
                            if (minutes.Length == 1) {
                                minutes = "0" + minutes;
                            }

                            if (values[j] == hours + ":" + minutes) {
                                for (int l = 2; l < Macros.MAX_ROW; l++) {
                                    dataGridView1[k, l].Style.BackColor = Macros.REST_COLOR;
                                }
                                break;
                            }
                        }
                    }
                }
                else if (values[0] == "定例会") {
                    for (int j = Macros.MTG_ROW + 1; j < Macros.MAX_ROW; j++) {
                        if (dataGridView1[Macros.SUBJECT_COL, j].Value != null) {
                            if (values[1] == dataGridView1[Macros.SUBJECT_COL, j].Value.ToString()) {
                                dataGridView1[Macros.CATEGORY_COL, j].Value = values[2];
                                break;
                            }
                        }
                    }
                }
            }
        }

        private void PostButton_Click(object sender, EventArgs e)
        {
            CtrlOutlook.scheduleSetting settingSchedule = new CtrlOutlook.scheduleSetting();
            CtrlOutlook.scheduleSetting settingSchedule2 = new CtrlOutlook.scheduleSetting();
            string body = "";
            string todayDate = DateTime.Today.ToString("yyyy/MM/dd");
            int[] arrWorkTime = new int[arrCategory.Length]; 

            if (MessageBox.Show(this, "Outlookに転記しますか？", "", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.No) {
                return;
            }

            // 各種設定
            settingSchedule.subject = "日報_" + todayDate;
            settingSchedule.start = DateTime.Now;
            settingSchedule.end = DateTime.Now;
            settingSchedule.allDayEvent = true;
            settingSchedule.importance = OlImportance.olImportanceNormal;

            // 本文
            for (int i = Macros.SCHEDULE_ROW; i < Macros.MAX_ROW; i++) {
                string subject = "";
                string category = "";
                string achieve = "";
                string memo = "";
                string time = "";
                int workTime = 0;

                if (i == Macros.SPLIT_ROW || i == Macros.MTG_ROW) {
                    continue;
                }

                for (int j = Macros.TIME_COL; j < dataGridView1.ColumnCount; j++) {
                    if (dataGridView1[j, i].Style.BackColor == Macros.RESULT_COLOR) {
                        workTime++;
                    }
                }
                            
                workTime = workTime * 15;
                subject = dataGridView1[Macros.SUBJECT_COL, i].Value.ToString();
                time = "　" + (workTime / 60).ToString("00") + ":" + (workTime % 60).ToString("00");
                category = dataGridView1[Macros.CATEGORY_COL, i].Value.ToString();
                achieve = "成果物<" + dataGridView1[Macros.ACHIEVE_COL, i].Value.ToString() + ">";
                memo = "メモ：" + dataGridView1[Macros.MEMO_COL, i].Value.ToString();

                if (subject != "") {
                    body = body + "・" + subject + "(" + category + time + ")\r\n" + achieve + "\r\n" + memo + "\r\n\r\n";
                }

                // 工数(後で使う)
                for (int j = 0; j < arrCategory.Length; j++) {
                    if (arrCategory[j] == dataGridView1[Macros.CATEGORY_COL, i].Value.ToString()) {
                        arrWorkTime[j] = arrWorkTime[j] + workTime;
                    }
                }

                // 予定入力
                bool startFlag = false;
                DateTime startTime = DateTime.Now;
                DateTime endTime = DateTime.Now;
                string hours = "";
                string minutes = "";
                string cell =  "";
                for (int j = Macros.TIME_COL; j < dataGridView1.ColumnCount; j++) {
                    if (dataGridView1[j, Macros.HEADER_ROW1].Value != null) {
                        hours = dataGridView1[j, Macros.HEADER_ROW1].Value.ToString();
                    }
                    minutes = dataGridView1[j, Macros.HEADER_ROW2].Value.ToString();

                    cell = "";
                    if (dataGridView1[j, i].Value != null) {
                        cell = dataGridView1[j, i].Value.ToString();
                    }

                    if (!startFlag) {
                        if (cell == Macros.PLAN_MARK) {
                            startFlag = true;
                            startTime = DateTime.Parse(DateTime.Now.ToString("yyyy/MM/dd") + " " + hours + ":" + minutes);
                        }
                    }
                    else {
                        if (cell != Macros.PLAN_MARK) {
                            startFlag = false;
                            endTime = DateTime.Parse(DateTime.Now.ToString("yyyy/MM/dd") + " " + hours + ":" + minutes);

                            settingSchedule2.subject = subject + "(予定)";
                            settingSchedule2.start = startTime;
                            settingSchedule2.end = endTime;
                            settingSchedule2.categories = "";
                            ctrlOutlook.SetSchedule(settingSchedule2, Macros.RESULT_FOLDER_NAME);
                        }

                        if (j == dataGridView1.ColumnCount - 1) {
                            startFlag = false;
                            minutes = ((int.Parse(minutes) + 15) % 60).ToString();
                            if (minutes == "0") {
                                hours = (int.Parse(hours) + 1).ToString();
                            }
                            endTime = DateTime.Parse(DateTime.Now.ToString("yyyy/MM/dd") + " " + hours + ":" + minutes);

                            settingSchedule2.subject = subject + "(予定)";
                            settingSchedule2.start = startTime;
                            settingSchedule2.end = endTime;
                            settingSchedule2.categories = "";
                            ctrlOutlook.SetSchedule(settingSchedule2, Macros.RESULT_FOLDER_NAME);
                        }
                    }
                }

                // 実績入力
                for (int j = Macros.TIME_COL; j < dataGridView1.ColumnCount; j++) {
                    if (dataGridView1[j, Macros.HEADER_ROW1].Value != null) {
                        hours = dataGridView1[j, Macros.HEADER_ROW1].Value.ToString();
                    }
                    minutes = dataGridView1[j, Macros.HEADER_ROW2].Value.ToString();

                    if (!startFlag) {
                        if (dataGridView1[j, i].Style.BackColor == Macros.RESULT_COLOR) {
                            startFlag = true;
                            startTime = DateTime.Parse(DateTime.Now.ToString("yyyy/MM/dd") + " " + hours + ":" + minutes);
                        }
                    }
                    else {
                        if (dataGridView1[j, i].Style.BackColor != Macros.RESULT_COLOR) {
                            startFlag = false;
                            endTime = DateTime.Parse(DateTime.Now.ToString("yyyy/MM/dd") + " " + hours + ":" + minutes);

                            settingSchedule2.subject = subject;
                            settingSchedule2.start = startTime;
                            settingSchedule2.end = endTime;
                            settingSchedule2.categories = category;
                            ctrlOutlook.SetSchedule(settingSchedule2, Macros.RESULT_FOLDER_NAME);
                        }

                        if (j == dataGridView1.ColumnCount - 1) {
                            startFlag = false;
                            minutes = ((int.Parse(minutes) + 15) % 60).ToString();
                            if (minutes == "0") {
                                hours = (int.Parse(hours) + 1).ToString();
                            }
                            endTime = DateTime.Parse(DateTime.Now.ToString("yyyy/MM/dd") + " " + hours + ":" + minutes);

                            settingSchedule2.subject = subject;
                            settingSchedule2.start = startTime;
                            settingSchedule2.end = endTime;
                            settingSchedule2.categories = category;
                            ctrlOutlook.SetSchedule(settingSchedule2, Macros.RESULT_FOLDER_NAME);
                        }
                    }
                }

            }
            settingSchedule.body = body;
            ctrlOutlook.SetSchedule(settingSchedule, Macros.RESULT_FOLDER_NAME);

            // クリップボードに工数をコピー
            string copyText = "";
            int[] copyNum = new int[arrCategory.Length];
            for (int i = 0; i < arrCategory.Length; i++) {
                string[] values = arrCategory[i].Split('_');
                int n = 0;

                if (int.TryParse(values[0], out n)) {
                    copyNum[n] = arrWorkTime[i];
                }              
            }

            for (int i = 0; i < copyNum.Length; i++) {
                copyText = copyText + (copyNum[i] / 60).ToString("00") + ":" + (copyNum[i] % 60).ToString("00") + "\t";
            }
            Clipboard.SetText(copyText);

            MessageBox.Show("Outlook予定表への転機を完了しました\nクリップボードへ工数をコピーしました", "", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        // ダブルクリックで計画・実績入力
        private void dataGridView1_CellDoubleClick(object sender, DataGridViewCellEventArgs e)
        {
            string cell = "";
            string mode = "";

            for (int i = 0; i < dataGridView1.SelectedCells.Count; i++) {
                int row = dataGridView1.SelectedCells[i].RowIndex;
                int col = dataGridView1.SelectedCells[i].ColumnIndex;

                if ((row < Macros.SCHEDULE_ROW) || (col < Macros.TIME_COL)) {
                    continue;
                }

                // 休憩は計画・実績入力不可
                if (dataGridView1[col, row].Style.BackColor == Macros.REST_COLOR) {
                    continue;
                }

                if (dataGridView1[col, row].Value != null) {
                    cell = dataGridView1[col, row].Value.ToString();
                }

                if (dataGridView1[Macros.CATEGORY_COL, Macros.HEADER_ROW2].Value != null) {
                    mode = dataGridView1[Macros.CATEGORY_COL, Macros.HEADER_ROW2].Value.ToString();
                }

                if (mode == Macros.PLAN_BTN) {
                    if (cell == "") {
                        dataGridView1[col, row].Value = Macros.PLAN_MARK;
                    }
                    else {
                        dataGridView1[col, row].Value = "";
                    }
                }
                else if (mode == Macros.ACHIEVE_BTN) {
                    if (dataGridView1[col, row].Style.BackColor == default) {
                        dataGridView1[col, row].Style.BackColor = Macros.RESULT_COLOR;
                    }
                    else {
                        dataGridView1[col, row].Style.BackColor = default;
                    }
                }
            }
        }

        // 指定したセルと1つ上のセルの値を比較
        bool IsTheSameCellValue(int column, int row, int mode)
        {
            DataGridViewCell cell1 = dataGridView1[column, row];
            DataGridViewCell cell2;

            if (mode == Macros.MODE_ROW) {
                cell2 = dataGridView1[column, row - 1];
            }
            else {
                cell2 = dataGridView1[column - 1, row];
            }

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
            int mode = Macros.MODE_ROW;

            // 1行目については何もしない
            if (( e.RowIndex == Macros.HEADER_ROW1) && (e.ColumnIndex < Macros.TIME_COL) ) {
                return;
            }
            if (e.RowIndex > Macros.HEADER_ROW2) {
                return;
            }

            if (e.ColumnIndex > Macros.CATEGORY_COL) {
                mode = Macros.MODE_COL;
            }

            if (IsTheSameCellValue(e.ColumnIndex, e.RowIndex, mode)) {
                e.Value = "";
                e.FormattingApplied = true; // 以降の書式設定は不要
            }
        }

        private void dataGridView1_CellPainting(object sender, DataGridViewCellPaintingEventArgs e)
        {
            // ヘッダー以外は何もしない
            if (e.RowIndex > Macros.HEADER_ROW1) {
                return;
            }

            // セルの下側・右側の境界線を「境界線なし」に設定
            if (e.ColumnIndex < Macros.TIME_COL) {
                e.AdvancedBorderStyle.Bottom = DataGridViewAdvancedCellBorderStyle.None;
            }
            else {
                e.AdvancedBorderStyle.Right = DataGridViewAdvancedCellBorderStyle.None;
            }

            // 1行目や列ヘッダ、行ヘッダの場合は何もしない
            if ( (e.RowIndex == Macros.HEADER_ROW1) && (e.ColumnIndex < Macros.TIME_COL) ) {
                return;
            }

            if (e.ColumnIndex < Macros.TIME_COL) {
                if (IsTheSameCellValue(e.ColumnIndex, e.RowIndex, Macros.MODE_ROW)) {
                    // セルの上側の境界線を「境界線なし」に設定
                    e.AdvancedBorderStyle.Top = DataGridViewAdvancedCellBorderStyle.None;
                }
                else {
                    // セルの上側の境界線を既定の境界線に設定
                    e.AdvancedBorderStyle.Top = dataGridView1.AdvancedCellBorderStyle.Top;
                }
            }
            if (e.ColumnIndex > Macros.TIME_COL) {
                if (IsTheSameCellValue(e.ColumnIndex, e.RowIndex, Macros.MODE_COL)) {
                    // セルの左側の境界線を「境界線なし」に設定
                    e.AdvancedBorderStyle.Left = DataGridViewAdvancedCellBorderStyle.None;
                }
                else {
                    // セルの左側の境界線を既定の境界線に設定
                    e.AdvancedBorderStyle.Left = dataGridView1.AdvancedCellBorderStyle.Left;
                }
            }
        }
    }
}
