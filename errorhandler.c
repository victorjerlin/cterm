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
 * $Id: errorhandler.c,v 1.3 2007-02-14 16:29:32 victor Exp $
 */

#include <stdio.h>

#include <X11/Xlib.h>
#include <gtk/gtk.h>

#define __ERRORHANDLER_C

#include "cterm.h"
#include "cluster.h"
#include "errorhandler.h"

int            
handlerBadWindow (Display * dpy, XErrorEvent * errEvent)
{     
  if (verbose)
    fprintf (stderr, "Removing window id 0x%x from clusters\n",
             (unsigned int) errEvent->resourceid);
  deleteFromCluster (errEvent->resourceid, 1);
  return (0);
}

int
setupErrorHandler (void)
{ 
  oldErrorHandler = XSetErrorHandler (handlerBadWindow);
  return (0);
}
