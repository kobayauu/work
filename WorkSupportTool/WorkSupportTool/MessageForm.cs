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
    public partial class MessageForm : Form
    {
        public string msg = "";
        public int status = 0;

        public MessageForm() {
            InitializeComponent();
        }

        private void MessageForm_Load(object sender, EventArgs e)
        {
            label1.Text = msg;
        }

        private void OkButton_Click(object sender, EventArgs e)
        {
            status = 0;
            this.Close();
        }

        private void CancelButton_Click(object sender, EventArgs e)
        {
            status = -1;
            this.Close();
        }
    }
}
