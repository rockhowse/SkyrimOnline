//--------------------------------------------------------------------------------
/// @author Maxime GRIOT
//--------------------------------------------------------------------------------

using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.Globalization;
using System.Reflection;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using SharpSvn;
using System.Net;
using Updater.Properties;
using System.Drawing;
using System.Media;

namespace Updater
{
    public partial class Panel : Form
    {
        /// <summary>
        /// Init the panel app
        /// </summary>
        public Panel()
        {
            hoverPlayer = new SoundPlayer(Resources.ui_hover);
            exitPlayer = new SoundPlayer(Resources.ui_exit);
            clickPlayer = new SoundPlayer(Resources.ui_click);

            this.SetStyle(ControlStyles.SupportsTransparentBackColor, true);
            InitializeComponent();
         

            isConnected = false;
            updated = false;

            svnWorker.RunWorkerAsync();
            statusWorker.RunWorkerAsync();
        }

        /// <summary>
        /// Handles exit event
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void onExitClick(object sender, EventArgs e)
        {
            playExit();
            Application.Exit();
        }

        private void onButtonClick(object sender, EventArgs e)
        {
            try
            {
                playClick();
                System.Diagnostics.Process process = new System.Diagnostics.Process();
                process.StartInfo.FileName = "TESV.exe";
                process.Start();
                this.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show("I was unable to find TESV.exe ! Check that you installed me in the correct folder !");
            }
        }

        private void onPlayMouseEnter(object sender, EventArgs e)
        {
            if(Play.Enabled)
                playHover();
            Play.Image = Resources.playhover;
        }

        private void onPlayMouseLeave(object sender, EventArgs e)
        {
            Play.Image = Resources.play;
        }

        private void minimize_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
        }


        private void onFormMouseDown(object sender, MouseEventArgs e)
        {
            dragging = true;
            dragCursorPoint = Cursor.Position;
            dragFormPoint = this.Location;
        }

        private void onFormMouseMove(object sender, MouseEventArgs e)
        {
            if (dragging)
            {
                Point dif = Point.Subtract(Cursor.Position, new Size(dragCursorPoint));
                this.Location = Point.Add(dragFormPoint, new Size(dif));
            }
        }

        private void onFormMouseUp(object sender, MouseEventArgs e)
        {
            dragging = false;
        }

        private void onSvnNotify(object sender, SvnNotifyEventArgs e)
        {
            if (e == null) return;

            if (e.CommandType.ToString() == "CheckOut" || e.CommandType.ToString() == "Update")
            {
                if (System.IO.Directory.GetCurrentDirectory() != e.FullPath)
                {
                    iSize += 1;
                    svnWorker.ReportProgress(iSize);
                }
            }
        }

        /// <summary>
        /// While the server isn't up to date
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void doSvnUpdate(object sender, DoWorkEventArgs e)
        {
            client = new SvnClient();
            client.Notify += onSvnNotify;
            client.Authentication.Clear();
            client.Authentication.DefaultCredentials = new System.Net.NetworkCredential("public","public");

            System.Console.Out.WriteLine(client.GetUriFromWorkingCopy(System.IO.Directory.GetCurrentDirectory()));

            Uri rep = client.GetUriFromWorkingCopy(System.IO.Directory.GetCurrentDirectory());
            Uri rel = new Uri("http://skyrim-online.com:4430/svn/skyrimonline/");
            //Uri rel = new Uri("http://subversion.assembla.com/svn/skyrimonlinepublic/");

            if (rep == null || rep != rel)
            {
                SvnDelete.findSvnDirectories(System.IO.Directory.GetCurrentDirectory());
                exploreDirectory(rel);

                download.Maximum = iCount;
                updating = true;

                SvnCheckOutArgs args = new SvnCheckOutArgs();
                args.AllowObstructions = true;

                if (client.CheckOut(rel, System.IO.Directory.GetCurrentDirectory(), args, out mResult))
                {
                    updated = true;
                }
                
            }
            else
            {
                downloadprogress.Text = "Building update list, please be patient...";


                updating = true;
                SvnStatusArgs sa = new SvnStatusArgs();
                sa.RetrieveRemoteStatus = true;

                Collection<SvnStatusEventArgs> r;
                client.GetStatus(System.IO.Directory.GetCurrentDirectory(), sa, out r);

                foreach (SvnStatusEventArgs i in r)
                {
                    client.Revert(i.FullPath);

                    if (i.IsRemoteUpdated)
                        iCount++;
                }

                download.Maximum = iCount;
                SvnUpdateArgs args = new SvnUpdateArgs();
                args.AllowObstructions = true;

                if (client.Update(System.IO.Directory.GetCurrentDirectory(), args))
                {
                    updated = true;
                }
                else
                {
                    Application.Exit();
                }
            }
        }

        private void svnUpdateChanged(object sender, ProgressChangedEventArgs e)
        {
            if (updating)
            {
                if (iSize > download.Maximum)
                    download.Maximum = iSize;

                download.Value = iSize;
                downloadprogress.Text = iSize.ToString() + " of " + download.Maximum + " files downloaded.";
            }
            else
                downloadprogress.Text = "Building update list " + iCount.ToString() + " files.";
        }

        private void svnUpdateDone(object sender, RunWorkerCompletedEventArgs e)
        {
            if (updated)
            {
                Play.Enabled = true;
                download.Visible = false;
                downloadprogress.Text = "Ready to play !";
            }
            else
            {
                iSize = 0;
                iCount = 0;
                updating = false;
                download.Value = 0;
                download.Maximum = 0;
                downloadprogress.Text = "I am recovering a fail update, please be patient.";
                SvnDelete.findSvnDirectories(System.IO.Directory.GetCurrentDirectory());

                svnWorker.RunWorkerAsync();
            }
        }

        private void exploreDirectory(Uri path)
        {
            Collection<SvnListEventArgs> list;
            bool gotList = client.GetList(path, out list);

            if (gotList)
            {
                foreach (SvnListEventArgs item in list)
                {
                    iCount++;
                    svnWorker.ReportProgress(iCount);

                    if (item.Entry.NodeKind == SvnNodeKind.Directory)
                    {
                        if (item.Uri != path)
                            exploreDirectory(item.Uri);
                    }
                }
            }
        }

        private void doStatusUpdate(object sender, DoWorkEventArgs e)
        {
            while (!updated)
            {
                if (iStars == 20)
                    iStars = 0;

                downloadspeed.Text = "Please be patient this may take a few hours...";
                for (int i = 0; i < iStars; ++i)
                    downloadspeed.Text += '.';
                ++iStars;

                Thread.Sleep(500);
            }
        }

        private void statusUpdateDone(object sender, RunWorkerCompletedEventArgs e)
        {
            downloadspeed.Text = "";
        }

        private void playHover()
        {
            hoverPlayer.Play();
        }

        private void playExit()
        {
            exitPlayer.Play();
        }

        private void playClick()
        {
            clickPlayer.Play();
        }


        bool updating;
        bool isConnected;
        bool updated;
        Int32 iCount;
        Int16 iStars;
        Int32 iSize;
        SvnClient client;
        SharpSvn.SvnUpdateResult mResult;

        private bool dragging = false;
        private Point dragCursorPoint;
        private Point dragFormPoint;

        SoundPlayer hoverPlayer, exitPlayer, clickPlayer;

        private void minimize_MouseEnter(object sender, EventArgs e)
        {
            playHover();
        }

        private void exit_MouseEnter(object sender, EventArgs e)
        {
            playHover();
        }


    }
}