using Microsoft.Office.Interop.Outlook;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WorkSupportTool
{
    static class Constants
    {
        public const int a = 0;
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
            else if ( (minutes >= 15) && (minutes < 30) ) {
                minutes = 15;
            }
            else if ( (minutes >= 30) && (minutes < 45) ) {
                minutes = 30;
            }
            else {
                minutes = 45;
            }

            return hour.ToString() + ":" + minutes.ToString();
        }
    }
}
