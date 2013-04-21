using Skyrim.Game.IO;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Skyrim.Game.Config
{
    public partial class Play : Form
    {
        private ListViewColumnSorter sorter = new ListViewColumnSorter();
        private MasterClient client = null;
        private static string MASTER_SERVER_ADDRESS = "127.0.0.1";
        private Int64 GAME_SERVER_ID = 0;
        private bool connecting = false;

        public Play()
        {
            InitializeComponent();

            client = new IO.MasterClient();

            client.Updated += clientUpdated;
            client.NatIntroductionSuccess += natIntroductionSuccess;

            LoadServerList();

            serverList.ListViewItemSorter = sorter;

            Application.Idle += new EventHandler(AppIdle);
        }

        private void clientUpdated(object[] server)
        {

            //If a listview item with the same id/key as the incoming server exists already, remove it
            serverList.Items.RemoveByKey(server.GetValue(0).ToString());

            //Add the new server to the listview, using the id as the key
            var item = serverList.Items.Add(server.GetValue(0).ToString(), server.GetValue(1).ToString(), "");
            item.Tag = server.GetValue(0);

            item.SubItems.Add(server.GetValue(2).ToString());
            item.SubItems.Add(server.GetValue(3).ToString());
        }

        private void connectionSuccess()
        {
            Entry.Enabled = true;
            this.Close();
        }

        private void connectionFailed()
        {
            playButton.Enabled = true;
            singlePlayerButton.Enabled = true;
        }

        private void natIntroductionSuccess(IPEndPoint endpoint)
        {
            m_timer.Enabled = false;

            Entry.GameClient = new GameClient(endpoint);

            Entry.GameClient.ConnectionSuccess += connectionSuccess;
            Entry.GameClient.ConnectionFailed += connectionFailed;

            Entry.GameClient.Connect();
        }

        private void LoadServerList()
        {
            serverList.Items.Clear();
            client.GetServerList(MASTER_SERVER_ADDRESS);
        }


        #region Idle

        [StructLayout(LayoutKind.Sequential)]
        public struct PeekMsg
        {
            public IntPtr hWnd;
            public Message msg;
            public IntPtr wParam;
            public IntPtr lParam;
            public uint time;
            public System.Drawing.Point p;
        }

        [System.Security.SuppressUnmanagedCodeSecurity]
        [DllImport("User32.dll", CharSet = CharSet.Auto)]
        public static extern bool PeekMessage(out PeekMsg msg, IntPtr hWnd, uint messageFilterMin, uint messageFilterMax, uint flags);

        public bool AppStillIdle
        {
            get
            {
                PeekMsg msg;
                return !PeekMessage(out msg, IntPtr.Zero, 0, 0, 0);
            }
        }

        void AppIdle(object sender, EventArgs e)
        {
            while (AppStillIdle)
            {
                if (Entry.GameClient != null)
                    Entry.GameClient.Update();
                client.Update();
            }
        }

        #endregion

        #region UIEvents

        private void singlePlayerButton_Click(object sender, EventArgs e)
        {
            Entry.Enabled = false;
            this.Close();
        }

        private void playButton_Click(object sender, EventArgs e)
        {
            if (GAME_SERVER_ID != 0)
            {
                connecting = true;
                m_timer.Enabled = true;

                client.RequestNATIntroduction(GAME_SERVER_ID);
                playButton.Enabled = false;
                singlePlayerButton.Enabled = false;
            }
        }

        private void serverList_ColumnClick(object sender, ColumnClickEventArgs e)
        {
            if (e.Column == sorter.SortColumn)
            {
                if (sorter.Order == SortOrder.Ascending)
                {
                    sorter.Order = SortOrder.Descending;
                }
                else
                {
                    sorter.Order = SortOrder.Ascending;
                }
            }
            else
            {
                sorter.SortColumn = e.Column;
                sorter.Order = SortOrder.Ascending;
            }

            this.serverList.Sort();
        }

        private void serverList_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (!connecting)
            {
                ListView.SelectedListViewItemCollection selectedServers = serverList.SelectedItems;
                foreach (ListViewItem server in selectedServers)
                {
                    if (server != null)
                    {
                        GAME_SERVER_ID = (long)server.Tag;
                        IPEndPoint gameServerIp = client.GetServerIPByKey(GAME_SERVER_ID);
                        selectedServerKey.Text = gameServerIp.ToString();
                        playButton.Enabled = true;
                    }
                    else
                        playButton.Enabled = false;
                    break;
                }
            }
        }

        #endregion

        private void m_timer_Tick(object sender, EventArgs e)
        {
            connecting = false;
            singlePlayerButton.Enabled = true;
            serverList_SelectedIndexChanged(null, null);
            m_timer.Enabled = false;
        }
    }
}
