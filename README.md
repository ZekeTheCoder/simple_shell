## Simple_Shell

### Simple UNIX command line interpreter.

### Requirements
#### General
* Editors: vi, vim, emacs.
* All files compiled on Ubuntu 20.04 LTS using gcc, using the options `-Wall -Werror -Wextra -pedantic -std=gnu89`
* All files end with a new line.
* Code use the Betty style. Checked using betty-style.pl and betty-doc.pl.
* Shell does not have any memory leaks.
* No more than 5 functions per file.
* All header files are include guarded.
* System calls used only when you needed.
* A README with the description of your project exist at the root of the folder of the project.
* An AUTHORS file at the root of your repository exist, listing all individuals having contributed content to the repository.

### More Info
#### Output
- Program has the exact same output as sh (/bin/sh) as well as the exact same error output.
- The only difference is when you print an error, the name of the program must be equivalent to your argv[0] (See below)
Example of error with sh:
```
$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
$
```
Same error with your program hsh:
```
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
$
```
#### compilation
```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```
#### Testing
Our simple shell works like this in interactive mode:
```
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```
But also in non-interactive mode:
```
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```
### Tasks
0. Betty would be proud
* Our beautiful code passes the Betty checks
* Run `betty *` to verify

1. Simple shell 0.1
*UNIX command line interpreter.

Our Shell:
* Displays a prompt and wait for the user to type a command.
* A command line always ends with a new line.
* The prompt is displayed again each time a command has been executed.
* If an executable cannot be found, print an error message and display the prompt again.
* Handles errors.
* You have to handle the “end of file” condition (`Ctrl+D`).

2. Simple shell 0.2
- Simple shell 0.1 +
* Handles command lines with arguments

3. Simple shell 0.3
- Simple shell 0.2 +

* Handles the PATH
* fork is not be called if the command doesn’t exist

4. Simple shell 0.4
- Simple shell 0.3 +

* Implements the exit built-in, that exits the shell

5. Simple shell 1.0
- Simple shell 0.4 +

* Implements the env built-in, that prints the current environment
