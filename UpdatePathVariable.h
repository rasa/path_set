/*

$Id$

Copyright (c) 2005-2006 Ross Smith II (http://smithii.com). All rights reserved.

This program is free software; you can redistribute it and/or modify it
under the terms of version 2 of the GNU General Public License 
as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

*/

#ifndef UPDATEPATHVARIABLE_H
#define UPDATEPATHVARIABLE_H

extern int UpdatePathVariable(char *szVarName, char *szPath, int iUser, int iPrepend, int iExpand, int dont_duplicate, int replace);

#endif // UPDATEPATHVARIABLE_H
