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
 * $Id: misc.c,v 1.2 2006-06-26 09:52:56 victor Exp $
 */

#include <stdlib.h>
#include <string.h>

#include "misc.h"

char *
fixSlashes (char *string)
{
  char *newString;
  int i, slashes = 0, s;

  for (i = 0; i < strlen (string); i++)
    if (string[i] == '/')
      slashes++;
   
  newString = malloc (sizeof (char) * (strlen (string) + slashes + 1));
  for (i = s = 0; s < strlen (string); i++, s++)
    {
      if (string[s] == '/')
        {
          newString[i++] = '\\';
        }
      newString[i] = string[s];
    }
  newString[i] = '\0';
  
  return (newString);
} 
