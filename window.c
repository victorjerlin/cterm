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
 * $Id: window.c,v 1.3 2007-02-14 16:29:33 victor Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#define XK_LATIN1 1
#define XK_MISCELLANY 1

#include <X11/Xlib.h>
#include <X11/Xmu/WinUtil.h>

#define __WINDOW_C

#include "cterm.h"
#include "cluster.h"
#include "menu.h"
#include "selectwindow.h"
#include "window.h"

int
AddWindow (void)
{
  struct clusterapps *t_ca = malloc (sizeof (struct clusterapps));
  struct clusterapps *tmp_ca;
  char *windowName;
  char *infoLine = malloc (sizeof (char) * 256);

  t_ca->window = selectWindow (display, defaultScreen);
  t_ca->window = XmuClientWindow (display, t_ca->window);
  t_ca->clusterid = cluster;
  t_ca->next = NULL;

  windowName = getWindowName (t_ca->window);
  if (verbose)
    fprintf (stderr, "Adding window 0x%x (%s) to cluster '%d'.\n",
             (unsigned int) t_ca->window, windowName, t_ca->clusterid);
  snprintf (infoLine, 256, "0x%x - %s", (unsigned int) t_ca->window,
            windowName);
  t_ca->clusterrow = infoLine;
  free (windowName);

  if (windows == NULL)
    windows = t_ca;
  else
    {
      for (tmp_ca = windows; tmp_ca->next != NULL; tmp_ca = tmp_ca->next);
      tmp_ca->next = t_ca;
    }
  AddItemTo (clusterMembers, t_ca->clusterrow);

  return (0);
}

char *
getWindowName (Window theWindow)
{
  char *windowName = NULL;
  char **list = NULL;
  int count, ret, i;
  XTextProperty tp;

  if (!XGetWMName (display, theWindow, &tp))
    windowName = strdup ("unknown");
  else
    {
      ret = XmbTextPropertyToTextList (display, &tp, &list, &count);

      if ((ret == Success || ret > 0) && list != NULL)
        {
          for (i = 0; i < count; i++)
            windowName = strdup (list[i]);
          XFreeStringList (list);
        } else
          windowName = strdup ((char *) tp.value);
    }

  return (windowName);
}
