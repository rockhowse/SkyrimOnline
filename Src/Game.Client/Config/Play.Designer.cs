namespace Game.Client.Config
{
    partial class Play
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.ColumnHeader populationHeader;
            System.Windows.Forms.ColumnHeader maximumHeader;
            this.singlePlayerButton = new System.Windows.Forms.Button();
            this.playButton = new System.Windows.Forms.Button();
            this.serverList = new System.Windows.Forms.ListView();
            this.nameHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.label1 = new System.Windows.Forms.Label();
            this.playerNameBox = new System.Windows.Forms.TextBox();
            this.playerNameLabel = new System.Windows.Forms.Label();
            this.selectedServerKey = new System.Windows.Forms.Label();
            this.m_timer = new System.Windows.Forms.Timer(this.components);
            this.Exit_Button = new System.Windows.Forms.Button();
            this.DirectConnect_Button = new System.Windows.Forms.Button();
            this.DirectConnect_Label = new System.Windows.Forms.Label();
            this.DirectConnectAddress_TextBox = new System.Windows.Forms.TextBox();
            this.DirectConnectPort_TextBox = new System.Windows.Forms.TextBox();
            this.DirectConnectPort_Label = new System.Windows.Forms.Label();
            this.DirectConnectAddress_Label = new System.Windows.Forms.Label();
            populationHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            maximumHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.SuspendLayout();
            // 
            // populationHeader
            // 
            populationHeader.Tag = "populationHeader";
            populationHeader.Text = "Population";
            populationHeader.Width = 78;
            // 
            // maximumHeader
            // 
            maximumHeader.Tag = "maximumHeader";
            maximumHeader.Text = "Maximum";
            maximumHeader.Width = 66;
            // 
            // singlePlayerButton
            // 
            this.singlePlayerButton.Location = new System.Drawing.Point(360, 288);
            this.singlePlayerButton.Name = "singlePlayerButton";
            this.singlePlayerButton.Size = new System.Drawing.Size(147, 23);
            this.singlePlayerButton.TabIndex = 0;
            this.singlePlayerButton.Text = "Single player";
            this.singlePlayerButton.UseVisualStyleBackColor = true;
            this.singlePlayerButton.Click += new System.EventHandler(this.singlePlayerButton_Click);
            // 
            // playButton
            // 
            this.playButton.Enabled = false;
            this.playButton.Location = new System.Drawing.Point(360, 259);
            this.playButton.Name = "playButton";
            this.playButton.Size = new System.Drawing.Size(147, 23);
            this.playButton.TabIndex = 1;
            this.playButton.Text = "Join server";
            this.playButton.UseVisualStyleBackColor = true;
            this.playButton.Click += new System.EventHandler(this.playButton_Click);
            // 
            // serverList
            // 
            this.serverList.Alignment = System.Windows.Forms.ListViewAlignment.Default;
            this.serverList.AutoArrange = false;
            this.serverList.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.nameHeader,
            populationHeader,
            maximumHeader});
            this.serverList.FullRowSelect = true;
            this.serverList.GridLines = true;
            this.serverList.Location = new System.Drawing.Point(10, 40);
            this.serverList.MultiSelect = false;
            this.serverList.Name = "serverList";
            this.serverList.Size = new System.Drawing.Size(340, 300);
            this.serverList.TabIndex = 2;
            this.serverList.UseCompatibleStateImageBehavior = false;
            this.serverList.View = System.Windows.Forms.View.Details;
            this.serverList.ColumnClick += new System.Windows.Forms.ColumnClickEventHandler(this.serverList_ColumnClick);
            this.serverList.SelectedIndexChanged += new System.EventHandler(this.serverList_SelectedIndexChanged);
            // 
            // nameHeader
            // 
            this.nameHeader.Tag = "nameHeader";
            this.nameHeader.Text = "Name";
            this.nameHeader.Width = 193;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(59, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Server list :";
            // 
            // playerNameBox
            // 
            this.playerNameBox.Location = new System.Drawing.Point(360, 65);
            this.playerNameBox.MaxLength = 100;
            this.playerNameBox.Name = "playerNameBox";
            this.playerNameBox.Size = new System.Drawing.Size(147, 20);
            this.playerNameBox.TabIndex = 4;
            this.playerNameBox.Text = "Your nick name";
            // 
            // playerNameLabel
            // 
            this.playerNameLabel.AutoSize = true;
            this.playerNameLabel.Location = new System.Drawing.Point(360, 40);
            this.playerNameLabel.Name = "playerNameLabel";
            this.playerNameLabel.Size = new System.Drawing.Size(100, 13);
            this.playerNameLabel.TabIndex = 5;
            this.playerNameLabel.Text = "Input Player Name :";
            // 
            // selectedServerKey
            // 
            this.selectedServerKey.AutoSize = true;
            this.selectedServerKey.Location = new System.Drawing.Point(79, 12);
            this.selectedServerKey.Name = "selectedServerKey";
            this.selectedServerKey.Size = new System.Drawing.Size(0, 13);
            this.selectedServerKey.TabIndex = 6;
            // 
            // m_timer
            // 
            this.m_timer.Interval = 3000;
            this.m_timer.Tick += new System.EventHandler(this.m_timer_Tick);
            // 
            // Exit_Button
            // 
            this.Exit_Button.Location = new System.Drawing.Point(360, 317);
            this.Exit_Button.Name = "Exit_Button";
            this.Exit_Button.Size = new System.Drawing.Size(147, 23);
            this.Exit_Button.TabIndex = 7;
            this.Exit_Button.Text = "Exit";
            this.Exit_Button.UseVisualStyleBackColor = true;
            this.Exit_Button.Click += new System.EventHandler(this.onExitButton_Click);
            // 
            // DirectConnect_Button
            // 
            this.DirectConnect_Button.Location = new System.Drawing.Point(360, 216);
            this.DirectConnect_Button.Name = "DirectConnect_Button";
            this.DirectConnect_Button.Size = new System.Drawing.Size(147, 23);
            this.DirectConnect_Button.TabIndex = 8;
            this.DirectConnect_Button.Text = "Direct connect";
            this.DirectConnect_Button.UseVisualStyleBackColor = true;
            this.DirectConnect_Button.Click += new System.EventHandler(this.onDirectConnectClick);
            // 
            // DirectConnect_Label
            // 
            this.DirectConnect_Label.Location = new System.Drawing.Point(360, 100);
            this.DirectConnect_Label.Name = "DirectConnect_Label";
            this.DirectConnect_Label.Size = new System.Drawing.Size(147, 14);
            this.DirectConnect_Label.TabIndex = 10;
            this.DirectConnect_Label.Text = "Direct connect section";
            this.DirectConnect_Label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // DirectConnectAddress_TextBox
            // 
            this.DirectConnectAddress_TextBox.Location = new System.Drawing.Point(360, 145);
            this.DirectConnectAddress_TextBox.MaxLength = 100;
            this.DirectConnectAddress_TextBox.Name = "DirectConnectAddress_TextBox";
            this.DirectConnectAddress_TextBox.Size = new System.Drawing.Size(146, 20);
            this.DirectConnectAddress_TextBox.TabIndex = 9;
            this.DirectConnectAddress_TextBox.Text = "127.0.0.1";
            // 
            // DirectConnectPort_TextBox
            // 
            this.DirectConnectPort_TextBox.Location = new System.Drawing.Point(360, 190);
            this.DirectConnectPort_TextBox.MaxLength = 100;
            this.DirectConnectPort_TextBox.Name = "DirectConnectPort_TextBox";
            this.DirectConnectPort_TextBox.Size = new System.Drawing.Size(146, 20);
            this.DirectConnectPort_TextBox.TabIndex = 11;
            this.DirectConnectPort_TextBox.Text = "14243";
            this.DirectConnectPort_TextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.onDirectConnectPort_KeyPress);
            // 
            // DirectConnectPort_Label
            // 
            this.DirectConnectPort_Label.AutoSize = true;
            this.DirectConnectPort_Label.Location = new System.Drawing.Point(360, 170);
            this.DirectConnectPort_Label.Name = "DirectConnectPort_Label";
            this.DirectConnectPort_Label.Size = new System.Drawing.Size(63, 13);
            this.DirectConnectPort_Label.TabIndex = 12;
            this.DirectConnectPort_Label.Text = "Server Port:";
            // 
            // DirectConnectAddress_Label
            // 
            this.DirectConnectAddress_Label.AutoSize = true;
            this.DirectConnectAddress_Label.Location = new System.Drawing.Point(360, 125);
            this.DirectConnectAddress_Label.Name = "DirectConnectAddress_Label";
            this.DirectConnectAddress_Label.Size = new System.Drawing.Size(82, 13);
            this.DirectConnectAddress_Label.TabIndex = 13;
            this.DirectConnectAddress_Label.Text = "Only IP Address";
            // 
            // Play
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(514, 347);
            this.ControlBox = false;
            this.Controls.Add(this.DirectConnectAddress_Label);
            this.Controls.Add(this.DirectConnectPort_Label);
            this.Controls.Add(this.DirectConnectPort_TextBox);
            this.Controls.Add(this.DirectConnect_Label);
            this.Controls.Add(this.DirectConnectAddress_TextBox);
            this.Controls.Add(this.DirectConnect_Button);
            this.Controls.Add(this.Exit_Button);
            this.Controls.Add(this.selectedServerKey);
            this.Controls.Add(this.playerNameLabel);
            this.Controls.Add(this.playerNameBox);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.serverList);
            this.Controls.Add(this.playButton);
            this.Controls.Add(this.singlePlayerButton);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(530, 385);
            this.MinimumSize = new System.Drawing.Size(530, 385);
            this.Name = "Play";
            this.Text = "Skyrim Online - Configuration";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button singlePlayerButton;
        private System.Windows.Forms.Button playButton;
        private System.Windows.Forms.ListView serverList;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ColumnHeader nameHeader;
        private System.Windows.Forms.TextBox playerNameBox;
        private System.Windows.Forms.Label playerNameLabel;
        private System.Windows.Forms.Label selectedServerKey;
        private System.Windows.Forms.Timer m_timer;
        private System.Windows.Forms.Button Exit_Button;
        private System.Windows.Forms.Button DirectConnect_Button;
        private System.Windows.Forms.Label DirectConnect_Label;
        private System.Windows.Forms.TextBox DirectConnectAddress_TextBox;
        private System.Windows.Forms.TextBox DirectConnectPort_TextBox;
        private System.Windows.Forms.Label DirectConnectPort_Label;
        private System.Windows.Forms.Label DirectConnectAddress_Label;
    }
}