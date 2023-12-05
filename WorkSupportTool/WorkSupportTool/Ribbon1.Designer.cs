namespace WorkSupportTool
{
    partial class Ribbon1 : Microsoft.Office.Tools.Ribbon.RibbonBase
    {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        public Ribbon1()
            : base(Globals.Factory.GetRibbonFactory())
        {
            InitializeComponent();
        }

        /// <summary> 
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージド リソースを破棄する場合は true を指定し、その他の場合は false を指定します。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region コンポーネント デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl1 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl2 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl3 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl4 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl5 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl6 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl7 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl8 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl9 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl10 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl11 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl12 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl13 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl14 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl15 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl16 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl17 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl18 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl19 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl20 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl21 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl22 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl23 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl24 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl25 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl26 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl27 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl28 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl29 = this.Factory.CreateRibbonDropDownItem();
            Microsoft.Office.Tools.Ribbon.RibbonDropDownItem ribbonDropDownItemImpl30 = this.Factory.CreateRibbonDropDownItem();
            this.tab1 = this.Factory.CreateRibbonTab();
            this.group3 = this.Factory.CreateRibbonGroup();
            this.ScheduleButton = this.Factory.CreateRibbonButton();
            this.RecordButton = this.Factory.CreateRibbonButton();
            this.SubjectComboBox = this.Factory.CreateRibbonComboBox();
            this.WorkButton = this.Factory.CreateRibbonButton();
            this.HomeWorkButton = this.Factory.CreateRibbonButton();
            this.group1 = this.Factory.CreateRibbonGroup();
            this.PomodoroButton = this.Factory.CreateRibbonButton();
            this.WorkMinutesDropDown = this.Factory.CreateRibbonDropDown();
            this.RestMinutesDropDown = this.Factory.CreateRibbonDropDown();
            this.tab1.SuspendLayout();
            this.group3.SuspendLayout();
            this.group1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tab1
            // 
            this.tab1.ControlId.ControlIdType = Microsoft.Office.Tools.Ribbon.RibbonControlIdType.Office;
            this.tab1.Groups.Add(this.group3);
            this.tab1.Groups.Add(this.group1);
            this.tab1.Label = "TabAddIns";
            this.tab1.Name = "tab1";
            // 
            // group3
            // 
            this.group3.Items.Add(this.ScheduleButton);
            this.group3.Items.Add(this.RecordButton);
            this.group3.Items.Add(this.SubjectComboBox);
            this.group3.Items.Add(this.WorkButton);
            this.group3.Items.Add(this.HomeWorkButton);
            this.group3.Label = "勤務管理";
            this.group3.Name = "group3";
            // 
            // ScheduleButton
            // 
            this.ScheduleButton.Image = global::OutlookAddIn1.Properties.Resources.schedule;
            this.ScheduleButton.Label = "予定表";
            this.ScheduleButton.Name = "ScheduleButton";
            this.ScheduleButton.ShowImage = true;
            this.ScheduleButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.ScheduleButton_Click);
            // 
            // RecordButton
            // 
            this.RecordButton.Image = global::OutlookAddIn1.Properties.Resources.startRecord;
            this.RecordButton.Label = "記録開始";
            this.RecordButton.Name = "RecordButton";
            this.RecordButton.ShowImage = true;
            this.RecordButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.RecordButton_Click);
            // 
            // SubjectComboBox
            // 
            this.SubjectComboBox.Label = "件名";
            this.SubjectComboBox.Name = "SubjectComboBox";
            this.SubjectComboBox.Text = null;
            // 
            // WorkButton
            // 
            this.WorkButton.Image = global::OutlookAddIn1.Properties.Resources.company;
            this.WorkButton.Label = "出勤切替";
            this.WorkButton.Name = "WorkButton";
            this.WorkButton.ShowImage = true;
            this.WorkButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.WorkButton_Click);
            // 
            // HomeWorkButton
            // 
            this.HomeWorkButton.Image = global::OutlookAddIn1.Properties.Resources.home;
            this.HomeWorkButton.Label = "在宅切替";
            this.HomeWorkButton.Name = "HomeWorkButton";
            this.HomeWorkButton.ShowImage = true;
            this.HomeWorkButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.HomeWorkButton_Click);
            // 
            // group1
            // 
            this.group1.Items.Add(this.PomodoroButton);
            this.group1.Items.Add(this.WorkMinutesDropDown);
            this.group1.Items.Add(this.RestMinutesDropDown);
            this.group1.Label = "ポモードロタイマー";
            this.group1.Name = "group1";
            // 
            // PomodoroButton
            // 
            this.PomodoroButton.Image = global::OutlookAddIn1.Properties.Resources.startTimer;
            this.PomodoroButton.Label = "タイマー開始";
            this.PomodoroButton.Name = "PomodoroButton";
            this.PomodoroButton.ShowImage = true;
            this.PomodoroButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.pomodoroTimerButton_Click);
            // 
            // WorkMinutesDropDown
            // 
            ribbonDropDownItemImpl1.Label = "1";
            ribbonDropDownItemImpl2.Label = "2";
            ribbonDropDownItemImpl3.Label = "3";
            ribbonDropDownItemImpl4.Label = "4";
            ribbonDropDownItemImpl5.Label = "5";
            ribbonDropDownItemImpl6.Label = "6";
            ribbonDropDownItemImpl7.Label = "7";
            ribbonDropDownItemImpl8.Label = "8";
            ribbonDropDownItemImpl9.Label = "9";
            ribbonDropDownItemImpl10.Label = "10";
            ribbonDropDownItemImpl11.Label = "11";
            ribbonDropDownItemImpl12.Label = "12";
            ribbonDropDownItemImpl13.Label = "13";
            ribbonDropDownItemImpl14.Label = "14";
            ribbonDropDownItemImpl15.Label = "15";
            ribbonDropDownItemImpl16.Label = "16";
            ribbonDropDownItemImpl17.Label = "17";
            ribbonDropDownItemImpl18.Label = "18";
            ribbonDropDownItemImpl19.Label = "19";
            ribbonDropDownItemImpl20.Label = "20";
            ribbonDropDownItemImpl21.Label = "21";
            ribbonDropDownItemImpl22.Label = "22";
            ribbonDropDownItemImpl23.Label = "23";
            ribbonDropDownItemImpl24.Label = "24";
            ribbonDropDownItemImpl25.Label = "25";
            this.WorkMinutesDropDown.Items.Add(ribbonDropDownItemImpl1);
            this.WorkMinutesDropDown.Items.Add(ribbonDropDownItemImpl2);
            this.WorkMinutesDropDown.Items.Add(ribbonDropDownItemImpl3);
            this.WorkMinutesDropDown.Items.Add(ribbonDropDownItemImpl4);
            this.WorkMinutesDropDown.Items.Add(ribbonDropDownItemImpl5);
            this.WorkMinutesDropDown.Items.Add(ribbonDropDownItemImpl6);
            this.WorkMinutesDropDown.Items.Add(ribbonDropDownItemImpl7);
            this.WorkMinutesDropDown.Items.Add(ribbonDropDownItemImpl8);
            this.WorkMinutesDropDown.Items.Add(ribbonDropDownItemImpl9);
            this.WorkMinutesDropDown.Items.Add(ribbonDropDownItemImpl10);
            this.WorkMinutesDropDown.Items.Add(ribbonDropDownItemImpl11);
            this.WorkMinutesDropDown.Items.Add(ribbonDropDownItemImpl12);
            this.WorkMinutesDropDown.Items.Add(ribbonDropDownItemImpl13);
            this.WorkMinutesDropDown.Items.Add(ribbonDropDownItemImpl14);
            this.WorkMinutesDropDown.Items.Add(ribbonDropDownItemImpl15);
            this.WorkMinutesDropDown.Items.Add(ribbonDropDownItemImpl16);
            this.WorkMinutesDropDown.Items.Add(ribbonDropDownItemImpl17);
            this.WorkMinutesDropDown.Items.Add(ribbonDropDownItemImpl18);
            this.WorkMinutesDropDown.Items.Add(ribbonDropDownItemImpl19);
            this.WorkMinutesDropDown.Items.Add(ribbonDropDownItemImpl20);
            this.WorkMinutesDropDown.Items.Add(ribbonDropDownItemImpl21);
            this.WorkMinutesDropDown.Items.Add(ribbonDropDownItemImpl22);
            this.WorkMinutesDropDown.Items.Add(ribbonDropDownItemImpl23);
            this.WorkMinutesDropDown.Items.Add(ribbonDropDownItemImpl24);
            this.WorkMinutesDropDown.Items.Add(ribbonDropDownItemImpl25);
            this.WorkMinutesDropDown.Label = "作業[分]";
            this.WorkMinutesDropDown.Name = "WorkMinutesDropDown";
            // 
            // RestMinutesDropDown
            // 
            ribbonDropDownItemImpl26.Label = "1";
            ribbonDropDownItemImpl27.Label = "2";
            ribbonDropDownItemImpl28.Label = "3";
            ribbonDropDownItemImpl29.Label = "4";
            ribbonDropDownItemImpl30.Label = "5";
            this.RestMinutesDropDown.Items.Add(ribbonDropDownItemImpl26);
            this.RestMinutesDropDown.Items.Add(ribbonDropDownItemImpl27);
            this.RestMinutesDropDown.Items.Add(ribbonDropDownItemImpl28);
            this.RestMinutesDropDown.Items.Add(ribbonDropDownItemImpl29);
            this.RestMinutesDropDown.Items.Add(ribbonDropDownItemImpl30);
            this.RestMinutesDropDown.Label = "休憩[分]";
            this.RestMinutesDropDown.Name = "RestMinutesDropDown";
            // 
            // Ribbon1
            // 
            this.Name = "Ribbon1";
            this.RibbonType = "Microsoft.Outlook.Explorer, Microsoft.Outlook.Journal";
            this.Tabs.Add(this.tab1);
            this.Load += new Microsoft.Office.Tools.Ribbon.RibbonUIEventHandler(this.Ribbon1_Load);
            this.tab1.ResumeLayout(false);
            this.tab1.PerformLayout();
            this.group3.ResumeLayout(false);
            this.group3.PerformLayout();
            this.group1.ResumeLayout(false);
            this.group1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        internal Microsoft.Office.Tools.Ribbon.RibbonTab tab1;
        internal Microsoft.Office.Tools.Ribbon.RibbonGroup group1;
        internal Microsoft.Office.Tools.Ribbon.RibbonDropDown WorkMinutesDropDown;
        internal Microsoft.Office.Tools.Ribbon.RibbonDropDown RestMinutesDropDown;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton HomeWorkButton;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton PomodoroButton;
        internal Microsoft.Office.Tools.Ribbon.RibbonGroup group3;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton RecordButton;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton ScheduleButton;
        internal Microsoft.Office.Tools.Ribbon.RibbonComboBox SubjectComboBox;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton WorkButton;
    }

    partial class ThisRibbonCollection
    {
        internal Ribbon1 Ribbon1
        {
            get { return this.GetRibbon<Ribbon1>(); }
        }
    }
}
