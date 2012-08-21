using System.Drawing;
namespace Updater
{
    partial class Panel
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Panel));
            this.download = new System.Windows.Forms.ProgressBar();
            this.webBrowser1 = new System.Windows.Forms.WebBrowser();
            this.svnWorker = new System.ComponentModel.BackgroundWorker();
            this.downloadprogress = new System.Windows.Forms.Label();
            this.Play = new System.Windows.Forms.Button();
            this.exit = new System.Windows.Forms.Button();
            this.statusWorker = new System.ComponentModel.BackgroundWorker();
            this.downloadspeed = new System.Windows.Forms.Label();
            this.minimize = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // download
            // 
            this.download.Location = new System.Drawing.Point(41, 428);
            this.download.Name = "download";
            this.download.Size = new System.Drawing.Size(486, 20);
            this.download.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.download.TabIndex = 0;
            // 
            // webBrowser1
            // 
            this.webBrowser1.AllowNavigation = false;
            this.webBrowser1.IsWebBrowserContextMenuEnabled = false;
            this.webBrowser1.Location = new System.Drawing.Point(349, 167);
            this.webBrowser1.MinimumSize = new System.Drawing.Size(20, 20);
            this.webBrowser1.Name = "webBrowser1";
            this.webBrowser1.ScrollBarsEnabled = false;
            this.webBrowser1.Size = new System.Drawing.Size(382, 202);
            this.webBrowser1.TabIndex = 1;
            this.webBrowser1.Url = new System.Uri("http://skyrim-online.com/update.php", System.UriKind.Absolute);
            this.webBrowser1.WebBrowserShortcutsEnabled = false;
            // 
            // svnWorker
            // 
            this.svnWorker.WorkerReportsProgress = true;
            this.svnWorker.DoWork += new System.ComponentModel.DoWorkEventHandler(this.doSvnUpdate);
            this.svnWorker.ProgressChanged += new System.ComponentModel.ProgressChangedEventHandler(this.svnUpdateChanged);
            this.svnWorker.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler(this.svnUpdateDone);
            // 
            // downloadprogress
            // 
            this.downloadprogress.AutoSize = true;
            this.downloadprogress.BackColor = System.Drawing.Color.Transparent;
            this.downloadprogress.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.downloadprogress.ForeColor = System.Drawing.Color.DarkOrange;
            this.downloadprogress.Location = new System.Drawing.Point(38, 456);
            this.downloadprogress.Name = "downloadprogress";
            this.downloadprogress.Size = new System.Drawing.Size(0, 13);
            this.downloadprogress.TabIndex = 4;
            // 
            // Play
            // 
            this.Play.BackColor = System.Drawing.Color.Transparent;
            this.Play.BackgroundImage = global::Updater.Properties.Resources.play;
            this.Play.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.Play.Enabled = false;
            this.Play.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Play.Location = new System.Drawing.Point(596, 419);
            this.Play.Name = "Play";
            this.Play.Size = new System.Drawing.Size(135, 65);
            this.Play.TabIndex = 10;
            this.Play.UseVisualStyleBackColor = false;
            this.Play.Click += new System.EventHandler(this.onButtonClick);
            this.Play.MouseEnter += new System.EventHandler(this.onPlayMouseEnter);
            this.Play.MouseLeave += new System.EventHandler(this.onPlayMouseLeave);
            // 
            // exit
            // 
            this.exit.BackColor = System.Drawing.Color.Transparent;
            this.exit.BackgroundImage = global::Updater.Properties.Resources.close;
            this.exit.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.exit.Location = new System.Drawing.Point(740, 1);
            this.exit.Name = "exit";
            this.exit.Size = new System.Drawing.Size(25, 33);
            this.exit.TabIndex = 11;
            this.exit.UseVisualStyleBackColor = false;
            this.exit.Click += new System.EventHandler(this.onExitClick);
            this.exit.MouseEnter += new System.EventHandler(this.exit_MouseEnter);
            // 
            // statusWorker
            // 
            this.statusWorker.DoWork += new System.ComponentModel.DoWorkEventHandler(this.doStatusUpdate);
            this.statusWorker.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler(this.statusUpdateDone);
            // 
            // downloadspeed
            // 
            this.downloadspeed.AutoSize = true;
            this.downloadspeed.BackColor = System.Drawing.Color.Transparent;
            this.downloadspeed.ForeColor = System.Drawing.Color.DarkOrange;
            this.downloadspeed.Location = new System.Drawing.Point(38, 478);
            this.downloadspeed.Name = "downloadspeed";
            this.downloadspeed.Size = new System.Drawing.Size(82, 13);
            this.downloadspeed.TabIndex = 12;
            this.downloadspeed.Text = "downloadspeed";
            // 
            // minimize
            // 
            this.minimize.BackColor = System.Drawing.Color.Transparent;
            this.minimize.BackgroundImage = global::Updater.Properties.Resources.minimize;
            this.minimize.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.minimize.Location = new System.Drawing.Point(714, 0);
            this.minimize.Name = "minimize";
            this.minimize.Size = new System.Drawing.Size(25, 33);
            this.minimize.TabIndex = 13;
            this.minimize.UseVisualStyleBackColor = false;
            this.minimize.Click += new System.EventHandler(this.minimize_Click);
            this.minimize.MouseEnter += new System.EventHandler(this.minimize_MouseEnter);
            // 
            // Panel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Lime;
            this.BackgroundImage = global::Updater.Properties.Resources.launcherframe;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.ClientSize = new System.Drawing.Size(772, 535);
            this.Controls.Add(this.minimize);
            this.Controls.Add(this.downloadspeed);
            this.Controls.Add(this.exit);
            this.Controls.Add(this.Play);
            this.Controls.Add(this.downloadprogress);
            this.Controls.Add(this.webBrowser1);
            this.Controls.Add(this.download);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximumSize = new System.Drawing.Size(772, 535);
            this.MinimumSize = new System.Drawing.Size(772, 535);
            this.Name = "Panel";
            this.TransparencyKey = System.Drawing.Color.Lime;
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.onFormMouseDown);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.onFormMouseMove);
            this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.onFormMouseUp);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion Windows Form Designer generated code

        private System.Windows.Forms.ProgressBar download;
        private System.Windows.Forms.WebBrowser webBrowser1;
        private System.ComponentModel.BackgroundWorker svnWorker;
        private System.Windows.Forms.Label downloadprogress;
        private System.Windows.Forms.Button Play;
        private System.Windows.Forms.Button exit;
        private System.ComponentModel.BackgroundWorker statusWorker;
        private System.Windows.Forms.Label downloadspeed;
        private System.Windows.Forms.Button minimize;
    }
}