path_set 1.3 - Jul 07 2006
Copyright (c) 2005-2006 Ross Smith II (http://smithii.com) All Rights Reserved

------------------------------------------------------------------------------

Usage: path_set [options] path [path2 ...]
Options:
-v VarName Append path(s) to environmental variable VarName (default is Path)
-s         Modify variable in the system environment (default)
-u         Modify variable in the current user's environment
-d         Modify variable in the default user environment
-e char    Change % substitution character to 'char' (default is `)
-n         Don't add path if the variable already contains it
-p         Prepend path(s) to variable
-r         Replace the value (default is to append)
-x         Use REG_EXPAND_SZ type (default if ` char is used)
-z         Use REG_SZ type (default)
-c         Show version and copyright statement
-?         Show this help screen

Examples:
  rem append c:\bin to the system Path variable:
  path_set -n c:\bin

  rem prepend c:\usr\local\bin and c:\bin to the system Path:
  path_set -n -p c:\usr\local\bin c:\bin 

  rem Add "C:\Program Files\Java\bin" to the system Path:
  path_set -n "C:\Program Files\Java\bin"

or, even better:

  rem add or replace JAVA_HOME with %ProgramFiles%\Java
  path_set -n -r -x -v JAVA_HOME `ProgramFiles`\Java
  
  rem Append %JAVA_HOME%\bin to the system Path:
  path_set -n `JAVA_HOME`\bin

------------------------------------------------------------------------------

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

$Id$
