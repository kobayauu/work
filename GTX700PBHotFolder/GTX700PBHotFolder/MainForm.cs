//Confidential
//Copyright (C) 2023 Brother Industries, Ltd. All Rights Reserved.
using System;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;

namespace GTX700PBHotFolder
{
    public partial class MainForm : Form
    {
        private Settings setting;

        public MainForm()
        {
            InitializeComponent();
        }
        private void MainForm_Load(object sender, EventArgs e)
        {
            string file = Path.ChangeExtension(Application.ExecutablePath, @".xml");
            setting = new Settings(0);
            Utility.LoadXML(file, ref setting);
            // setting.LoadXML();
            InitHotFolder();
            PathHotFolder(setting.Input);
        }
        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            EnableHotFolder(false);
            ExitHotFolder();
        }

        private void btnSetting_Click(object sender, EventArgs e)
        {
            EnableHotFolder(false);
            if(setting.Config())
            {
                string file = Path.ChangeExtension(Application.ExecutablePath, @".xml");
                Utility.SaveXML(file, setting);
                // setting.SaveXML();
                PathHotFolder(setting.Input);
            }
            EnableHotFolder(checkHotFolder.Checked);
        }

        private void checkHotFolder_CheckedChanged(object sender, EventArgs e)
        {
            EnableHotFolder(checkHotFolder.Checked);
            btnSetting.Enabled = !checkHotFolder.Checked;
        }

        // Watch Folder

        private FileSystemWatcher watcher;

        private void InitHotFolder()
        {
            watcher                       = new FileSystemWatcher();
            watcher.NotifyFilter          = NotifyFilters.LastAccess | NotifyFilters.FileName;
            watcher.IncludeSubdirectories = true;
            watcher.Filter                = @"*.png";
            watcher.SynchronizingObject   = this;
            watcher.Created              += new FileSystemEventHandler(watcher_Created);
        }
        private void ExitHotFolder()
        {
            watcher.Dispose();
        }
        private void PathHotFolder(string path)
        {
            watcher.Path                  = path;
        }
        private void EnableHotFolder(bool flag)
        {
            watcher.EnableRaisingEvents   = flag;
        }

        private void watcher_Created(object source, FileSystemEventArgs e)
        {
            if (e.ChangeType != WatcherChangeTypes.Created)
            {
                return;
            }

            string[] array = Path.GetFileNameWithoutExtension(e.Name).Split('_');
            if (array.Length == 6)
            {
                string setupfile= Path.GetFullPath(Path.Combine(setting.Setup, array[0] + @".xml"));
                string table    = array[1];
                string name     = array[2];
                string ext      = Path.GetExtension(e.Name);
                int    copies   = int.Parse(array[3]);
                // string pos      = String.Format(@"{0},{1}", int.Parse(array[4]), int.Parse(array[5]));
                string pos      = String.Format(@"{0},{1}", 0, int.Parse(array[5]));

                var setup = new Setup(0);
                Utility.LoadXML(setupfile, ref setup);

                string rate     = String.Format(@"{0:0000}", setup.Rate);
                string profile  = Path.GetFullPath(Path.Combine(setting.Profile, setup.Profile));
                string infile   = Path.GetFullPath(e.FullPath);
                // string outfile  = Path.GetFullPath(Path.Combine(setting.Output, Path.ChangeExtension(e.Name, @".arx4")));
                string backfile = Path.GetFullPath(Path.Combine(setting.Backup, e.Name));
                string pritner  = setup.Printer;
                // CheckFile(outfile);
                CheckFile(backfile);
                string probak = ModifyProfile(profile, table, copies);
                string inbak  = ModifyInfile(infile, name, ext);

                string arguments = String.Format(@"print -X ""{0}"" -I ""{1}"" -P ""{2}"" -O ""{3}"" -R ""{4}"" -W 1", 
                                                    probak, inbak, pritner, pos, rate);
                //string arguments = String.Format(@"print -X ""{0}"" -I ""{1}"" -P ""{2}"" -O ""{3}"" -R ""{4}""",
                //                    probak, inbak, pritner, pos, rate);
                // string arguments = String.Format(@"print -L {0} -S {1} -X ""{2}"" -I ""{3}"" -A ""{4}""",
                //                                     pos, size, profile, infile, outfile);
                Process process  = Process.Start(@"GTX700PBCMD.exe", arguments);
                process.WaitForExit();

                File.Delete(inbak);
                File.Delete(probak);
                File.Move(infile, backfile);
            }
        }
        private bool CheckFile(string file)
        {
            if (!File.Exists(file))
            {
                return true;
            }

            string path = Path.ChangeExtension(file, null);
            string ext  = Path.GetExtension(file);
            int    num  = 0;
            string to;
            do
            {
                to = path + string.Format(@"_{0}", num) + ext;
                ++num;
            }
            while(File.Exists(to));

            File.Move(file, to);
            return false;
        }
        private string ModifyProfile(string file, string table, int copies)
        {
            var option  = new GTOPTION(0);
            Utility.LoadXML(file, ref option);
            option.uiCopies = copies;

            string[] array = { "16x21", "16x18", "14x16", "10x12", "7x8", "24x24", "18×22" };
            int index = Array.IndexOf(array, table);
            //if (index >= 0)
            if (index >= 2 && index <= 3) // モニター時点での対応サイズは14x16, 10x12のみ
            {
                option.byPlatenSize = (byte)index;
            }

            string path = Path.GetTempFileName();
            Utility.SaveXML(path, option);
            return path;
        }
        private string ModifyInfile(string file, string name, string ext)
        {
            string path = Path.Combine(Path.GetTempPath(), name + ext);
            File.Copy(file, path);
            return path;
        }
    }
}
