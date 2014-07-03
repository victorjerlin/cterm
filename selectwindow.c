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
 * $Id: selectwindow.c,v 1.2 2006-06-26 09:52:56 victor Exp $
 */

#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/X.h>

#include <X11/cursorfont.h>
#include <gtk/gtk.h>

#include "cterm.h"

Window
selectWindow (Display * dpy, int screen)
{       
  int status, buttons = 0;
  Cursor cursor;
  XEvent mouseEvent;
  Window targetWindow = None;


  cursor = XCreateFontCursor (dpy, XC_crosshair);
  status = XGrabPointer (dpy, rootWindow, False,
                         ButtonPressMask | ButtonReleaseMask, GrabModeSync,
                         GrabModeAsync, rootWindow, cursor, CurrentTime);

  if (status != GrabSuccess)
    {
      fprintf (stderr, "Error grabbing mouse.\n");
      return (0);
    }

  while (targetWindow == None || buttons != 0)
    {
      XAllowEvents (dpy, SyncPointer, CurrentTime);
      XWindowEvent (dpy, rootWindow, ButtonPressMask | ButtonReleaseMask,
                    &mouseEvent);

      switch (mouseEvent.type)
        {
        case ButtonPress:
          if (targetWindow == None)
            {
              targetWindow = mouseEvent.xbutton.subwindow;
              if (targetWindow == None)
                targetWindow = rootWindow;
            }
          buttons++;
          break;

        case ButtonRelease:
          if (buttons >= 1)
            buttons--;
          break;

        default:
          break;
        }
    }

  XUngrabPointer (dpy, CurrentTime);

  return (targetWindow);
}

