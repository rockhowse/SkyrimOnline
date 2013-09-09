#region

using System.Collections;
using System.Windows.Forms;

#endregion

public class ListViewColumnSorter : IComparer
{
    private readonly CaseInsensitiveComparer ObjectCompare;
    private int ColumnToSort;
    private SortOrder OrderOfSort;

    public ListViewColumnSorter()
    {
        ColumnToSort = 0;
        OrderOfSort = SortOrder.None;
        ObjectCompare = new CaseInsensitiveComparer();
    }

    public int SortColumn
    {
        set { ColumnToSort = value; }
        get { return ColumnToSort; }
    }

    public SortOrder Order
    {
        set { OrderOfSort = value; }
        get { return OrderOfSort; }
    }

    public int Compare(object x, object y)
    {
        int compareResult;
        ListViewItem listviewX, listviewY;

        listviewX = (ListViewItem) x;
        listviewY = (ListViewItem) y;

        compareResult = ObjectCompare.Compare(listviewX.SubItems[ColumnToSort].Text,
            listviewY.SubItems[ColumnToSort].Text);

        if (OrderOfSort == SortOrder.Ascending)
        {
            return compareResult;
        }
        if (OrderOfSort == SortOrder.Descending)
        {
            return (-compareResult);
        }
        return 0;
    }
}