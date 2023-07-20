namespace CtrlPC
{
    partial class Form1
    {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

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

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.Startbutton = new System.Windows.Forms.Button();
            this.Closebutton = new System.Windows.Forms.Button();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.CtrlFiletextBox = new System.Windows.Forms.TextBox();
            this.FuncFiletextBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.RefCtrlFilebutton = new System.Windows.Forms.Button();
            this.RefFuncFilebutton = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.OutputtextBox = new System.Windows.Forms.TextBox();
            this.RecordStartbutton = new System.Windows.Forms.Button();
            this.RecordCancelbutton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // Startbutton
            // 
            this.Startbutton.Location = new System.Drawing.Point(382, 77);
            this.Startbutton.Margin = new System.Windows.Forms.Padding(2);
            this.Startbutton.Name = "Startbutton";
            this.Startbutton.Size = new System.Drawing.Size(75, 23);
            this.Startbutton.TabIndex = 0;
            this.Startbutton.Text = "操作開始";
            this.Startbutton.UseVisualStyleBackColor = true;
            this.Startbutton.Click += new System.EventHandler(this.Startbutton_Click);
            // 
            // Closebutton
            // 
            this.Closebutton.Location = new System.Drawing.Point(382, 197);
            this.Closebutton.Margin = new System.Windows.Forms.Padding(2);
            this.Closebutton.Name = "Closebutton";
            this.Closebutton.Size = new System.Drawing.Size(75, 23);
            this.Closebutton.TabIndex = 1;
            this.Closebutton.Text = "閉じる";
            this.Closebutton.UseVisualStyleBackColor = true;
            this.Closebutton.Click += new System.EventHandler(this.Closebutton_Click);
            // 
            // CtrlFiletextBox
            // 
            this.CtrlFiletextBox.Location = new System.Drawing.Point(78, 15);
            this.CtrlFiletextBox.Margin = new System.Windows.Forms.Padding(2);
            this.CtrlFiletextBox.Name = "CtrlFiletextBox";
            this.CtrlFiletextBox.Size = new System.Drawing.Size(300, 19);
            this.CtrlFiletextBox.TabIndex = 2;
            // 
            // FuncFiletextBox
            // 
            this.FuncFiletextBox.Location = new System.Drawing.Point(78, 46);
            this.FuncFiletextBox.Margin = new System.Windows.Forms.Padding(2);
            this.FuncFiletextBox.Name = "FuncFiletextBox";
            this.FuncFiletextBox.Size = new System.Drawing.Size(300, 19);
            this.FuncFiletextBox.TabIndex = 3;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(11, 18);
            this.label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(63, 12);
            this.label1.TabIndex = 4;
            this.label1.Text = "操作ファイル";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(11, 51);
            this.label2.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(63, 12);
            this.label2.TabIndex = 5;
            this.label2.Text = "関数ファイル";
            // 
            // RefCtrlFilebutton
            // 
            this.RefCtrlFilebutton.Location = new System.Drawing.Point(382, 13);
            this.RefCtrlFilebutton.Margin = new System.Windows.Forms.Padding(2);
            this.RefCtrlFilebutton.Name = "RefCtrlFilebutton";
            this.RefCtrlFilebutton.Size = new System.Drawing.Size(75, 23);
            this.RefCtrlFilebutton.TabIndex = 6;
            this.RefCtrlFilebutton.Text = "参照";
            this.RefCtrlFilebutton.UseVisualStyleBackColor = true;
            this.RefCtrlFilebutton.Click += new System.EventHandler(this.RefCtrlFilebutton_Click);
            // 
            // RefFuncFilebutton
            // 
            this.RefFuncFilebutton.Location = new System.Drawing.Point(382, 44);
            this.RefFuncFilebutton.Margin = new System.Windows.Forms.Padding(2);
            this.RefFuncFilebutton.Name = "RefFuncFilebutton";
            this.RefFuncFilebutton.Size = new System.Drawing.Size(75, 23);
            this.RefFuncFilebutton.TabIndex = 7;
            this.RefFuncFilebutton.Text = "参照";
            this.RefFuncFilebutton.UseVisualStyleBackColor = true;
            this.RefFuncFilebutton.Click += new System.EventHandler(this.RefFuncFilebutton_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(11, 117);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 12);
            this.label3.TabIndex = 9;
            this.label3.Text = "出力結果";
            // 
            // OutputtextBox
            // 
            this.OutputtextBox.HideSelection = false;
            this.OutputtextBox.Location = new System.Drawing.Point(78, 114);
            this.OutputtextBox.Margin = new System.Windows.Forms.Padding(2);
            this.OutputtextBox.Multiline = true;
            this.OutputtextBox.Name = "OutputtextBox";
            this.OutputtextBox.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.OutputtextBox.Size = new System.Drawing.Size(300, 70);
            this.OutputtextBox.TabIndex = 13;
            // 
            // RecordStartbutton
            // 
            this.RecordStartbutton.Location = new System.Drawing.Point(382, 112);
            this.RecordStartbutton.Margin = new System.Windows.Forms.Padding(2);
            this.RecordStartbutton.Name = "RecordStartbutton";
            this.RecordStartbutton.Size = new System.Drawing.Size(75, 23);
            this.RecordStartbutton.TabIndex = 14;
            this.RecordStartbutton.Text = "記録開始";
            this.RecordStartbutton.UseVisualStyleBackColor = true;
            this.RecordStartbutton.Click += new System.EventHandler(this.RecordStartbutton_Click);
            // 
            // RecordCancelbutton
            // 
            this.RecordCancelbutton.Enabled = false;
            this.RecordCancelbutton.Location = new System.Drawing.Point(382, 139);
            this.RecordCancelbutton.Margin = new System.Windows.Forms.Padding(2);
            this.RecordCancelbutton.Name = "RecordCancelbutton";
            this.RecordCancelbutton.Size = new System.Drawing.Size(75, 23);
            this.RecordCancelbutton.TabIndex = 15;
            this.RecordCancelbutton.Text = "記録中断";
            this.RecordCancelbutton.UseVisualStyleBackColor = true;
            this.RecordCancelbutton.Click += new System.EventHandler(this.RecordCancelbutton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(480, 231);
            this.Controls.Add(this.RecordCancelbutton);
            this.Controls.Add(this.RecordStartbutton);
            this.Controls.Add(this.OutputtextBox);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.RefFuncFilebutton);
            this.Controls.Add(this.RefCtrlFilebutton);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.FuncFiletextBox);
            this.Controls.Add(this.CtrlFiletextBox);
            this.Controls.Add(this.Closebutton);
            this.Controls.Add(this.Startbutton);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Margin = new System.Windows.Forms.Padding(2);
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "CtrlPC";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button Startbutton;
        private System.Windows.Forms.Button Closebutton;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.TextBox CtrlFiletextBox;
        private System.Windows.Forms.TextBox FuncFiletextBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button RefCtrlFilebutton;
        private System.Windows.Forms.Button RefFuncFilebutton;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox OutputtextBox;
        private System.Windows.Forms.Button RecordStartbutton;
        private System.Windows.Forms.Button RecordCancelbutton;
    }
}

