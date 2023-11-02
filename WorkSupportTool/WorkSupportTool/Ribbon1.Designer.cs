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
            this.tab1 = this.Factory.CreateRibbonTab();
            this.group3 = this.Factory.CreateRibbonGroup();
            this.subjectComboBox = this.Factory.CreateRibbonComboBox();
            this.categoryList = this.Factory.CreateRibbonDropDown();
            this.scheduleButton = this.Factory.CreateRibbonButton();
            this.homeWorkButton = this.Factory.CreateRibbonButton();
            this.group1 = this.Factory.CreateRibbonGroup();
            this.pomodoroTimerButton = this.Factory.CreateRibbonButton();
            this.workMinutesList = this.Factory.CreateRibbonDropDown();
            this.restMinutesList = this.Factory.CreateRibbonDropDown();
            this.recordButton = this.Factory.CreateRibbonButton();
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
            this.group3.Items.Add(this.recordButton);
            this.group3.Items.Add(this.subjectComboBox);
            this.group3.Items.Add(this.categoryList);
            this.group3.Items.Add(this.scheduleButton);
            this.group3.Items.Add(this.homeWorkButton);
            this.group3.Label = "勤務管理";
            this.group3.Name = "group3";
            // 
            // subjectComboBox
            // 
            this.subjectComboBox.Label = "件名";
            this.subjectComboBox.Name = "subjectComboBox";
            this.subjectComboBox.Text = null;
            this.subjectComboBox.TextChanged += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.subjectComboBox_TextChanged);
            // 
            // categoryList
            // 
            this.categoryList.Label = "分類";
            this.categoryList.Name = "categoryList";
            // 
            // scheduleButton
            // 
            this.scheduleButton.Image = global::OutlookAddIn1.Properties.Resources.schedule;
            this.scheduleButton.Label = "予定表";
            this.scheduleButton.Name = "scheduleButton";
            this.scheduleButton.ShowImage = true;
            this.scheduleButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.scheduleButton_Click);
            // 
            // homeWorkButton
            // 
            this.homeWorkButton.Image = global::OutlookAddIn1.Properties.Resources.home;
            this.homeWorkButton.Label = "在宅切替";
            this.homeWorkButton.Name = "homeWorkButton";
            this.homeWorkButton.ShowImage = true;
            this.homeWorkButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.homeWorkButton_Click);
            // 
            // group1
            // 
            this.group1.Items.Add(this.pomodoroTimerButton);
            this.group1.Items.Add(this.workMinutesList);
            this.group1.Items.Add(this.restMinutesList);
            this.group1.Label = "ポモードロタイマー";
            this.group1.Name = "group1";
            // 
            // pomodoroTimerButton
            // 
            this.pomodoroTimerButton.Image = global::OutlookAddIn1.Properties.Resources.startTimer;
            this.pomodoroTimerButton.Label = "タイマー開始";
            this.pomodoroTimerButton.Name = "pomodoroTimerButton";
            this.pomodoroTimerButton.ShowImage = true;
            this.pomodoroTimerButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.pomodoroTimerButton_Click);
            // 
            // workMinutesList
            // 
            this.workMinutesList.Label = "作業[分]";
            this.workMinutesList.Name = "workMinutesList";
            // 
            // restMinutesList
            // 
            this.restMinutesList.Label = "休憩[分]";
            this.restMinutesList.Name = "restMinutesList";
            // 
            // recordButton
            // 
            this.recordButton.Image = global::OutlookAddIn1.Properties.Resources.startRecord;
            this.recordButton.Label = "記録開始";
            this.recordButton.Name = "recordButton";
            this.recordButton.ShowImage = true;
            this.recordButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.recordButton_Click);
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
        internal Microsoft.Office.Tools.Ribbon.RibbonDropDown workMinutesList;
        internal Microsoft.Office.Tools.Ribbon.RibbonDropDown restMinutesList;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton homeWorkButton;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton pomodoroTimerButton;
        internal Microsoft.Office.Tools.Ribbon.RibbonGroup group3;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton recordButton;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton scheduleButton;
        internal Microsoft.Office.Tools.Ribbon.RibbonComboBox subjectComboBox;
        internal Microsoft.Office.Tools.Ribbon.RibbonDropDown categoryList;
    }

    partial class ThisRibbonCollection
    {
        internal Ribbon1 Ribbon1
        {
            get { return this.GetRibbon<Ribbon1>(); }
        }
    }
}
