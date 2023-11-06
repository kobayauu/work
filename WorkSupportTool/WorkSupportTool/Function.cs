using Microsoft.Office.Interop.Outlook;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WorkSupportTool
{
    // マクロ定義
    static class Macros
    {
        // 情報保存ファイル
        public const string SCHEDULE_FILE = @"C:\Users\kobayauu\OneDrive - Brother\schedule.csv";
        public const string SETTING_FILE  = @"C:\Users\kobayauu\OneDrive - Brother\setting.csv";

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
    }

    internal class Function
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
        public string RoundTime(DateTime time, bool endFlag) {
            string tmpTime = "";
            int hour = 0;
            int minutes = 0;
            string[] tmp;

            tmpTime = time.ToString("H:m");
            tmp = tmpTime.Split(':');
            hour = int.Parse(tmp[0]);
            minutes = int.Parse(tmp[1]);

            if (!endFlag) {
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
            }
            else {
                if (minutes <= 15) {
                    minutes = 0;
                }
                else if ((minutes > 15) && (minutes <= 30)) {
                    minutes = 15;
                }
                else if ((minutes > 30) && (minutes <= 45)) {
                    minutes = 30;
                }
                else {
                    minutes = 45;
                }
            }

            return hour.ToString() + ":" + minutes.ToString();
        }
    }
}
