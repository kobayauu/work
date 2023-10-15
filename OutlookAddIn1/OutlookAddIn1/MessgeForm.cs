using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace OutlookAddIn1
{
    public partial class MessgeForm : Form
    {
        const string WINDOW_TITLE = "Outlook";

        System.Timers.Timer timer = new System.Timers.Timer(200);
        public DialogResult ret;
        String strMessage = "";
        MessageBoxButtons btnMessage;
        MessageBoxIcon iconMessage;

        public MessgeForm(string message, MessageBoxButtons btn, MessageBoxIcon icon) {
            InitializeComponent();
            strMessage = message;
            btnMessage = btn;
            iconMessage = icon;
        }

        private void MessgeForm_Load(object sender, EventArgs e) {
            this.Left = 0;
            this.Top = 0;
         
            timer.Elapsed += new System.Timers.ElapsedEventHandler(OnElapsed);
            timer.Start();
        }

        // タイマーのイベント
        private void OnElapsed(object sender, System.Timers.ElapsedEventArgs e) {
            timer.Stop();
            ret = MessageBox.Show(this, strMessage, WINDOW_TITLE, btnMessage, iconMessage);
            this.Close();
        }
    }
}
