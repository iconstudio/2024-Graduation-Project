namespace Test_Chat_Client
{
	partial class Form1
	{
		/// <summary>
		///  Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		///  Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		///  Required method for Designer support - do not modify
		///  the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			chatPage = new TableLayoutPanel();
			chatContents = new Panel();
			chatInputBox = new TextBox();
			mainMenuStrip = new MenuStrip();
			파일ToolStripMenuItem = new ToolStripMenuItem();
			signInMenuItem = new ToolStripMenuItem();
			signOutMenuItem = new ToolStripMenuItem();
			settingMenuItem = new ToolStripMenuItem();
			toolStripSeparator1 = new ToolStripSeparator();
			quitMenuItem = new ToolStripMenuItem();
			도움말ToolStripMenuItem = new ToolStripMenuItem();
			정보ToolStripMenuItem = new ToolStripMenuItem();
			backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
			signInPage = new Panel();
			signInButton = new Button();
			toolStripStatusLabel1 = new ToolStripStatusLabel();
			toolStripStatusLabel2 = new ToolStripStatusLabel();
			toolStripStatusLabel3 = new ToolStripStatusLabel();
			statusStrip1 = new StatusStrip();
			inputLayer = new TableLayoutPanel();
			chatSendButton = new Button();
			memberListBox = new ListBox();
			chatPage.SuspendLayout();
			mainMenuStrip.SuspendLayout();
			signInPage.SuspendLayout();
			statusStrip1.SuspendLayout();
			inputLayer.SuspendLayout();
			SuspendLayout();
			// 
			// chatPage
			// 
			chatPage.AutoSize = true;
			chatPage.AutoSizeMode = AutoSizeMode.GrowAndShrink;
			chatPage.BackColor = SystemColors.Control;
			chatPage.ColumnCount = 3;
			chatPage.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 9.333333F));
			chatPage.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 90.6666641F));
			chatPage.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 201F));
			chatPage.Controls.Add(chatContents, 1, 1);
			chatPage.Controls.Add(inputLayer, 1, 2);
			chatPage.Controls.Add(memberListBox, 2, 1);
			chatPage.Dock = DockStyle.Fill;
			chatPage.Location = new Point(0, 24);
			chatPage.Margin = new Padding(3, 3, 3, 18);
			chatPage.Name = "chatPage";
			chatPage.Padding = new Padding(0, 0, 0, 10);
			chatPage.RowCount = 3;
			chatPage.RowStyles.Add(new RowStyle(SizeType.Percent, 14.61794F));
			chatPage.RowStyles.Add(new RowStyle(SizeType.Percent, 85.38206F));
			chatPage.RowStyles.Add(new RowStyle(SizeType.Absolute, 30F));
			chatPage.Size = new Size(727, 342);
			chatPage.TabIndex = 2;
			chatPage.Visible = false;
			// 
			// chatContents
			// 
			chatContents.BackColor = SystemColors.ControlDark;
			chatContents.Dock = DockStyle.Fill;
			chatContents.Location = new Point(52, 47);
			chatContents.Name = "chatContents";
			chatContents.Size = new Size(470, 251);
			chatContents.TabIndex = 7;
			// 
			// chatInputBox
			// 
			chatInputBox.Dock = DockStyle.Fill;
			chatInputBox.Location = new Point(3, 3);
			chatInputBox.Name = "chatInputBox";
			chatInputBox.Size = new Size(400, 23);
			chatInputBox.TabIndex = 8;
			// 
			// mainMenuStrip
			// 
			mainMenuStrip.Items.AddRange(new ToolStripItem[] { 파일ToolStripMenuItem, 도움말ToolStripMenuItem });
			mainMenuStrip.Location = new Point(0, 0);
			mainMenuStrip.Name = "mainMenuStrip";
			mainMenuStrip.Size = new Size(727, 24);
			mainMenuStrip.TabIndex = 4;
			mainMenuStrip.Text = "menuStrip1";
			// 
			// 파일ToolStripMenuItem
			// 
			파일ToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { signInMenuItem, signOutMenuItem, settingMenuItem, toolStripSeparator1, quitMenuItem });
			파일ToolStripMenuItem.Name = "파일ToolStripMenuItem";
			파일ToolStripMenuItem.ShortcutKeys =  Keys.Alt | Keys.T;
			파일ToolStripMenuItem.Size = new Size(57, 20);
			파일ToolStripMenuItem.Text = "도구(&T)";
			// 
			// signInMenuItem
			// 
			signInMenuItem.Name = "signInMenuItem";
			signInMenuItem.Size = new Size(156, 22);
			signInMenuItem.Text = "로그인(&E)";
			signInMenuItem.Click += 로그인ToolStripMenuItem_Click;
			// 
			// signOutMenuItem
			// 
			signOutMenuItem.Name = "signOutMenuItem";
			signOutMenuItem.Size = new Size(156, 22);
			signOutMenuItem.Text = "로그아웃(&E)";
			signOutMenuItem.Click += signOutMenuItem_Click;
			// 
			// settingMenuItem
			// 
			settingMenuItem.Name = "settingMenuItem";
			settingMenuItem.Size = new Size(156, 22);
			settingMenuItem.Text = "설정(&S)";
			settingMenuItem.Click += 설정ToolStripMenuItem_Click;
			// 
			// toolStripSeparator1
			// 
			toolStripSeparator1.Name = "toolStripSeparator1";
			toolStripSeparator1.Size = new Size(153, 6);
			// 
			// quitMenuItem
			// 
			quitMenuItem.AccessibleName = "Close";
			quitMenuItem.Name = "quitMenuItem";
			quitMenuItem.ShortcutKeyDisplayString = "";
			quitMenuItem.ShortcutKeys =  Keys.Alt | Keys.F4;
			quitMenuItem.Size = new Size(156, 22);
			quitMenuItem.Text = "닫기(&X)";
			quitMenuItem.Click += 닫기ToolStripMenuItem_Click;
			// 
			// 도움말ToolStripMenuItem
			// 
			도움말ToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { 정보ToolStripMenuItem });
			도움말ToolStripMenuItem.Name = "도움말ToolStripMenuItem";
			도움말ToolStripMenuItem.ShortcutKeys =  Keys.Alt | Keys.H;
			도움말ToolStripMenuItem.Size = new Size(72, 20);
			도움말ToolStripMenuItem.Text = "도움말(&H)";
			// 
			// 정보ToolStripMenuItem
			// 
			정보ToolStripMenuItem.Name = "정보ToolStripMenuItem";
			정보ToolStripMenuItem.ShortcutKeys = Keys.F1;
			정보ToolStripMenuItem.Size = new Size(118, 22);
			정보ToolStripMenuItem.Text = "정보";
			// 
			// signInPage
			// 
			signInPage.Controls.Add(signInButton);
			signInPage.Dock = DockStyle.Fill;
			signInPage.Location = new Point(0, 0);
			signInPage.Name = "signInPage";
			signInPage.Size = new Size(727, 388);
			signInPage.TabIndex = 5;
			// 
			// signInButton
			// 
			signInButton.Location = new Point(326, 160);
			signInButton.Name = "signInButton";
			signInButton.Size = new Size(75, 23);
			signInButton.TabIndex = 3;
			signInButton.Text = "Sign In";
			signInButton.UseVisualStyleBackColor = true;
			signInButton.Click += signInButton_Click;
			// 
			// toolStripStatusLabel1
			// 
			toolStripStatusLabel1.Name = "toolStripStatusLabel1";
			toolStripStatusLabel1.Size = new Size(121, 17);
			toolStripStatusLabel1.Text = "toolStripStatusLabel1";
			// 
			// toolStripStatusLabel2
			// 
			toolStripStatusLabel2.Name = "toolStripStatusLabel2";
			toolStripStatusLabel2.Size = new Size(121, 17);
			toolStripStatusLabel2.Text = "toolStripStatusLabel2";
			// 
			// toolStripStatusLabel3
			// 
			toolStripStatusLabel3.Name = "toolStripStatusLabel3";
			toolStripStatusLabel3.Size = new Size(121, 17);
			toolStripStatusLabel3.Text = "toolStripStatusLabel3";
			// 
			// statusStrip1
			// 
			statusStrip1.Items.AddRange(new ToolStripItem[] { toolStripStatusLabel1, toolStripStatusLabel2, toolStripStatusLabel3 });
			statusStrip1.Location = new Point(0, 366);
			statusStrip1.Name = "statusStrip1";
			statusStrip1.Size = new Size(727, 22);
			statusStrip1.TabIndex = 3;
			statusStrip1.Text = "statusStrip1";
			// 
			// inputLayer
			// 
			inputLayer.ColumnCount = 2;
			inputLayer.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 50F));
			inputLayer.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 68F));
			inputLayer.Controls.Add(chatInputBox, 0, 0);
			inputLayer.Controls.Add(chatSendButton, 1, 0);
			inputLayer.Dock = DockStyle.Fill;
			inputLayer.Location = new Point(50, 302);
			inputLayer.Margin = new Padding(1);
			inputLayer.Name = "inputLayer";
			inputLayer.RowCount = 1;
			inputLayer.RowStyles.Add(new RowStyle(SizeType.Percent, 50F));
			inputLayer.Size = new Size(474, 29);
			inputLayer.TabIndex = 9;
			// 
			// chatSendButton
			// 
			chatSendButton.Location = new Point(409, 3);
			chatSendButton.Name = "chatSendButton";
			chatSendButton.Size = new Size(62, 23);
			chatSendButton.TabIndex = 9;
			chatSendButton.Text = "Send";
			chatSendButton.UseVisualStyleBackColor = true;
			// 
			// memberListBox
			// 
			memberListBox.Dock = DockStyle.Fill;
			memberListBox.FormattingEnabled = true;
			memberListBox.ImeMode = ImeMode.NoControl;
			memberListBox.ItemHeight = 15;
			memberListBox.Location = new Point(528, 47);
			memberListBox.Name = "memberListBox";
			memberListBox.Size = new Size(196, 251);
			memberListBox.Sorted = true;
			memberListBox.TabIndex = 10;
			// 
			// Form1
			// 
			AutoScaleDimensions = new SizeF(7F, 15F);
			AutoScaleMode = AutoScaleMode.Font;
			ClientSize = new Size(727, 388);
			Controls.Add(chatPage);
			Controls.Add(statusStrip1);
			Controls.Add(mainMenuStrip);
			Controls.Add(signInPage);
			MainMenuStrip = mainMenuStrip;
			Margin = new Padding(2);
			Name = "Form1";
			Text = "Form1";
			Load += Form1_Load;
			chatPage.ResumeLayout(false);
			mainMenuStrip.ResumeLayout(false);
			mainMenuStrip.PerformLayout();
			signInPage.ResumeLayout(false);
			statusStrip1.ResumeLayout(false);
			statusStrip1.PerformLayout();
			inputLayer.ResumeLayout(false);
			inputLayer.PerformLayout();
			ResumeLayout(false);
			PerformLayout();
		}

		#endregion
		private TableLayoutPanel chatPage;
		private MenuStrip mainMenuStrip;
		private ToolStripMenuItem 파일ToolStripMenuItem;
		private ToolStripMenuItem 도움말ToolStripMenuItem;
		private System.ComponentModel.BackgroundWorker backgroundWorker1;
		private ToolStripMenuItem signInMenuItem;
		private ToolStripMenuItem settingMenuItem;
		private ToolStripSeparator toolStripSeparator1;
		private ToolStripMenuItem quitMenuItem;
		private ToolStripMenuItem 정보ToolStripMenuItem;
		private Panel chatContents;
		private Panel signInPage;
		private Button signInButton;
		private ToolStripMenuItem signOutMenuItem;
		private TextBox chatInputBox;
		private ToolStripStatusLabel toolStripStatusLabel1;
		private ToolStripStatusLabel toolStripStatusLabel2;
		private ToolStripStatusLabel toolStripStatusLabel3;
		private StatusStrip statusStrip1;
		private TableLayoutPanel inputLayer;
		private Button chatSendButton;
		private ListBox memberListBox;
	}
}
