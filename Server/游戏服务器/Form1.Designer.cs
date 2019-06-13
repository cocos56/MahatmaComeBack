partial class Form1
{
    /// 必需的设计器变量。
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    /// 清理所有正在使用的资源。
    /// </summary>
    /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
    protected override void Dispose(bool disposing)
    {
        if (disposing && (components != null))
        {
            components.Dispose();
        }
        base.Dispose(disposing);
    }

    #region Windows 窗体设计器生成的代码

    /// <summary>
    /// 设计器支持所需的方法 - 不要修改
    /// 使用代码编辑器修改此方法的内容。
    /// </summary>
    private void InitializeComponent()
    {
            this.ipText = new System.Windows.Forms.TextBox();
            this.ipLabel = new System.Windows.Forms.Label();
            this.portLabel = new System.Windows.Forms.Label();
            this.portText = new System.Windows.Forms.TextBox();
            this.listenerButton = new System.Windows.Forms.Button();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.stopListenerButton = new System.Windows.Forms.Button();
            this.connectMysqlButton = new System.Windows.Forms.Button();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.logText = new System.Windows.Forms.TextBox();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.button1 = new System.Windows.Forms.Button();
            this.Notice = new System.Windows.Forms.TextBox();
            this.noticeText = new System.Windows.Forms.TextBox();
            this.tabControl1.SuspendLayout();
            this.tabPage3.SuspendLayout();
            this.tabPage1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.tabPage2.SuspendLayout();
            this.tabPage4.SuspendLayout();
            this.SuspendLayout();
            // 
            // ipText
            // 
            this.ipText.Font = new System.Drawing.Font("宋体", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.ipText.Location = new System.Drawing.Point(426, 53);
            this.ipText.Name = "ipText";
            this.ipText.Size = new System.Drawing.Size(144, 38);
            this.ipText.TabIndex = 0;
            this.ipText.Text = "10.6.32.1";
            this.ipText.TextChanged += new System.EventHandler(this.IpText_TextChanged);
            // 
            // ipLabel
            // 
            this.ipLabel.AutoSize = true;
            this.ipLabel.Font = new System.Drawing.Font("宋体", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.ipLabel.Location = new System.Drawing.Point(172, 64);
            this.ipLabel.Name = "ipLabel";
            this.ipLabel.Size = new System.Drawing.Size(202, 27);
            this.ipLabel.TabIndex = 1;
            this.ipLabel.Text = "服务器ip地址：";
            // 
            // portLabel
            // 
            this.portLabel.AutoSize = true;
            this.portLabel.Font = new System.Drawing.Font("宋体", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.portLabel.Location = new System.Drawing.Point(274, 153);
            this.portLabel.Name = "portLabel";
            this.portLabel.Size = new System.Drawing.Size(80, 27);
            this.portLabel.TabIndex = 2;
            this.portLabel.Text = "端口:";
            // 
            // portText
            // 
            this.portText.Font = new System.Drawing.Font("宋体", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.portText.Location = new System.Drawing.Point(426, 142);
            this.portText.Name = "portText";
            this.portText.Size = new System.Drawing.Size(144, 38);
            this.portText.TabIndex = 3;
            this.portText.Text = "80";
            this.portText.TextChanged += new System.EventHandler(this.PortText_TextChanged);
            // 
            // listenerButton
            // 
            this.listenerButton.Font = new System.Drawing.Font("宋体", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.listenerButton.Location = new System.Drawing.Point(153, 230);
            this.listenerButton.Name = "listenerButton";
            this.listenerButton.Size = new System.Drawing.Size(221, 63);
            this.listenerButton.TabIndex = 4;
            this.listenerButton.Text = "开始监听服务器";
            this.listenerButton.UseVisualStyleBackColor = true;
            this.listenerButton.Click += new System.EventHandler(this.listenerButton_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage4);
            this.tabControl1.Location = new System.Drawing.Point(12, 3);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(882, 572);
            this.tabControl1.TabIndex = 5;
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.stopListenerButton);
            this.tabPage3.Controls.Add(this.connectMysqlButton);
            this.tabPage3.Controls.Add(this.ipLabel);
            this.tabPage3.Controls.Add(this.listenerButton);
            this.tabPage3.Controls.Add(this.ipText);
            this.tabPage3.Controls.Add(this.portText);
            this.tabPage3.Controls.Add(this.portLabel);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Padding = new System.Windows.Forms.Padding(3, 3, 3, 3);
            this.tabPage3.Size = new System.Drawing.Size(874, 546);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "初始化服务器";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // stopListenerButton
            // 
            this.stopListenerButton.Enabled = false;
            this.stopListenerButton.Font = new System.Drawing.Font("宋体", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.stopListenerButton.Location = new System.Drawing.Point(464, 230);
            this.stopListenerButton.Name = "stopListenerButton";
            this.stopListenerButton.Size = new System.Drawing.Size(221, 63);
            this.stopListenerButton.TabIndex = 6;
            this.stopListenerButton.Text = "断开服务器链接";
            this.stopListenerButton.UseVisualStyleBackColor = true;
            this.stopListenerButton.Click += new System.EventHandler(this.stopListenerButton_Click);
            // 
            // connectMysqlButton
            // 
            this.connectMysqlButton.Font = new System.Drawing.Font("宋体", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.connectMysqlButton.Location = new System.Drawing.Point(312, 371);
            this.connectMysqlButton.Name = "connectMysqlButton";
            this.connectMysqlButton.Size = new System.Drawing.Size(221, 65);
            this.connectMysqlButton.TabIndex = 5;
            this.connectMysqlButton.Text = "链接数据库";
            this.connectMysqlButton.UseVisualStyleBackColor = true;
            this.connectMysqlButton.Click += new System.EventHandler(this.connectMysqlButton_Click);
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.dataGridView1);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3, 3, 3, 3);
            this.tabPage1.Size = new System.Drawing.Size(874, 546);
            this.tabPage1.TabIndex = 3;
            this.tabPage1.Text = "角色";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // dataGridView1
            // 
            this.dataGridView1.AllowUserToAddRows = false;
            this.dataGridView1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Location = new System.Drawing.Point(6, 0);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowHeadersWidth = 51;
            this.dataGridView1.RowTemplate.Height = 23;
            this.dataGridView1.Size = new System.Drawing.Size(868, 543);
            this.dataGridView1.TabIndex = 0;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.logText);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3, 3, 3, 3);
            this.tabPage2.Size = new System.Drawing.Size(874, 546);
            this.tabPage2.TabIndex = 4;
            this.tabPage2.Text = "日志";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // logText
            // 
            this.logText.Location = new System.Drawing.Point(7, 6);
            this.logText.Multiline = true;
            this.logText.Name = "logText";
            this.logText.Size = new System.Drawing.Size(864, 534);
            this.logText.TabIndex = 1;
            // 
            // tabPage4
            // 
            this.tabPage4.Controls.Add(this.button1);
            this.tabPage4.Controls.Add(this.Notice);
            this.tabPage4.Controls.Add(this.noticeText);
            this.tabPage4.Location = new System.Drawing.Point(4, 22);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Padding = new System.Windows.Forms.Padding(3, 3, 3, 3);
            this.tabPage4.Size = new System.Drawing.Size(874, 546);
            this.tabPage4.TabIndex = 5;
            this.tabPage4.Text = "公告";
            this.tabPage4.UseVisualStyleBackColor = true;
            // 
            // button1
            // 
            this.button1.Font = new System.Drawing.Font("宋体", 21.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button1.Location = new System.Drawing.Point(714, 490);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(154, 50);
            this.button1.TabIndex = 2;
            this.button1.Text = "发送公告";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // Notice
            // 
            this.Notice.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.Notice.Location = new System.Drawing.Point(3, 490);
            this.Notice.Multiline = true;
            this.Notice.Name = "Notice";
            this.Notice.Size = new System.Drawing.Size(705, 50);
            this.Notice.TabIndex = 1;
            // 
            // noticeText
            // 
            this.noticeText.Location = new System.Drawing.Point(0, 3);
            this.noticeText.Multiline = true;
            this.noticeText.Name = "noticeText";
            this.noticeText.Size = new System.Drawing.Size(871, 481);
            this.noticeText.TabIndex = 0;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(896, 587);
            this.Controls.Add(this.tabControl1);
            this.Name = "Form1";
            this.Text = "游戏服务器(作者：张红银，徐可可)";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.tabControl1.ResumeLayout(false);
            this.tabPage3.ResumeLayout(false);
            this.tabPage3.PerformLayout();
            this.tabPage1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.tabPage4.ResumeLayout(false);
            this.tabPage4.PerformLayout();
            this.ResumeLayout(false);

    }

    #endregion

    private System.Windows.Forms.TextBox ipText;
    private System.Windows.Forms.Label ipLabel;
    private System.Windows.Forms.Label portLabel;
    private System.Windows.Forms.TextBox portText;
    private System.Windows.Forms.Button listenerButton;
    private System.Windows.Forms.TabControl tabControl1;
    private System.Windows.Forms.TabPage tabPage3;
    private System.Windows.Forms.TabPage tabPage1;
    private System.Windows.Forms.DataGridView dataGridView1;
    private System.Windows.Forms.TabPage tabPage2;
    private System.Windows.Forms.TextBox logText;
    private System.Windows.Forms.Button connectMysqlButton;
    private System.Windows.Forms.Button stopListenerButton;
    private System.Windows.Forms.TabPage tabPage4;
    private System.Windows.Forms.Button button1;
    private System.Windows.Forms.TextBox Notice;
    private System.Windows.Forms.TextBox noticeText;
}