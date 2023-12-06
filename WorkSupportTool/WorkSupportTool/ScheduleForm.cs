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
    public partial class ScheduleForm : Form
    {
        string[] arrCategory = new string[0];


        public ScheduleForm() {
            InitializeComponent();
        }

        private void ScheduleForm_Load(object sender, EventArgs e)
        {
            string[] lines     = new string[0];
            string currentTime = Common.RoundTime(DateTime.Now);

            // データグリッドビューの設定
            // 行追加 
            for (int i = 0; i < Common.MAX_ROW; i++) {
                dataGridView1.Rows.Add();
            }

            // 編集不可行列設定
            dataGridView1.Rows[Common.HOUR_ROW].ReadOnly      = true;
            dataGridView1.Rows[Common.MINUTE_ROW].ReadOnly    = true;
            dataGridView1.Rows[Common.SPLIT_ROW].ReadOnly     = true;
            dataGridView1.Rows[Common.FIRST_MTG_ROW].ReadOnly = true;
            for (int i = Common.FIRST_TIME_COL; i < dataGridView1.ColumnCount; i++) {
                dataGridView1.Columns[i].ReadOnly = true;
            }
            dataGridView1[Common.CATEGORY_COL, Common.MINUTE_ROW].ReadOnly = false;

            // ヘッダーの背景色設定
            dataGridView1.Rows[Common.HOUR_ROW].DefaultCellStyle.BackColor = Color.LightCyan;
            dataGridView1.Rows[Common.MINUTE_ROW].DefaultCellStyle.BackColor = Color.LightCyan;

            // 計画/実績モード設定
            if (WorkSupportTool.Properties.Settings.Default.scheduleMode == 0) {
                PlanRadioButton.Checked = true;
            }
            else {
                AchieveRadioButton.Checked = true;
            }

            // ファイル読込
            Common.ctrlFile.ReadCSVFile(WorkSupportTool.Properties.Settings.Default.shcheduleFile, ref lines);
            for (int i = 0; i < Common.MAX_ROW; i++) {
                string[] values = lines[i].Split(',');

                for (int j = 0; j <= dataGridView1.ColumnCount; j++) {
                    if (j == 0) {
                        continue;
                    }

                    // やること、メモ、成果物
                    if ( (i < Common.FIRST_SCHEDULE_ROW) || (j <= Common.FIRST_TIME_COL) ) {
                        dataGridView1[j - 1, i].Value = values[j];
                    }
                    // 予定・実績
                    else {
                        if (values[j] == Common.PLAN_NUM) {
                            dataGridView1[j - 1, i].Value = Common.PLAN_MARK;
                        }
                        else if (values[j] == Common.ACHEIVE_NUM) {
                            dataGridView1[j - 1, i].Style.BackColor = Common.RESULT_COLOR;
                        }
                        else if (values[j] == Common.AS_PLANED_NUM) {
                            dataGridView1[j - 1, i].Value = Common.PLAN_MARK;
                            dataGridView1[j - 1, i].Style.BackColor = Common.RESULT_COLOR;
                        }
                        else if (values[j] == Common.REST_NUM) {
                            dataGridView1[j - 1, i].Style.BackColor = Common.REST_COLOR;
                        }
                    }
                }
            }

            // PJ No列設定
            Common.ctrlOutlook.GetCategory(ref arrCategory);
            for (int i = 2; i < Common.MAX_ROW;i++) {
                int selectIndex = 0;
                string tmp = dataGridView1[Common.CATEGORY_COL, i].Value.ToString();

                //指定セルにデータコンボボックスを作成
                dataGridView1[Common.CATEGORY_COL, i] = new DataGridViewComboBoxCell();

                //既に入っているテキストデータがエラーの原因となるため初期化
                dataGridView1[Common.CATEGORY_COL, i].Value = null;
             
                //データコンボボックスのリストの内容を追加
                ((DataGridViewComboBoxCell)dataGridView1[Common.CATEGORY_COL, i]).Items.Add("");
                for (int j = 0; j < arrCategory.Length; j++) {
                    ((DataGridViewComboBoxCell)dataGridView1[Common.CATEGORY_COL, i]).Items.Add(arrCategory[j]);

                    if (tmp == arrCategory[j]) {
                        selectIndex = j + 1;
                    }
                }

                //データコンボボックスの初期値を設定
                dataGridView1[Common.CATEGORY_COL, i].Value = ((DataGridViewComboBoxCell)dataGridView1[Common.CATEGORY_COL, i]).Items[selectIndex];
            }

            // 現在の時間列を強調           
            for (int i = 0; i < dataGridView1.ColumnCount; i++) {               
                string hours   = "";
                string minutes = "";

                if (dataGridView1[i, Common.HOUR_ROW].Value != null) {
                    hours = dataGridView1[i, Common.HOUR_ROW].Value.ToString();
                }
                minutes = dataGridView1[i, Common.MINUTE_ROW].Value.ToString();

                if (currentTime == hours + ":" + minutes) {
                    dataGridView1[i, Common.MINUTE_ROW].Style.BackColor = Common.CURRENT_COLOR;

                    for (int j = Common.FIRST_SCHEDULE_ROW; j < Common.MAX_ROW; j++) {
                        if (dataGridView1[i, j].Value != null) {
                            dataGridView1[Common.SUBJECT_COL, j].Style.BackColor = Common.CURRENT_COLOR;
                            dataGridView1[Common.MEMO_COL, j].Style.BackColor    = Common.CURRENT_COLOR;
                            dataGridView1[Common.ACHIEVE_COL, j].Style.BackColor = Common.CURRENT_COLOR;
                            break;
                        }
                    }
                    break;
                }
            }
        }

        private void ScheduleForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            string[] lines = new string[Common.MAX_ROW];

            // 計画/実績モード設定
            if (PlanRadioButton.Checked) {
                WorkSupportTool.Properties.Settings.Default.scheduleMode = 0;
            }
            else {
                WorkSupportTool.Properties.Settings.Default.scheduleMode = 1;
            }

            // ファイルへ編集結果更新(3行目～)
            Common.ctrlFile.ReadCSVFile(WorkSupportTool.Properties.Settings.Default.shcheduleFile, ref lines);            
            for (int i = Common.FIRST_SCHEDULE_ROW; i < Common.MAX_ROW; i++) {
                string tmp = (i - 1).ToString();

                for (int j = 0; j < dataGridView1.ColumnCount; j++) {
                    string cell = "";
                    if (dataGridView1[j, i].Value != null) {
                        cell = dataGridView1[j, i].Value.ToString();
                    }

                    if (j < Common.FIRST_TIME_COL) {
                        tmp = tmp + "," + cell;
                    }
                    else {
                        if ( (cell == Common.PLAN_MARK) && (dataGridView1[j, i].Style.BackColor == Common.RESULT_COLOR) ) {
                            tmp = tmp + "," + Common.AS_PLANED_NUM;
                        }
                        else if ( (cell == "") && (dataGridView1[j, i].Style.BackColor == Common.RESULT_COLOR) ) {
                            tmp = tmp + "," + Common.ACHEIVE_NUM;
                        }
                        else if ( (cell == Common.PLAN_MARK) && (dataGridView1[j, i].Style.BackColor == default) ) {
                            tmp = tmp + "," + Common.PLAN_NUM;
                        }
                        else if (dataGridView1[j, i].Style.BackColor == Common.REST_COLOR) {
                            tmp = tmp + "," + Common.REST_NUM;
                        }
                        else {
                            tmp = tmp + ",";
                        }
                    }
                }
                lines[i] = tmp;
            }

            Common.ctrlFile.WriteCSVFile(WorkSupportTool.Properties.Settings.Default.shcheduleFile, lines);
        }

        private void ClearButton_Click(object sender, EventArgs e)
        {
            CtrlOutlook.SCHEDULEOPTION[] gettingSchedule = new CtrlOutlook.SCHEDULEOPTION[0];
            int n          = Common.FIRST_MTG_ROW + 1;
            string hours   = "";
            string minutes = "";

            if (MessageBox.Show("クリアしますか？", "WorkSupportTool", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.No) {
                return;
            }

            // 計画/実績モード設定
            PlanRadioButton.Checked = true;

            // クリア
            for (int i = Common.FIRST_SCHEDULE_ROW; i < Common.MAX_ROW; i++) {
                dataGridView1[Common.SUBJECT_COL, i].Value                    = "";
                dataGridView1[Common.MEMO_COL, i].Value                       = "";
                dataGridView1[Common.ACHIEVE_COL, i].Value                    = "";
                dataGridView1[Common.CATEGORY_COL, i].Value                   = "";
                dataGridView1[Common.SUBJECT_COL, Common.FIRST_MTG_ROW].Value = "以下MTG";

                for (int j = Common.FIRST_TIME_COL; j < dataGridView1.ColumnCount; j++) {
                    if (dataGridView1[j, i].Style.BackColor != Common.REST_COLOR) {
                        dataGridView1[j, i].Value           = "";
                        dataGridView1[j, i].Style.BackColor = default;
                    }
                }
            }

            // 予定表から読込
            Common.ctrlOutlook.GetSchedule(ref gettingSchedule, dateTimePicker1.Value.ToString("yyyy/MM/dd"));
            for (int i = 0; i < gettingSchedule.Length; i++) {
                if ( (gettingSchedule[i].categories != "その他") && (gettingSchedule[i].allDayEvent != true) ) {
                    if (n == Common.MAX_ROW) {
                        break;
                    }

                    // 件名
                    dataGridView1[0, n].Value = gettingSchedule[i].subject;
                    if (gettingSchedule[i].subject == "朝会") {
                        dataGridView1[1, n].Value = "進捗：、予定：";
                    }

                    bool startFlag = false;
                    int startCol   = 0;
                    int endCol     = dataGridView1.ColumnCount - 1;

                    // 予定
                    for (int j = Common.FIRST_TIME_COL; j < dataGridView1.ColumnCount; j++) {
                        if (dataGridView1[j, 0].Value != null) {
                            hours = dataGridView1[j, 0].Value.ToString();
                        }
                        minutes = dataGridView1[j, 1].Value.ToString();

                        if (!startFlag) {
                            if (Common.RoundTime(gettingSchedule[i].start) == hours + ":" + minutes) {
                                startCol  = j;
                                startFlag = true;
                            }
                        }
                        else {
                            if (Common.RoundTime(gettingSchedule[i].end) == hours + ":" + minutes) {
                                endCol    = j;
                                startFlag = false;
                                break;
                            }
                        }
                    }

                    // なければスキップ
                    if (startCol == 0) {
                        continue;
                    }

                    // MTG予定入力
                    for (int j = startCol; j < endCol; j++) {
                        dataGridView1[j, n].Value = Common.PLAN_MARK;
                    }
                    if (endCol == dataGridView1.ColumnCount - 1) {
                        dataGridView1[endCol, n].Value = Common.PLAN_MARK;
                    }
                    n++;
                }
            }

            // 定例MTGのPJ No設定
            string[] lines = WorkSupportTool.Properties.Settings.Default.regularMTG.Split(',');
            for (int i = 0; i < lines.Length; i++) {
                for (int j = Common.FIRST_MTG_ROW + 1; j < Common.MAX_ROW; j++) {
                    string[] values = lines[i].Split('-');

                    if (dataGridView1[Common.SUBJECT_COL, j].Value != null) {
                        if (values[0] == dataGridView1[Common.SUBJECT_COL, j].Value.ToString()) {
                            dataGridView1[Common.CATEGORY_COL, j].Value = values[1];
                            break;
                        }
                    }
                }
            }
        }

        private void PostButton_Click(object sender, EventArgs e)
        {
            CtrlOutlook.SCHEDULEOPTION settingSchedule = new CtrlOutlook.SCHEDULEOPTION();
            int[] arrWorkTime                          = new int[arrCategory.Length]; 

            if (MessageBox.Show(this, "Outlookへ実績を記入しますか？", "WorkSupportTool", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.No) {
                return;
            }

            // 本文
            for (int i = Common.FIRST_SCHEDULE_ROW; i < Common.MAX_ROW; i++) {
                int workTime    = 0;
                string subject  = "";
                string category = "";

                if (i == Common.SPLIT_ROW || i == Common.FIRST_MTG_ROW) {
                    continue;
                }

                // 工数(後で使う)
                for (int j = Common.FIRST_TIME_COL; j < dataGridView1.ColumnCount; j++) {
                    if (dataGridView1[j, i].Style.BackColor == Common.RESULT_COLOR) {
                        workTime++;
                    }
                }             
                workTime = workTime * 15;

                for (int j = 0; j < arrCategory.Length; j++) {
                    if (arrCategory[j] == dataGridView1[Common.CATEGORY_COL, i].Value.ToString()) {
                        arrWorkTime[j] = arrWorkTime[j] + workTime;
                    }
                }

                // 以前転記して時間が残っていたら削除
                subject = dataGridView1[Common.SUBJECT_COL, i].Value.ToString();
                category = dataGridView1[Common.CATEGORY_COL, i].Value.ToString();
                string[] tmp = subject.Split('(');
                if (tmp.Length != 0) {
                    subject = tmp[0];
                }

                if (workTime != 0) {
                    dataGridView1[Common.SUBJECT_COL, i].Value = subject + "(" + (workTime / 60).ToString("00") + ":" + (workTime % 60).ToString("00") + ")";
                }
                else {
                    dataGridView1[Common.SUBJECT_COL, i].Value = subject;
                }

                // 予定表から取得したものはOutlookに転記しない
                if (i > Common.SPLIT_ROW) {
                    continue;
                }

                // 実績入力
                bool startFlag     = false;
                DateTime startTime = dateTimePicker1.Value;
                DateTime endTime   = dateTimePicker1.Value;
                string hours       = "";
                string minutes     = "";
                for (int j = Common.FIRST_TIME_COL; j < dataGridView1.ColumnCount; j++) {
                    if (dataGridView1[j, Common.HOUR_ROW].Value != null) {
                        hours = dataGridView1[j, Common.HOUR_ROW].Value.ToString();
                    }
                    minutes = dataGridView1[j, Common.MINUTE_ROW].Value.ToString();

                    if (!startFlag) {
                        if (dataGridView1[j, i].Style.BackColor == Common.RESULT_COLOR) {
                            startFlag = true;
                            startTime = DateTime.Parse(dateTimePicker1.Value.ToString("yyyy/MM/dd") + " " + hours + ":" + minutes);
                        }
                    }
                    else {
                        if (dataGridView1[j, i].Style.BackColor != Common.RESULT_COLOR) {
                            // 最終列の場合、ちょっと調整
                            if (j == dataGridView1.ColumnCount - 1) {
                                minutes = ((int.Parse(minutes) + 15) % 60).ToString();
                                if (minutes == "0") {
                                    hours = (int.Parse(hours) + 1).ToString();
                                }
                            }
                            startFlag = false;
                            endTime = DateTime.Parse(dateTimePicker1.Value.ToString("yyyy/MM/dd") + " " + hours + ":" + minutes);

                            settingSchedule.subject     = subject;
                            settingSchedule.start       = startTime;
                            settingSchedule.end         = endTime;
                            settingSchedule.categories  = category;
                            settingSchedule.importance  = OlImportance.olImportanceNormal;
                            settingSchedule.sensitivity = OlSensitivity.olPrivate;
                            Common.ctrlOutlook.SetSchedule(settingSchedule);
                        }
                    }
                }
            }

            MessageBox.Show("Outlookへの実績を記入しました", "WorkSupportTool", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void CopyButton_Click(object sender, EventArgs e)
        {
            int[] arrWorkTime = new int[arrCategory.Length];
            string copyText   = "";

            // 工数計算
            for (int i = Common.FIRST_SCHEDULE_ROW; i < Common.MAX_ROW; i++) {
                int workTime = 0;

                if ( (i == Common.SPLIT_ROW) || (i == Common.FIRST_MTG_ROW) ) {
                    continue;
                }

                for (int j = Common.FIRST_TIME_COL; j < dataGridView1.ColumnCount; j++) {
                    if (dataGridView1[j, i].Style.BackColor == Common.RESULT_COLOR) {
                        workTime++;
                    }
                }

                workTime = workTime * 15;
                for (int j = 0; j < arrCategory.Length; j++) {
                    if (arrCategory[j] == dataGridView1[Common.CATEGORY_COL, i].Value.ToString()) {
                        arrWorkTime[j] = arrWorkTime[j] + workTime;
                    }
                }
            }

            // クリップボードに工数をコピー 
            for (int i = 0; i < arrWorkTime.Length; i++) {
                copyText = copyText + (arrWorkTime[i] / 60).ToString("00") + ":" + (arrWorkTime[i] % 60).ToString("00") + "\t";
            }
            Clipboard.SetText(copyText);
            MessageBox.Show("クリップボードへ工数をコピーしました", "WorkSupportTool", MessageBoxButtons.OK, MessageBoxIcon.Information);
            System.Diagnostics.Process.Start(WorkSupportTool.Properties.Settings.Default.worktimeURL);
        }

        // ダブルクリックで計画・実績入力
        private void dataGridView1_CellDoubleClick(object sender, DataGridViewCellEventArgs e)
        {
            string cell = "";

            for (int i = 0; i < dataGridView1.SelectedCells.Count; i++) {
                int row = dataGridView1.SelectedCells[i].RowIndex;
                int col = dataGridView1.SelectedCells[i].ColumnIndex;

                if ( (row < Common.FIRST_SCHEDULE_ROW) || (col < Common.FIRST_TIME_COL) ) {
                    continue;
                }

                // 休憩は計画・実績入力不可
                if (dataGridView1[col, row].Style.BackColor == Common.REST_COLOR) {
                    continue;
                }

                if (dataGridView1[col, row].Value != null) {
                    cell = dataGridView1[col, row].Value.ToString();
                }

                if (PlanRadioButton.Checked) {
                    if (cell == "") {
                        dataGridView1[col, row].Value = Common.PLAN_MARK;
                    }
                    else {
                        dataGridView1[col, row].Value = "";
                    }
                }
                else {
                    if (dataGridView1[col, row].Style.BackColor == default) {
                        dataGridView1[col, row].Style.BackColor = Common.RESULT_COLOR;
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

            if (mode == Common.CHECK_ROW_MODE) {
                cell2 = dataGridView1[column, row - 1];
            }
            else {
                cell2 = dataGridView1[column - 1, row];
            }

            if ( (cell1.Value == null) || (cell2.Value == null) ) {
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
            int mode = Common.CHECK_ROW_MODE;

            // 1行目については何もしない
            if ( (e.RowIndex == Common.HOUR_ROW) && (e.ColumnIndex < Common.FIRST_TIME_COL) ) {
                return;
            }
            if (e.RowIndex > Common.MINUTE_ROW) {
                return;
            }

            if (e.ColumnIndex > Common.CATEGORY_COL) {
                mode = Common.CHECK_COL_MODE;
            }

            if (IsTheSameCellValue(e.ColumnIndex, e.RowIndex, mode)) {
                e.Value = "";
                e.FormattingApplied = true; // 以降の書式設定は不要
            }
        }

        private void dataGridView1_CellPainting(object sender, DataGridViewCellPaintingEventArgs e)
        {
            // ヘッダー以外は何もしない
            if (e.RowIndex > Common.HOUR_ROW) {
                return;
            }

            // セルの下側・右側の境界線を「境界線なし」に設定
            if (e.ColumnIndex < Common.FIRST_TIME_COL) {
                e.AdvancedBorderStyle.Bottom = DataGridViewAdvancedCellBorderStyle.None;
            }
            else {
                e.AdvancedBorderStyle.Right = DataGridViewAdvancedCellBorderStyle.None;
            }

            // 1行目や列ヘッダ、行ヘッダの場合は何もしない
            if ( (e.RowIndex == Common.HOUR_ROW) && (e.ColumnIndex < Common.FIRST_TIME_COL) ) {
                return;
            }

            if (e.ColumnIndex < Common.FIRST_TIME_COL) {
                if (IsTheSameCellValue(e.ColumnIndex, e.RowIndex, Common.CHECK_ROW_MODE)) {
                    // セルの上側の境界線を「境界線なし」に設定
                    e.AdvancedBorderStyle.Top = DataGridViewAdvancedCellBorderStyle.None;
                }
                else {
                    // セルの上側の境界線を既定の境界線に設定
                    e.AdvancedBorderStyle.Top = dataGridView1.AdvancedCellBorderStyle.Top;
                }
            }
            if (e.ColumnIndex > Common.FIRST_TIME_COL) {
                if (IsTheSameCellValue(e.ColumnIndex, e.RowIndex, Common.CHECK_COL_MODE)) {
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
