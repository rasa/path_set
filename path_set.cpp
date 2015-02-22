// Copyright (c) 2005-2015 Ross Smith II. See Mit LICENSE in /LICENSE

/*
TODO:

add -d | --delete option, including wildcard:

path_set -d "c:\j2sdk*"

change -d | --default to -f | --default

if the specified path already exists in the path, and they specify --move then it will
	be deleted from its current location and either appended, or prepended
treat repeating \'s as \ in comparing paths
ignore trailing \'s and spaces in comparing paths
change REG type if specified type is different

*/

#ifdef _MSC_VER
#pragma warning(disable:4996)
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "user32.lib")
#endif

#ifndef WIN32_LEAN_AND_MEAN
# define WIN32_LEAN_AND_MEAN 1
#endif

#define _WIN32_WINNT 0x501

#include <windows.h>
#include <stdio.h>
#include <cstdlib>
//#include <atlbase.h> // required for Stackwalker

#include "Stackwalker.h"
#include "Optimize.h"
#include "debug.h"
#include "UpdatePathVariable.h"
#include "getopt.h"

#include "version.h"

#define APPNAME			VER_INTERNAL_NAME
#define APPVERSION		VER_STRING2
#define APPCOPYRIGHT	VER_LEGAL_COPYRIGHT

// #define ESCAPE_CHAR '`'
#define ESCAPE_STRING "`"

static char *short_options = "v:sude:nprxzV?";

static struct option long_options[] = {
	{"variable",		required_argument,	0, 'v'},
	{"var",				required_argument,	0, 'v'},
	{"v",				required_argument,	0, 'v'},
	{"system",			no_argument,		0, 's'},
	{"s",				no_argument,		0, 's'},
	{"user",			no_argument,		0, 'u'},
	{"u",				no_argument,		0, 'u'},
	{"default",			no_argument,		0, 'd'},
	{"d",				no_argument,		0, 'd'},
	{"percent",			required_argument,	0, 'e'},
	{"e",				required_argument,	0, 'e'},
	{"no-dups",			no_argument,		0, 'n'},
	{"nodups",			no_argument,		0, 'n'},
	{"no_dups",			no_argument,		0, 'n'},
	{"n",				no_argument,		0, 'n'},
	{"prepend",			no_argument,		0, 'p'},
	{"p",				no_argument,		0, 'p'},
	{"replace",			no_argument,		0, 'r'},
	{"r",				no_argument,		0, 'r'},
	{"reg-expand-sz",	no_argument,		0, 'x'},
	{"reg_expand_sz",	no_argument,		0, 'x'},
	{"expand-sz",		no_argument,		0, 'x'},
	{"expand_sz",		no_argument,		0, 'x'},
	{"expand",			no_argument,		0, 'x'},
	{"x",				no_argument,		0, 'x'},
	{"reg-sz",			no_argument,		0, 'z'},
	{"reg_sz",			no_argument,		0, 'z'},
	{"sz",				no_argument,		0, 'z'},
	{"z",				no_argument,		0, 'z'},
	{"version",			no_argument,		0, 'V'},
	{"V",				no_argument,		0, 'V'},
	{"help",			no_argument,		0, '?'},
	{"h",				no_argument,		0, '?'},
	{"?",				no_argument,		0, '?'},
	{NULL,				0,					0, 0}
};

void usage() {
	printf(
		"Usage: " APPNAME " [options] path [path2 ...]\n\n"
		"Options:\n"
//2345678901234567890123456789012345678901234567890123456789012345678901234567890
"-v | --var var   Append path(s) to environmental variable 'var' (default: Path)\n"
"-s | --system    Modify variable in the system environment (default)\n"
"-u | --user      Modify variable in the current user's environment\n"
"-d | --default   Modify variable in the default user environment\n"
"-e | --percent c Change %% substitution character to 'c' (default is " ESCAPE_STRING ")\n"
"-n | --no-dups   Don't add path if the variable already contains it\n"
"-p | --prepend   Prepend path(s) to variable\n"
"-r | --replace   Replace the value (default is to append)\n"
"-x | --expand-sz Use REG_EXPAND_SZ type (default if " ESCAPE_STRING " char is used)\n"
"-z | --sz        Use REG_SZ type (default)\n"
"-V | --version   Show version and copyright information and quit\n"
"-? | --help      Show this help message and quit\n"

		"\nExamples:\n"
		"  " APPNAME " -n c:\\bin\n"
		"  " APPNAME " -n \"C:\\Program Files\\Java\\bin\"\n"
		"or, even better:\n"
		"  " APPNAME " -n -r -x -v JAVA_HOME " ESCAPE_STRING "ProgramFiles" ESCAPE_STRING "\\Java\n"
		"  " APPNAME " -n " ESCAPE_STRING "JAVA_HOME" ESCAPE_STRING "\\bin\n"
	);
}

int main(int argc, char **argv)
{
#ifdef _DEBUG_ALLOC
    InitAllocCheck();
#endif

	if (argc < 2) {
		usage();
		exit(1);
	}

	int prepend = 0;
	int user = 0;
	int expand = 0;
	int dont_duplicate = 0;
	int replace = 0;

	opterr = 0;

	char *szVarName = "Path";
	char *percent_char = ESCAPE_STRING;

	while (1) {
		int c;
		int option_index = 0;

		if (optind < argc && argv[optind] && argv[optind][0] == '/')
			argv[optind][0] = '-';

		c = getopt_long(argc, argv, short_options, long_options, &option_index);

		if (opterr) {
			usage();
			exit(1);
		}

		if (c == -1)
			break;

        switch (c) {
            case 'V':
				printf("%s - Version %s - %s\n", APPNAME, APPVERSION, __DATE__);
				printf(APPCOPYRIGHT "\n\n");

				printf(
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n");

				exit(0);
                break;
            case 'd':
				user = 2;
                break;
            case 'e':
				percent_char[0] = (char) optarg[0];
                break;
			case 'n':
				dont_duplicate = 1;
				break;
            case 'p':
				prepend = 1;
                break;
            case 'r':
				replace = 1;
                break;
            case 's':
            case 'm':
				user = 0;
                break;
            case 'u':
				user = 1;
                break;
            case 'v':
				szVarName = (char*) optarg;
                break;
            case 'x':
				expand = 1;
                break;
            case 'z':
				expand = 0;
                break;
			case '?':
				usage();
				exit(0);
			case ':':
				fprintf(stderr, "Option -%c requires an operand\n", optopt);
				// fallthrough
			default:
				usage();
				exit(1);
        }
    }

	int rv = 0;
	int found_percent_char = 0;

	for (; optind < argc; ++optind)
	{
		char *arg = argv[optind];
		char *p = arg;
		unsigned int len = strlen(arg);

		while (len-- > 0)
			if (arg[len] == percent_char[0]) {
				found_percent_char = 1;
				arg[len] = '%';
			}

		rv |= UpdatePathVariable(szVarName, arg, user, prepend, expand || found_percent_char, dont_duplicate, replace);
	}

	exit(rv);
	return rv;
}
