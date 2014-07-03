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
 * $Id: cluster.c,v 1.4 2007-02-14 16:29:32 victor Exp $
 */

#include <stdlib.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <gtk/gtk.h>

#define __CLUSTER_C
#include "cterm.h"
#include "cluster.h"
#include "menu.h"

void deleteFromMenu (struct clusterapps *cluster);

int
sendToCluster (long eventMask, XEvent * event)
{
  struct clusterapps *t_ca = windows;

  for (; t_ca != NULL; t_ca = t_ca->next)
    {
      if (t_ca->clusterid == cluster)
	{
	  event->xkey.window = t_ca->window;
          XSendEvent (display, t_ca->window, 0, eventMask, event);
	}
    }
  XSync (display, False);
  return (0);
}

int
deleteFromCluster (Window theWindow, int global)
{
  struct clusterapps *tmp_ca, *tmp_ca2;

  while (windows != NULL && windows->window == theWindow
         && (global == 1 || cluster == windows->clusterid))
    {
      tmp_ca = windows;
      windows = windows->next;
      deleteFromMenu (tmp_ca);
      free (tmp_ca);
    }

  if (windows == NULL)
    return (0);

  for (tmp_ca = windows; tmp_ca != NULL;
       tmp_ca2 = tmp_ca, tmp_ca = tmp_ca->next)
    {
      if (tmp_ca->window == theWindow
          && (global == 1 || cluster == windows->clusterid))
        {
          tmp_ca2->next = tmp_ca->next;
          deleteFromMenu (tmp_ca);
          free (tmp_ca->clusterrow);
          free (tmp_ca);
        }
    }

  return (0);
}

void
toCluster (gpointer callback_data, guint newCluster, GtkWidget * menu_item)
{
  if (GTK_CHECK_MENU_ITEM (menu_item)->active)
    {
      if (verbose)
        fprintf (stderr, "Changing from cluster '%d' to '%d'.\n", cluster,
                 newCluster);
      redrawClusterMenu (cluster, newCluster);
      cluster = newCluster;
    }
  return;
}
