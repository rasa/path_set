# path_set 

Modify system and user environment variables

## Usage

````
path_set [options] path [path2 ...]

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
````

## Examples

````
  rem append c:\bin to the system Path variable:
  path_set -n c:\bin

  rem prepend c:\usr\local\bin and c:\bin to the system Path:
  path_set -n -p c:\usr\local\bin c:\bin 

  rem Add "C:\Program Files\Java\bin" to the system Path:
  path_set -n "C:\Program Files\Java\bin"
````

or, even better:

````
  rem add or replace JAVA_HOME with %ProgramFiles%\Java
  path_set -n -r -x -v JAVA_HOME `ProgramFiles`\Java
  
  rem Append %JAVA_HOME%\bin to the system Path:
  path_set -n `JAVA_HOME`\bin
````

## Contributing

To contribute to this project, please see [CONTRIBUTING.md](CONTRIBUTING.md).

## Bugs

To view existing bugs, or report a new bug, please see the [issues](/issues) page for this project.

## License

This project is [MIT licensed](LICENSE).

## Changelog

Please see [CHANGELOG.md](CHANGELOG.md) for the version history for this project.

## Contact

This project was originally developed by [Ross Smith II](mailto:ross@smithii.com).
Any enhancements and suggestions are welcome.
