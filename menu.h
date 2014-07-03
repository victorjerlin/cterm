void redrawClusterMenu (int oldcluster, int newcluster);
void deleteFromMenu (struct clusterapps *cluster);
void AddItemTo (GtkWidget *members, char *infoline);
void DeleteItemFrom (GtkWidget *members, char *item);
GtkWidget *createMenubar (GtkWidget * window);
void menuAddWindow (GtkWidget * w, gpointer data);
void menuDeleteWindow (GtkWidget * w, gpointer data);


#ifdef __MENU_C
  GtkItemFactoryEntry menuItems[] = {
    {"/_File", NULL, NULL, 0, "<Branch>"},
    {"/File/Add window", "<control><shift>N", menuAddWindow, 0, "<StockItem>", GTK_STOCK_NEW},
    {"/File/Delete window", "<control><shift>R", menuDeleteWindow, 0, "<StockItem>", GTK_STOCK_SAVE},
    {"/File/sep1", NULL, NULL, 0, "<Separator>"},
    {"/File/_Quit", "<control><shift>Q", gtk_main_quit, 0, "<StockItem>", GTK_STOCK_QUIT},
    {"/Cluster", NULL, NULL, 0, "<Branch>"},
    {"/Cluster/All", NULL, toCluster, 0, "<RadioItem>"},
    {"/Cluster/sep", NULL, NULL, 0, "<Separator>"},
    {"/Cluster/c1", NULL, toCluster, 1, "/Cluster/All"},
    {"/Cluster/c2", NULL, toCluster, 2, "/Cluster/All"},
    {"/Cluster/c3", NULL, toCluster, 3, "/Cluster/All"},
    {"/Cluster/c4", NULL, toCluster, 4, "/Cluster/All"},
    {"/Cluster/c5", NULL, toCluster, 5, "/Cluster/All"},
    {"/Cluster/c6", NULL, toCluster, 6, "/Cluster/All"},
    {"/Cluster/c7", NULL, toCluster, 7, "/Cluster/All"},
    {"/Cluster/c8", NULL, toCluster, 8, "/Cluster/All"},
    {"/Cluster/c9", NULL, toCluster, 9, "/Cluster/All"},
    {"/Members", NULL, NULL, 0, "<Branch>"},
    {"/_Help", NULL, NULL, 0, "<LastBranch>"},
    {"/_Help/About", NULL, showabout, 0, "<Item>"},
  };
  gint nmenuItems = sizeof (menuItems) / sizeof (menuItems[0]);
  GtkItemFactory *itemFactory;
#else
  extern GtkItemFactoryEntry menuItems[];
  extern gint nmenuItems;
  extern GtkItemFactory *itemFactory;
#endif
