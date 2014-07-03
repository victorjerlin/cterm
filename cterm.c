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
 * $Id: cterm.c,v 1.5 2007-02-14 16:29:32 victor Exp $
 */

/*
** This is proprietary source-code belonging to Victor Jerlin.
** You have no right reading/using/distributing this code without
** the authors written consent.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>

#include <gtk/gtk.h>
#include <X11/Xlib.h>
#include <X11/X.h>
#include <X11/Xutil.h>

#include <X11/keysymdef.h>

#include <X11/cursorfont.h>
#include <X11/Xmu/WinUtil.h>

#define __CTERM_C

#include "cterm.h"
#include "cluster.h"
#include "menu.h"
#include "window.h"
#include "misc.h"
#include "errorhandler.h"

gint
sendtextbox (GtkWidget * textentry, gpointer gdata)
{
  XKeyEvent myevent;
  char *thetext;
  char temp[] = { 0, 0 };

  thetext = (gchar *) gtk_entry_get_text (GTK_ENTRY (textentry));


  for (; *thetext; thetext++)
    {
      myevent.display = display;
      myevent.type = KeyPress;
      myevent.root = rootWindow;
      myevent.subwindow = None;
      myevent.time = CurrentTime;
      myevent.state = 0;
      myevent.x = 1;
      myevent.y = 1;
      myevent.x_root = 1;
      myevent.y_root = 1;
      myevent.same_screen = TRUE;

      temp[0] = *thetext;
      myevent.keycode =
	XKeysymToKeycode (display, XStringToKeysym ((char *) &temp));

      myevent.type = KeyPress;
      sendToCluster (KeyPressMask, (XEvent *) & myevent);
//      myevent.type = KeyRelease;
//      sendToCluster (KeyPressMask, (XEvent *)&myevent);
    }

  gtk_entry_set_text (GTK_ENTRY (textentry), "");
  return 0;
}

gint
callback_keybinds (GtkWidget * widget, GdkEvent * event,
		   gpointer callback_data)
{
  XKeyEvent myevent;
  GdkEventType *GET = (GdkEventType *) & event->type;
  GdkEventKey *GEK;

  if (*GET == GDK_KEY_PRESS)
    myevent.type = KeyPress;
  else if (*GET == GDK_KEY_PRESS)
    myevent.type = KeyRelease;
  else
    {
      g_message ("not keypress!\n");
      return 1;
    }

  GEK = (GdkEventKey *) event;

  myevent.type = KeyPress;
  myevent.window = rootWindow;
  myevent.subwindow = rootWindow;
  myevent.state = GEK->state;
  myevent.keycode = XKeysymToKeycode (display, GEK->keyval);

  sendToCluster (KeyPressMask, (XEvent *) & myevent);

  return 1;
}

int
main (int argc, char **argv)
{
  GtkWidget *main_vbox;
  GtkWidget *menubar;
//  GtkWidget *textentry;
  GtkWidget *instantentry;

  display = XOpenDisplay (getenv("DISPLAY"));
  if (!display)
    {
      fprintf (stderr, "%s: cant connect to display \"%s\"\n", PROJNAME,
	       getenv("DISPLAY"));
      return (0);
    }

  if (argc > 1 && !strcmp(argv[1], "-v")) // ugly but don't have time to implement getopt() for one argument
    verbose = 1;


  defaultScreen = DefaultScreen (display);
  screenWidth = DisplayWidth (display, defaultScreen);
  screenHeight = DisplayHeight (display, defaultScreen);
  rootWindow = RootWindow (display, defaultScreen);

  if (verbose)
    fprintf (stderr, "Screen %d: Has resolution %dx%d.\n", defaultScreen,
	     screenWidth, screenHeight);

  if (verbose)
    fprintf (stderr, "Fully initiated..\n");

  gtk_init (&argc, &argv);

  /* there's a better way of solving this!! */
  setupErrorHandler ();

  gtkRootWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_signal_connect (G_OBJECT (gtkRootWindow), "destroy",
		    G_CALLBACK (gtk_main_quit), NULL);

  gtk_window_set_title (GTK_WINDOW (gtkRootWindow), "C-TERM");

  main_vbox = gtk_vbox_new (FALSE, 1);
  gtk_container_set_border_width (GTK_CONTAINER (main_vbox), 1);
  gtk_container_add (GTK_CONTAINER (gtkRootWindow), main_vbox);

  menubar = createMenubar (gtkRootWindow);
  gtk_box_pack_start (GTK_BOX (main_vbox), menubar, FALSE, TRUE, 0);

// XXX This was pretty ugly
//  textentry = gtk_entry_new ();
//  g_signal_connect (GTK_ENTRY (textentry), "activate",
//		    GTK_SIGNAL_FUNC (sendtextbox), NULL);
//  gtk_box_pack_start (GTK_BOX (main_vbox), textentry, FALSE, TRUE, 0);
  instantentry = gtk_entry_new ();
  g_signal_connect (GTK_ENTRY (instantentry), "key_press_event",
		    GTK_SIGNAL_FUNC (callback_keybinds), NULL);
  /*
   * g_signal_connect (GTK_ENTRY(instantentry), "key_release_event", GTK_SIGNAL_FUNC(callback_keybinds), NULL);
   */

  gtk_box_pack_start (GTK_BOX (main_vbox), instantentry, FALSE, TRUE, 0);
  gtk_widget_show_all (gtkRootWindow);

  clusterMembers =
    gtk_item_factory_get_widget (GTK_ITEM_FACTORY (itemFactory), "/Members");
  if (clusterMembers == NULL)
    {
      g_message ("cant find the members-menu\n");
      return (0);
    }

  gtk_main ();

  XCloseDisplay (display);
  return (1);
}
