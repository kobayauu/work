using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Net.Mime.MediaTypeNames;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace CtrlPC
{
    public partial class Form1 : Form
    {
        private bool cancelFlag = false;

        private const int MOUSEEVENTF_LEFTDOWN = 0x2;
        private const int MOUSEEVENTF_LEFTUP = 0x4;

        [DllImport("USER32.dll", CallingConvention = CallingConvention.StdCall)]
        static extern void SetCursorPos(int X, int Y);

        [DllImport("USER32.dll", CallingConvention = CallingConvention.StdCall)]
        static extern void mouse_event(int dwFlags, int dx, int dy, int cButtons, int dwExtraInfo);

        [DllImport("user32.dll")]
        private static extern short GetAsyncKeyState(int vKey);

        public Form1()
        {
            InitializeComponent();

            // 実行ファイルと同じフォルダに関数ファイルがあれば、関数ファイルのパスを表示
            if (File.Exists(AppDomain.CurrentDomain.BaseDirectory + "func.csv") == true)
            {
                FuncFiletextBox.Text = AppDomain.CurrentDomain.BaseDirectory + "func.csv";
            }
        }

        private void RefCtrlFilebutton_Click(object sender, EventArgs e)
        {
            CtrlFiletextBox.Text = GetFilePath();
        }

        private void RefFuncFilebutton_Click(object sender, EventArgs e)
        {
            FuncFiletextBox.Text = GetFilePath();
        }

        private void Startbutton_Click(object sender, EventArgs e)
        {
            List<string> ctrlLists = new List<string>();
            List<string> funcLists = new List<string>();

            DialogResult result = MessageBox.Show("PC操作を開始します。", "CtrlPC", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            if (result == DialogResult.OK)
            {
                // 操作ファイル読込
                if (ReadCSV(CtrlFiletextBox.Text, ctrlLists) != 0)
                {
                    return;
                }

                // 関数ファイル読込
                if (ReadCSV(FuncFiletextBox.Text, funcLists) != 0)
                {
                    return;
                }

                // ボタンを無効化
                RefCtrlFilebutton.Enabled = false;
                RefFuncFilebutton.Enabled = false;
                Startbutton.Enabled = false;
                RecordStartbutton.Enabled = false;
                Closebutton.Enabled = false;
                CtrlFiletextBox.Enabled = false;
                FuncFiletextBox.Enabled = false;
                OutputtextBox.Enabled = false;

                // 操作ファイルに従い、PC操作
                cancelFlag = false;
                OutputtextBox.Text = "";
                OutputtextBox.Refresh();
                CtrlFiletextBox.Refresh();
                FuncFiletextBox.Refresh();
                System.Threading.Thread.Sleep(1000);
                foreach (string list in ctrlLists)
                {
                    // 「ESC」キーで中断
                    if (GetAsyncKeyState((int)System.Windows.Forms.Keys.Escape) != 0)
                    {
                        cancelFlag = true;
                        break;
                    }
                    CtrlMotion(list, funcLists);
                }

                // ボタンを有効化
                RefCtrlFilebutton.Enabled = true;
                RefFuncFilebutton.Enabled = true;
                Startbutton.Enabled = true;
                RecordStartbutton.Enabled = true;
                Closebutton.Enabled = true;
                CtrlFiletextBox.Enabled = true;
                FuncFiletextBox.Enabled = true;
                OutputtextBox.Enabled = true;

                if (cancelFlag == false)
                {
                    MessageBox.Show("PC操作を終了しました。", "CtrlPC", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
                }
                else
                {
                    MessageBox.Show("PC操作を中断しました。", "CtrlPC", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
                }
            }
        }

        private void RecordStartbutton_Click(object sender, EventArgs e)
        {
            int x = 0;
            int y = 0;
            bool startFlag = false;

            cancelFlag = false;

            DialogResult result = MessageBox.Show("マウス位置を記録します。", "CtrlPC", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            if (result == DialogResult.OK)
            {
                // ボタンを無効化
                RefCtrlFilebutton.Enabled = false;
                RefFuncFilebutton.Enabled = false;
                Startbutton.Enabled = false;
                Closebutton.Enabled = false;
                CtrlFiletextBox.Enabled = false;
                FuncFiletextBox.Enabled = false;
                RecordStartbutton.Enabled = false;
                RecordCancelbutton.Enabled = true;
                OutputtextBox.Enabled = false;

                // クリックした位置を取得
                OutputtextBox.Text = "";
                OutputtextBox.Refresh();
                System.Threading.Thread.Sleep(1000);
                while (true)
                {
                    //待機中のイベントを処理する
                    System.Windows.Forms.Application.DoEvents();

                    //キャンセルボタンがクリックされたか調べる
                    if (cancelFlag == true)
                    {
                        //キャンセルされた時、ループを抜ける
                        break;
                    }

                    if (GetAsyncKeyState((int)System.Windows.Forms.Keys.LButton) != 0)
                    {
                        if (startFlag == true)
                        {
                            x = Cursor.Position.X;
                            y = Cursor.Position.Y;

                            OutputtextBox.AppendText(x.ToString().PadRight(6) + y.ToString() + "\r\n");
                            OutputtextBox.Refresh();
                        }

                        // 記録開始時のクリック位置を記録させないようにする
                        if (startFlag == false)
                        {
                            startFlag = true;
                        }

                        System.Threading.Thread.Sleep(500);
                    }
                }

                // ボタンを有効化
                RefCtrlFilebutton.Enabled = true;
                RefFuncFilebutton.Enabled = true;
                Startbutton.Enabled = true;
                Closebutton.Enabled = true;
                CtrlFiletextBox.Enabled = true;
                FuncFiletextBox.Enabled = true;
                RecordStartbutton.Enabled = true;
                RecordCancelbutton.Enabled = false;
                OutputtextBox.Enabled = true;
            }
        }

        private void RecordCancelbutton_Click(object sender, EventArgs e)
        {
            cancelFlag = true;
        }

        private void Closebutton_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        // ファイル選択ダイアログ
        private string GetFilePath()
        {
            string filePath = "";

            using (OpenFileDialog openFileDialog = new OpenFileDialog())
            {
                openFileDialog.Filter = "csv files (*.csv)|*.csv";
                openFileDialog.FilterIndex = 2;
                openFileDialog.RestoreDirectory = true;

                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    filePath = openFileDialog.FileName;
                }
            }

            return filePath;
        }

        // CSVファイル読込
        private int ReadCSV(string filePath, List<string> lists)
        {
            if ((filePath == "") || (File.Exists(filePath) == false))
            {
                MessageBox.Show("ファイルが存在しません。", "Error", MessageBoxButtons.OKCancel, MessageBoxIcon.Exclamation);
                return -1;
            }

            using (StreamReader sr = new StreamReader(filePath, Encoding.GetEncoding("Shift_JIS")))
            {
                while (sr.Peek() > -1)
                {
                    lists.Add(sr.ReadLine());
                }
            }

            return 0;
        }

        // PC操作
        private void CtrlMotion(string list, List<string> funcLists)
        {
            string[] values = list.Split(',');
            bool sleepFlag = true;
            string commentout = "";
            string command = "";
            string arg1, arg2, arg3, arg4;

            commentout = values[0];
            command = values[1];
            arg1 = values[2];
            arg2 = values[3];
            arg3 = values[4];
            arg4 = values[5];

            // コメントアウトした行は処理しない
            if (commentout != "")
            {
                return;
            }

            switch (command)
            {
                // 待機(Sleep)
                case "Sleep":
                    System.Threading.Thread.Sleep(int.Parse(arg1));
                    break;

                // 移動してクリック
                case "PosClick":
                    SetCursorPos(int.Parse(arg1), int.Parse(arg2));
                    for (int i = 0; i < int.Parse(arg3); i++)
                    {
                        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                    }
                    break;

                // 文字入力
                case "Input":
                    Clipboard.SetText(arg1);
                    System.Threading.Thread.Sleep(100);
                    SendKeys.Send("^(v)");
                    System.Threading.Thread.Sleep(100);
                    break;

                // ドラッグ
                case "Drug":
                    // 開始地点に移動し、マウスの左クリックを押す
                    SetCursorPos(int.Parse(arg1), int.Parse(arg2));
                    System.Threading.Thread.Sleep(200);
                    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);

                    System.Threading.Thread.Sleep(200);

                    // 終了地点に移動し、マウスの左クリックを離す
                    SetCursorPos(int.Parse(arg3), int.Parse(arg4));
                    System.Threading.Thread.Sleep(200);
                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                    break;

                // 「Delete」キー押下
                case "Delete":
                    SendKeys.Send("{DELETE}");
                    break;

                // 「Enter」キー押下
                case "Enter":
                    SendKeys.Send("{ENTER}");
                    break;

                // 情報のコピー
                case "Copy":
                    SendKeys.Send("^(c)");
                    System.Threading.Thread.Sleep(200);

                    if (Clipboard.ContainsText())
                    {
                        string str = Clipboard.GetText();
                        OutputtextBox.AppendText(str + ", " + arg1 + "\r\n");
                        OutputtextBox.Refresh();
                        System.Windows.Forms.Application.DoEvents();
                    }
                    break;

                // ファイルのオープン
                case "Open":
                    System.Diagnostics.ProcessStartInfo psi = new System.Diagnostics.ProcessStartInfo();
                    psi.FileName = arg1;
                    psi.WindowStyle = System.Diagnostics.ProcessWindowStyle.Maximized;
                    System.Diagnostics.Process p = System.Diagnostics.Process.Start(psi);
                    break;

                // 関数(使い回す処理のまとまりで別シートに記載)
                case "Func":
                    bool endFlag = false;
                    string funcCommand = "";

                    foreach (string funcList in funcLists)
                    {
                        string[] funcValues = funcList.Split(',');
                        funcCommand = funcValues[1];

                        // 関数名が一致したら、関数の処理を開始
                        if ((endFlag == false) && (funcCommand == arg1))
                        {
                            endFlag = true;

                        }
                        else if ((endFlag == true) && (funcCommand != ""))
                        {
                            CtrlMotion(funcList, funcLists);

                        }
                        // 関数名が空白なら、関数の処理を終了
                        else if ((endFlag == true) && (funcCommand == ""))
                        {
                            break;
                        }
                    }
                    break;

                default:
                    sleepFlag = false;
                    break;
            }

            if (sleepFlag == true)
            {
                System.Threading.Thread.Sleep(200);
            }
        }
    }
}
