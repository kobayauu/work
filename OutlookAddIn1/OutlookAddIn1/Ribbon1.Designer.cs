namespace OutlookAddIn1
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
            this.group1 = this.Factory.CreateRibbonGroup();
            this.StartBtn = this.Factory.CreateRibbonButton();
            this.timeStatusBtn = this.Factory.CreateRibbonButton();
            this.group2 = this.Factory.CreateRibbonGroup();
            this.workMinutesList = this.Factory.CreateRibbonDropDown();
            this.restMinutesList = this.Factory.CreateRibbonDropDown();
            this.tab1.SuspendLayout();
            this.group1.SuspendLayout();
            this.group2.SuspendLayout();
            this.SuspendLayout();
            // 
            // tab1
            // 
            this.tab1.ControlId.ControlIdType = Microsoft.Office.Tools.Ribbon.RibbonControlIdType.Office;
            this.tab1.Groups.Add(this.group1);
            this.tab1.Groups.Add(this.group2);
            this.tab1.Label = "TabAddIns";
            this.tab1.Name = "tab1";
            // 
            // group1
            // 
            this.group1.Items.Add(this.StartBtn);
            this.group1.Items.Add(this.timeStatusBtn);
            this.group1.Label = "タイマー開始・停止";
            this.group1.Name = "group1";
            // 
            // StartBtn
            // 
            this.StartBtn.Image = global::OutlookAddIn1.Properties.Resources.player_button01_saisei;
            this.StartBtn.Label = "開始";
            this.StartBtn.Name = "StartBtn";
            this.StartBtn.ShowImage = true;
            this.StartBtn.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.StartButton_Click);
            // 
            // timeStatusBtn
            // 
            this.timeStatusBtn.Label = "停止 25:00";
            this.timeStatusBtn.Name = "timeStatusBtn";
            this.timeStatusBtn.ShowImage = true;
            this.timeStatusBtn.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.timeStatusBtn_Click);
            // 
            // group2
            // 
            this.group2.Items.Add(this.workMinutesList);
            this.group2.Items.Add(this.restMinutesList);
            this.group2.Label = "設定";
            this.group2.Name = "group2";
            // 
            // workMinutesList
            // 
            this.workMinutesList.Label = "作業時間[分]";
            this.workMinutesList.Name = "workMinutesList";
            this.workMinutesList.SelectionChanged += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.workMinutesList_SelectionChanged);
            // 
            // restMinutesList
            // 
            this.restMinutesList.Label = "休憩時間[分]";
            this.restMinutesList.Name = "restMinutesList";
            // 
            // Ribbon1
            // 
            this.Name = "Ribbon1";
            this.RibbonType = "Microsoft.Outlook.Explorer, Microsoft.Outlook.Journal";
            this.Tabs.Add(this.tab1);
            this.Load += new Microsoft.Office.Tools.Ribbon.RibbonUIEventHandler(this.Ribbon1_Load);
            this.tab1.ResumeLayout(false);
            this.tab1.PerformLayout();
            this.group1.ResumeLayout(false);
            this.group1.PerformLayout();
            this.group2.ResumeLayout(false);
            this.group2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        internal Microsoft.Office.Tools.Ribbon.RibbonTab tab1;
        internal Microsoft.Office.Tools.Ribbon.RibbonGroup group1;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton StartBtn;
        internal Microsoft.Office.Tools.Ribbon.RibbonGroup group2;
        internal Microsoft.Office.Tools.Ribbon.RibbonDropDown workMinutesList;
        internal Microsoft.Office.Tools.Ribbon.RibbonDropDown restMinutesList;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton timeStatusBtn;
    }

    partial class ThisRibbonCollection
    {
        internal Ribbon1 Ribbon1
        {
            get { return this.GetRibbon<Ribbon1>(); }
        }
    }
}
