//Confidential
//Copyright (C) 2023 Brother Industries, Ltd. All Rights Reserved.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace GTX700PBHotFolder
{
    static class Program
    {
        /// <summary>
        /// アプリケーションのメイン エントリ ポイントです。
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new MainForm());
        }
    }
}
