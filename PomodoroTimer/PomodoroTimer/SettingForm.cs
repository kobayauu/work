using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PomodoroTimer
{
    public partial class SettingForm : Form
    {
        public int SettingWorkTime { get; set; } = 1;
        public int SettingRestTime { get; set; } = 1;
        public int SettingFormBorderStyle { get; set; } = 0;


        public SettingForm()
        {
            InitializeComponent();
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            // コンボボックスに値を追加
            for (int i = 1; i <= 60; i++) {
                WorkTimeComboBox.Items.Add(i);
                RestTimeComboBox.Items.Add(i);
            }

            // 初期値を設定
            WorkTimeComboBox.SelectedIndex = WorkTimeComboBox.Items.IndexOf(SettingWorkTime);
            RestTimeComboBox.SelectedIndex = WorkTimeComboBox.Items.IndexOf(SettingRestTime);
            if (SettingFormBorderStyle == 0) {
                NoneRadioButton.Checked = true;
            }
            else {
                FixedSingleRadioButton.Checked = false;
            }
            
        }

        private void OKButton_Click(object sender, EventArgs e)
        {
            SettingWorkTime = (int)WorkTimeComboBox.SelectedItem;
            SettingRestTime = (int)RestTimeComboBox.SelectedItem;
            if (NoneRadioButton.Checked == true) {
                SettingFormBorderStyle = 0;
            }
            else {
                SettingFormBorderStyle = 1;
            }
            
            this.Close();
        }

        private void CancelButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
