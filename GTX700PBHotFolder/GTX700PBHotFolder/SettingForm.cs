//Confidential
//Copyright (C) 2023 Brother Industries, Ltd. All Rights Reserved.
using System;
using System.IO;
using System.Text;
using System.Windows.Forms;
using System.Xml.Serialization;

namespace GTX700PBHotFolder
{
    [Serializable]
    public struct Setup
    {
        public string Profile;
        public string Printer;
        public int Rate;

        public Setup(int dummy)
        {
            this.Profile = "default.xml";
            this.Printer = "Brother GTX700PB";
            this.Rate    = 1000;
        }
    }

    [Serializable]
    public struct Settings
    {
        public string Input;
        public string Output;
        public string Backup;
        public string Profile;
        public string Setup;

        public Settings(int dummy)
        {
            this.Input   = @"Input";
            this.Output  = @"Output";
            this.Backup  = @"Backup";
            this.Profile = @"Profile";
            this.Setup   = @"Setup";
        }

        // public bool LoadXML()
        // {
        //     try
        //     {
        //         string file = Path.ChangeExtension(Application.ExecutablePath, @".xml");
        //         var serializer = new XmlSerializer(typeof(Settings));
        //         var sr = new StreamReader(file, new UTF8Encoding(false));
        //         this = (Settings)serializer.Deserialize(sr);
        //         sr.Close();
        //         return true;
        //     }
        //     catch
        //     {
        //         return false;
        //     }
        // }
        // public bool SaveXML()
        // {
        //     try
        //     {
        //         string file = Path.ChangeExtension(Application.ExecutablePath, @".xml");
        //         var serializer = new XmlSerializer(typeof(Settings));
        //         var sw = new StreamWriter(file, false, new UTF8Encoding(false));
        //         serializer.Serialize(sw, this);
        //         sw.Close();
        //         return true;
        //     }
        //     catch
        //     {
        //         return false;
        //     }
        // }

        public bool Config()
        {
            var frm    = new SettingForm();
            var result = frm.ShowDialog(ref this);
            return (result == DialogResult.OK);
        }
    }

    public partial class SettingForm : Form
    {
        public DialogResult ShowDialog(ref Settings setting)
        {
            textBox1.Text = setting.Input;
            textBox2.Text = setting.Output;
            textBox3.Text = setting.Backup;
            textBox4.Text = setting.Profile;
            textBox5.Text = setting.Setup;

            DialogResult result = this.ShowDialog();
            if (result == DialogResult.OK)
            {
                setting.Input   = textBox1.Text;
                setting.Output  = textBox2.Text;
                setting.Backup  = textBox3.Text;
                setting.Profile = textBox4.Text;
                setting.Setup   = textBox5.Text;
            }

            return result;
        }

        public SettingForm()
        {
            InitializeComponent();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Close();
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            if (CheckFolder(textBox1.Text)
             && CheckFolder(textBox2.Text)
             && CheckFolder(textBox3.Text)
             && CheckFolder(textBox4.Text)
             && CheckFolder(textBox5.Text))
            {
                DialogResult = DialogResult.OK;
                Close();
            }
            else
            {
                MessageBox.Show("Not found Folder.");
            }
        }
        private bool CheckFolder(string path)
        {
            if (Directory.Exists(path))
            {
                return true;
            }
            else if (File.Exists(path))
            {
                return false;
            }

            try
            {
                Directory.CreateDirectory(path);
                return true;
            }
            catch
            {
                return false;
            }
        }

        private void btnBrowse_Click(object sender, EventArgs e)
        {
            var tag = Convert.ToInt32((sender as Button).Tag);
            var dlg = new FolderBrowserDialog();

            switch(tag)
            {
                case 1: dlg.SelectedPath = textBox1.Text; break;
                case 2: dlg.SelectedPath = textBox2.Text; break;
                case 3: dlg.SelectedPath = textBox3.Text; break;
                case 4: dlg.SelectedPath = textBox4.Text; break;
                case 5: dlg.SelectedPath = textBox5.Text; break;
            }
            dlg.SelectedPath = Path.GetFullPath(dlg.SelectedPath);

            if (dlg.ShowDialog() != System.Windows.Forms.DialogResult.OK)
            {
                return;
            }

            switch (tag)
            {
                case 1: textBox1.Text = dlg.SelectedPath; break;
                case 2: textBox2.Text = dlg.SelectedPath; break;
                case 3: textBox3.Text = dlg.SelectedPath; break;
                case 4: textBox4.Text = dlg.SelectedPath; break;
                case 5: textBox5.Text = dlg.SelectedPath; break;
            }
        }
    }
}
