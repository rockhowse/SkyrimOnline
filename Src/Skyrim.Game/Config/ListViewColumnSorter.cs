using System.Collections;
using System.Windows.Forms;

public class ListViewColumnSorter : IComparer
{
    /// <summary>
    /// Spécifie la colonne à trier
    /// </summary>
    private int ColumnToSort;
    /// <summary>
    /// Spécifie l'ordre de tri (en d'autres termes 'Croissant').
    /// </summary>
    private SortOrder OrderOfSort;
    /// <summary>
    /// Objet de comparaison ne respectant pas les majuscules et minuscules
    /// </summary>
    private CaseInsensitiveComparer ObjectCompare;

    /// <summary>
    /// Constructeur de classe.  Initializes various elements
    /// </summary>
    public ListViewColumnSorter()
    {
        // Initialise la colonne sur '0'
        ColumnToSort = 0;

        // Initialise l'ordre de tri sur 'aucun'
        OrderOfSort = SortOrder.None;

        // Initialise l'objet CaseInsensitiveComparer
        ObjectCompare = new CaseInsensitiveComparer();
    }

    /// <summary>
    /// Cette méthode est héritée de l'interface IComparer.  Il compare les deux objets passés en effectuant une comparaison 
    ///qui ne tient pas compte des majuscules et des minuscules.
    /// </summary>
    /// <param name="x">Premier objet à comparer</param>
    /// <param name="x">Deuxième objet à comparer</param>
    /// <returns>Le résultat de la comparaison. "0" si équivalent, négatif si 'x' est inférieur à 'y' 
    ///et positif si 'x' est supérieur à 'y'</returns>
    public int Compare(object x, object y)
    {
        int compareResult;
        ListViewItem listviewX, listviewY;

        // Envoit les objets à comparer aux objets ListViewItem
        listviewX = (ListViewItem)x;
        listviewY = (ListViewItem)y;

        // Compare les deux éléments
        compareResult = ObjectCompare.Compare(listviewX.SubItems[ColumnToSort].Text, listviewY.SubItems[ColumnToSort].Text);

        // Calcule la valeur correcte d'après la comparaison d'objets
        if (OrderOfSort == SortOrder.Ascending)
        {
            // Le tri croissant est sélectionné, renvoie des résultats normaux de comparaison
            return compareResult;
        }
        else if (OrderOfSort == SortOrder.Descending)
        {
            // Le tri décroissant est sélectionné, renvoie des résultats négatifs de comparaison
            return (-compareResult);
        }
        else
        {
            // Renvoie '0' pour indiquer qu'ils sont égaux
            return 0;
        }
    }

    /// <summary>
    /// Obtient ou définit le numéro de la colonne à laquelle appliquer l'opération de tri (par défaut sur '0').
    /// </summary>
    public int SortColumn
    {
        set
        {
            ColumnToSort = value;
        }
        get
        {
            return ColumnToSort;
        }
    }

    /// <summary>
    /// Obtient ou définit l'ordre de tri à appliquer (par exemple, 'croissant' ou 'décroissant').
    /// </summary>
    public SortOrder Order
    {
        set
        {
            OrderOfSort = value;
        }
        get
        {
            return OrderOfSort;
        }
    }

}