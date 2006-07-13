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

/*
todo WM_SETTINGCHANGE isn't working right, research
*/

#define _WIN32_WINNT 0x501

#ifndef WIN32_LEAN_AND_MEAN
# define WIN32_LEAN_AND_MEAN 1
#endif

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "UpdatePathVariable.h"
#include "debug.h"
#include "SystemMessage.h"

#define MAX_VALUE_LEN  32767

#define ENVREGKEY       "System\\CurrentControlSet\\Control\\Session Manager\\Environment"
#define USERENVREGKEY   "Environment"
#define DEFAULTUSERENVREGKEY ".DEFAULT\\Environment"

#define BROADCAST_TIMEOUT (5000)

void warn(char *message) {
	fprintf(stderr, message);
}

int UpdatePathVariable(char *szVarName, char *szPath, int iUser, int iPrepend, int iExpand, int dont_duplicate, int replace)
{
    HKEY hKey = NULL;
    char *szNewPath = NULL;
    char *szExpandedPath = NULL;
	DWORD rv = (DWORD) -1;

	D(("UpdatePathVariable() start"));
		
	for (;;)
	{
		char szVarValue[MAX_VALUE_LEN];
		DWORD dwPathLen = 0;
		DWORD dwLen = 0;
		DWORD dwType;
		DWORD dwNewLen = 0;

		dwPathLen = strlen(szPath);

		switch (iUser) {
			case 0:
				rv = RegOpenKeyEx(HKEY_LOCAL_MACHINE, ENVREGKEY, 0, KEY_READ | KEY_WRITE | KEY_QUERY_VALUE, &hKey);
				break;
			case 1:
				rv = RegOpenKeyEx(HKEY_CURRENT_USER, USERENVREGKEY, 0, KEY_READ | KEY_WRITE | KEY_QUERY_VALUE, &hKey);
				break;
			case 2:
				rv = RegOpenKeyEx(HKEY_USERS, DEFAULTUSERENVREGKEY, 0, KEY_READ | KEY_WRITE | KEY_QUERY_VALUE, &hKey);
				break;
		}
		if (rv != ERROR_SUCCESS)
		{
			warn(SystemMessage(rv));
			break;
		}

		dwLen = MAX_VALUE_LEN;
		dwType = REG_SZ;
		strcpy(szVarValue, "");
		rv = RegQueryValueEx(hKey, szVarName, NULL, &dwType, (LPBYTE) szVarValue, &dwLen);
		if (rv != ERROR_SUCCESS && rv != ERROR_FILE_NOT_FOUND) {
			dwType = REG_EXPAND_SZ;
			warn(SystemMessage(rv));
			break;
		}

		if (rv == ERROR_FILE_NOT_FOUND) {
			dwLen = 0;
			dwType = iExpand ? REG_EXPAND_SZ : REG_SZ;
		}

		if (dont_duplicate && dwLen) {
			rv = !ERROR_SUCCESS;
			size_t len = strlen(szPath);
			char *p = szVarValue;

			while (p) {
				if (_strnicmp(p, szPath, len) == 0) {
					char *p2 = p + len;
					if (*p2 == ';' || *p2 == '\0') {
						rv = ERROR_SUCCESS;
						break;
					}
				}
				p = strchr(p, ';');
				if (p)
					++p;
			}
			if (rv == ERROR_SUCCESS)
				break;
			rv = ERROR_SUCCESS;
		}

		dwNewLen = dwPathLen + dwLen + 4;
		D(("dwNewLen=%d", dwNewLen));

		szNewPath = (char *) malloc(dwNewLen + 4);
		if (szNewPath == NULL)
		{
			rv = GetLastError();
			warn(SystemMessage(rv));
		    break;
		}

		strcpy(szNewPath, "");

		if (!replace && !iPrepend && dwLen)
		{
			strcpy(szNewPath, szVarValue);
			strcat(szNewPath, ";");
		}

		D(("szNewPath=%s", szNewPath));

		strcat(szNewPath, szPath);

		D(("szNewPath=%s", szNewPath));

		if (!replace && iPrepend && dwLen)
		{
			strcat(szNewPath, ";");
			strcat(szNewPath, szVarValue);
		}

		D(("szNewPath=%s", szNewPath));

		szExpandedPath = (char *) malloc(32767);
		if (szExpandedPath == NULL)
		{
			rv = GetLastError();
			warn(SystemMessage(rv));
			break;
		}

		if (!ExpandEnvironmentStrings(szNewPath, szExpandedPath, 32767)) {
			rv = GetLastError();
			warn(SystemMessage(rv));
			break;
		}

		// todo only update path if running in PE
		if (dwType == REG_EXPAND_SZ)
		{
			rv = RegSetValueEx(hKey, szVarName, 0, dwType, (LPBYTE) szNewPath, strlen(szNewPath) * sizeof(char));
		} else {
			rv = RegSetValueEx(hKey, szVarName, 0, dwType, (LPBYTE) szExpandedPath, strlen(szExpandedPath) * sizeof(char));
		}

		if (rv != ERROR_SUCCESS)
		{
			warn(SystemMessage(rv));
			break;
		}

		if (!SetEnvironmentVariable(szVarName, szExpandedPath))
		{
			rv = GetLastError();
			warn(SystemMessage(rv));
			break;
		}

		static DWORD dummy;
		if (!SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM) "Environment", SMTO_ABORTIFHUNG, BROADCAST_TIMEOUT, &dummy))
		{
			rv = GetLastError();
			warn(SystemMessage(rv));
			break;
		}

		rv = ERROR_SUCCESS;
		break;
	}

	if (hKey)
		RegCloseKey(hKey);

	if (szNewPath)
   		free(szNewPath);
	
	if (szExpandedPath)
   		free(szExpandedPath);

	D(("UpdatePathVariable() returning %d", rv));

    return rv;
}
