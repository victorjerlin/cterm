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
 * $Id: about.c,v 1.3 2007-02-14 16:29:32 victor Exp $
 */

#include <X11/X.h>
#include <X11/Xlib.h>
#include <gtk/gtk.h>
#include <stdio.h>

#define __ABOUT_C
#include "cterm.h"

GtkWidget*
create_aboutdialog (void)
{
  GtkWidget *aboutdialog1;

  aboutdialog1 = gtk_about_dialog_new ();
  gtk_about_dialog_set_version (GTK_ABOUT_DIALOG (aboutdialog1), VERSION);
  gtk_about_dialog_set_name (GTK_ABOUT_DIALOG (aboutdialog1), "C-TERM");
  gtk_about_dialog_set_copyright (GTK_ABOUT_DIALOG (aboutdialog1), "Copyright 2006-2007 " AUTHOR);
  gtk_about_dialog_set_license (GTK_ABOUT_DIALOG (aboutdialog1), 
"Copyright (C) 2006-2007 Victor Jerlin <victor@pseudocode.se>\n" \
"+356 9999 0125, +4673 624 7815\n" \
"Flat 18, 5 Alhambra Court, Tower Road, Sliema, SLM15, Malta\n" \
"\n" \
"This program is free software; you can redistribute it and/or\n" \
"modify it under the terms of the GNU General Public License\n" \
"as published by the Free Software Foundation; either version 2\n" \
"of the License, or (at your option) any later version.\n" \
"\n" \
"This program is distributed in the hope that it will be useful,\n" \
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n" \
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n" \
"GNU General Public License for more details.\n" \
"\n" \
"You should have received a copy of the GNU General Public License\n" \
"along with this program; if not, write to the Free Software\n" \
"Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,\n" \
"MA 02110-1301, USA.\n");
  gtk_about_dialog_set_website (GTK_ABOUT_DIALOG (aboutdialog1), "http://www.pseudocode.se/");
  g_signal_connect (G_OBJECT (aboutdialog1),
                    "response",
                    G_CALLBACK (gtk_widget_hide),
                    NULL);

  return aboutdialog1;
}

void
showabout (void)
{
  GtkWidget *aboutWidget;
  aboutWidget = create_aboutdialog ();
  gtk_widget_show (aboutWidget);
}
