using Skyrim.Game.IO;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
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

        public Play()
        {
            InitializeComponent();

            client = new IO.MasterClient();

            LoadServerList();

            serverList.ListViewItemSorter = sorter;
            client.Updated += new EventHandler(clientUpdated);
            Application.Idle += new EventHandler(AppIdle);
        }

        private void clientUpdated(object sender, EventArgs e)
        {
            //Pop the incoming server object from the queue
            var server = client.m_serverQueue.Dequeue();

            //If a listview item with the same id/key as the incoming server exists already, remove it
            serverList.Items.RemoveByKey(server.GetValue(0).ToString());

            //Add the new server to the listview, using the id as the key
            var item = serverList.Items.Add(server.GetValue(0).ToString(), server.GetValue(1).ToString(), "");
            item.SubItems.Add(server.GetValue(2).ToString());
            item.SubItems.Add(server.GetValue(3).ToString());
        }

        private void disableButton_Click(object sender, EventArgs e)
        {
            Entry.Enabled = false;
            this.Close();
        }

        private void playButton_Click(object sender, EventArgs e)
        {
            Entry.Enabled = true;
            this.Close();
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

        private void HandleServer(string name, string population, string maxPopulation, string id)
        {
            var item = serverList.Items.Add(name);
            item.SubItems.Add(population.ToString());
            item.SubItems.Add(maxPopulation.ToString());
            item.SubItems.Add(id.ToString());
        }

        private void LoadServerList()
        {
            serverList.Items.Clear();
            client.GetServerList(MASTER_SERVER_ADDRESS);
        }

       
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
            while(AppStillIdle)
                client.Update();
        }

        private void serverList_SelectedIndexChanged(object sender, EventArgs e)
        {
            ListView.SelectedListViewItemCollection selectedServers = serverList.SelectedItems;
            foreach (ListViewItem server in selectedServers)
            {
                if (server != null)
                    playButton.Enabled = true;
                break;
            }
        }
    }
}
