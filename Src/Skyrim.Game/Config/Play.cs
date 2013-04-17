using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Skyrim.Game.Config
{
    public partial class Play : Form
    {
        private ListViewColumnSorter sorter = new ListViewColumnSorter();

        public ListView List
        {
            get { return listView1; }
        }

        public Play()
        {
            InitializeComponent();

            Entry.Client = new IO.MasterClient();
            Entry.Client.GetServerList("127.0.0.1");

            listView1.ListViewItemSorter = sorter;
            Application.Idle += new EventHandler(AppIdle);
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

        private void listView1_ColumnClick(object sender, ColumnClickEventArgs e)
        {
            // Déterminer si la colonne sélectionnée est déjà la colonne triée.
            if (e.Column == sorter.SortColumn)
            {
                // Inverser le sens de tri en cours pour cette colonne.
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
                // Définir le numéro de colonne à trier ; par défaut sur croissant.
                sorter.SortColumn = e.Column;
                sorter.Order = SortOrder.Ascending;
            }

            // Procéder au tri avec les nouvelles options.
            this.listView1.Sort();
        }

        static void AppIdle(object sender, EventArgs e)
        {
            Entry.Client.Update();
        }
    }
}
