# path_set [![Flattr this][flatter_png]][flatter]

Modify system and user environment variables.

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

````batch
  rem append c:\bin to the system Path variable:
  path_set -n c:\bin

  rem prepend c:\usr\local\bin and c:\bin to the system Path:
  path_set -n -p c:\usr\local\bin c:\bin

  rem Add "C:\Program Files\Java\bin" to the system Path:
  path_set -n "C:\Program Files\Java\bin"
````

or, even better:

````batch
  rem add or replace JAVA_HOME with %ProgramFiles%\Java
  path_set -n -r -x -v JAVA_HOME `ProgramFiles`\Java

  rem Append %JAVA_HOME%\bin to the system Path:
  path_set -n `JAVA_HOME`\bin
````

## Contributing

To contribute to this project, please see [CONTRIBUTING.md](CONTRIBUTING.md).

## Bugs

To view existing bugs, or report a new bug, please see [issues](../../issues).

## Changelog

To view the version history for this project, please see [CHANGELOG.md](CHANGELOG.md).

## License

This project is [MIT licensed](LICENSE).

## Contact

This project was created and is maintained by [Ross Smith II][] [![endorse][endorse_png]][endorse]

Feedback, suggestions, and enhancements are welcome.

[Ross Smith II]: mailto:ross@smithii.com "ross@smithii.com"
[flatter]: https://flattr.com/submit/auto?user_id=rasa&url=https%3A%2F%2Fgithub.com%2Frasa%2Fpath_set
[flatter_png]: http://button.flattr.com/flattr-badge-large.png "Flattr this"
[endorse]: https://coderwall.com/rasa
[endorse_png]: https://api.coderwall.com/rasa/endorsecount.png "endorse"

