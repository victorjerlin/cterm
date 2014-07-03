/* C-TERM - distributes keyboard-presses to several x-windows
 *
 * Copyright (C) 2006-2007 Victor Jerlin <victor@pseudocode.se>
 * +356 9999 0125, +4673 624 7815
 * Flat 18, 5 Alhambra Court, Tower Road, Sliema, SLM15, Malta
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 * $Id: menu.c,v 1.3 2007-02-14 16:29:33 victor Exp $
 */

#include <X11/Xlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

#ifndef XK_LATIN1
  #define XK_LATIN1 1
#endif
#ifndef XK_MISCELLANY
  #define XK_MISCELLANY 1
#endif

#include <X11/keysymdef.h>

#include <X11/cursorfont.h>
#include <X11/Xmu/WinUtil.h>

#define __MENU_C

#include "cterm.h"
#include "window.h"
#include "cluster.h"
#include "misc.h"
#include "about.h"
#include "menu.h"
#include "selectwindow.h"

void checkClusterEntry (void)
{
  GtkWidget *c1Widget;
  c1Widget = gtk_item_factory_get_widget (itemFactory, "/Cluster/c1");
  gtk_check_menu_item_set_state (GTK_CHECK_MENU_ITEM(c1Widget), TRUE);
}

GtkWidget *
createMenubar (GtkWidget * window)
{ 
  GtkAccelGroup *accelGroup;

  accelGroup = gtk_accel_group_new ();

  /* Make an ItemFactory */
  itemFactory = gtk_item_factory_new (GTK_TYPE_MENU_BAR, "<main>", accelGroup);
  gtk_item_factory_create_items (itemFactory, nmenuItems, menuItems, NULL);
  gtk_window_add_accel_group (GTK_WINDOW (window), accelGroup);

  checkClusterEntry ();
  
  return gtk_item_factory_get_widget (itemFactory, "<main>");
}

void
menuAddWindow (GtkWidget * w, gpointer data)
{
  if (verbose)
    g_message ("Adding Window\n");
  AddWindow ();
}

void
menuDeleteWindow (GtkWidget * w, gpointer data)
{
  Window tmpWindow;

  if (verbose)
    g_message ("Deleting Window\n");
  tmpWindow = selectWindow (display, defaultScreen);
  tmpWindow = XmuClientWindow (display, tmpWindow);
  deleteFromCluster (tmpWindow, (cluster == 0) ? 1 : 0);
}

void
AddItemTo (GtkWidget *members, char *infoline)
{
  char *location;
  char *theString;

  theString = fixSlashes (infoline);
  location = (char *) malloc (sizeof (char) * (strlen (theString) + 10));
  sprintf (location, "/Members/%s", theString);
  GtkItemFactoryEntry membersMenu = { location, NULL, NULL, 0, "<Item>" };
  gtk_item_factory_create_item (itemFactory, &membersMenu, NULL, 1);
  free (theString);
  free (location);
}

void
DeleteItemFrom (GtkWidget *members, char *item)
{
  gtk_item_factory_delete_item (itemFactory, item);
}

void
redrawClusterMenu (int oldcluster, int newcluster)
{
  struct clusterapps *t_ca = windows;

  for (; t_ca != NULL; t_ca = t_ca->next)
    {
      if (!oldcluster || t_ca->clusterid == oldcluster)
        deleteFromMenu (t_ca);
    }

  for (t_ca = windows; t_ca != NULL; t_ca = t_ca->next)
    {
      if (!newcluster || t_ca->clusterid == newcluster)
        AddItemTo (clusterMembers, t_ca->clusterrow);
    }
}

void
deleteFromMenu (struct clusterapps *cluster)
{
  char *tmpString;
  char *location;

  tmpString = fixSlashes (cluster->clusterrow);
  location = (char *) malloc (strlen (tmpString) + 10);
  sprintf (location, "/Members/%s", tmpString);
  DeleteItemFrom (clusterMembers, location);
}
