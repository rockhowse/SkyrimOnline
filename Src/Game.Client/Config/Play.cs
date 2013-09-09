#region

using System;
using System.Diagnostics;
using System.Drawing;
using System.Net;
using System.Runtime.InteropServices;
using System.Security;
using System.Windows.Forms;
using Game.Client.IO;

#endregion

namespace Game.Client.Config
{
    public partial class Play : Form
    {
        private static string MASTER_SERVER_ADDRESS = "game.skyrim-online.com";

        // Added
        public static readonly string NOT_A_NUMBER = "Only numbers in Port field !!!";
        public static readonly string NO_PORT_SET = "Before join, add server port";
        public static readonly string NO_ADDRESS_SET = "Before join, add server address: IP or server Name";
        private readonly MasterClient client;
        private readonly ListViewColumnSorter sorter = new ListViewColumnSorter();
        private Int64 GAME_SERVER_ID;
        private string address = "127.0.0.1";
        private bool connecting;
        private int port = 14243;
        //

        /// <summary>
        ///     TODO
        /// </summary>
        public Play()
        {
            InitializeComponent();
            client = new MasterClient();

            client.Updated += clientUpdated;
            client.NatIntroductionSuccess += natIntroductionSuccess;

            LoadServerList();

            serverList.ListViewItemSorter = sorter;

            Application.Idle += AppIdle;
        }

        /// <summary>
        ///     TODO
        /// </summary>
        /// <param name="server"></param>
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

        /// <summary>
        ///     TODO
        /// </summary>
        /// <param name="message"></param>
        private void connectionSuccess(string message)
        {
            Entry.Enabled = true;
            Close();
        }

        /// <summary>
        ///     TODO
        /// </summary>
        /// <param name="message"></param>
        private void connectionFailed(string message)
        {
            MessageBox.Show(message);

            playButton.Enabled = true;
            DirectConnect_Button.Enabled = true;
            singlePlayerButton.Enabled = true;
        }

        /// <summary>
        ///     TODO
        /// </summary>
        /// <param name="endpoint"></param>
        private void natIntroductionSuccess(IPEndPoint endpoint)
        {
            m_timer.Enabled = false;

            Entry.GameClient = new GameClient(endpoint);

            Entry.GameClient.ConnectionSuccess += connectionSuccess;
            Entry.GameClient.ConnectionFailed += connectionFailed;

            Entry.Username = playerNameBox.Text;

            Entry.GameClient.Connect();
        }

        /// <summary>
        ///     TODO
        /// </summary>
        private void LoadServerList()
        {
            serverList.Items.Clear();
            client.GetServerList(MASTER_SERVER_ADDRESS);
        }

        /// <summary>
        ///     TODO
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void m_timer_Tick(object sender, EventArgs e)
        {
            connecting = false;
            singlePlayerButton.Enabled = true;
            serverList_SelectedIndexChanged(null, null);
            m_timer.Enabled = false;
        }

        /// <summary>
        ///     TODO
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void onDirectConnectClick(object sender, EventArgs e)
        {
            if (DirectConnectPort_TextBox.Text != null && DirectConnectAddress_TextBox.Text != null)
            {
                Boolean isPortSet = false, isAddressSet = false;

                if (DirectConnectAddress_TextBox.Text.Equals(""))
                {
                    MessageBox.Show(NO_ADDRESS_SET);
                }
                else
                {
                    address = DirectConnectAddress_TextBox.Text;
                    isAddressSet = true;
                }

                if (DirectConnectPort_TextBox.Text.Equals(""))
                {
                    MessageBox.Show(NO_PORT_SET);
                }
                else
                {
                    port = Int32.Parse(DirectConnectPort_TextBox.Text);
                    isPortSet = true;
                }

                if (isAddressSet && isPortSet)
                {
                    DirectConnect_Button.Enabled = false;
                    IPAddress ipAddress = IPAddress.Parse(address);
                    natIntroductionSuccess(new IPEndPoint(ipAddress.MapToIPv4(), port));
                }
            }
        }

        /// <summary>
        ///     TODO
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void onExitButton_Click(object sender, EventArgs e)
        {
            Visible = false;
            Process.GetCurrentProcess().Kill();
        }

        /// <summary>
        ///     TODO
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void onDirectConnectPort_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsDigit(e.KeyChar) && !char.IsControl(e.KeyChar))
            {
                MessageBox.Show(NOT_A_NUMBER);
                e.Handled = true;
            }
        }

        #region Idle

        public bool AppStillIdle
        {
            get
            {
                PeekMsg msg;
                return !PeekMessage(out msg, IntPtr.Zero, 0, 0, 0);
            }
        }

        [SuppressUnmanagedCodeSecurity]
        [DllImport("User32.dll", CharSet = CharSet.Auto)]
        public static extern bool PeekMessage(out PeekMsg msg, IntPtr hWnd, uint messageFilterMin, uint messageFilterMax,
            uint flags);

        private void AppIdle(object sender, EventArgs e)
        {
            while (AppStillIdle)
            {
                if (Entry.GameClient != null)
                    Entry.GameClient.Update();
                client.Update();
            }
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct PeekMsg
        {
            public IntPtr hWnd;
            public Message msg;
            public IntPtr wParam;
            public IntPtr lParam;
            public uint time;
            public Point p;
        }

        #endregion

        #region UIEvents

        private void singlePlayerButton_Click(object sender, EventArgs e)
        {
            Entry.Enabled = false;
            Close();
        }

        private void playButton_Click(object sender, EventArgs e)
        {
            if (GAME_SERVER_ID != 0)
            {
                connecting = true;
                m_timer.Enabled = true;

                // client.RequestNATIntroduction(GAME_SERVER_ID);
                natIntroductionSuccess(client.GetServerIPByKey(GAME_SERVER_ID));

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

            serverList.Sort();
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
                        GAME_SERVER_ID = (long) server.Tag;
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
    }
}