# MINISHELL

## Shortcuts for inserting special characters

| action  | shortcut       |
|:-------:|:--------------:|
| \t      | ctrl+v, tab    |
| \n      | ctrl+v, ctrl+j |
| \r      | ctr+v, ctrl+m  |
| enter   | ctrl+m         |

## Requirements
* Minishell will need to handle multiple heredocs
* Minishell will need to handle files/scripts without a #!
* Minishell will need to update prompt based on single or multi quote, heredoc, |, ||, &&, if/for, [], \ and others?
* Minishell will need to pipe n amount of commands
* Minishell will need to display output of heredoc even when no command is specified.
* Minishell will need to process heredoc first before giving it to a command.
* Minishell will need to keep track of any added variables.
* Minishell will need to add variables to env when export is used.
* Minishell will need to search and return the PATH to the binary for executing the command.

## Objectives
* Display prompt when waiting
* History of commands
* Search and launch executables (PATH variable, relative, absolute path)
* ONE global variable for signals (signo)
* Support \ special characters and quotes
* Single quotes for preventing the shell to interpert the meta characters
* Double quotes for preventing the shell to interpert the meta characters (exception is $)
* Redirection (< input, > output , << read until line with delimiter found (no history?), >> redirect/append to)
* Pipes | (output of each is connected to the in of the next command)
* Environment variables ($<name>) expand to their values
* $? exapnd to the exit status of the most recently executed foreground pipeline
* ctrl-C, ctr-D, and ctrl-\ behave like bash (when a command is running)
* Interactive mode (waiting for a prompt/ and it is not run as a command itself):
	* ctrl-C: display new prompt
	* ctrl-D: exits the shell (EOF signal)
	* ctrl-\: does nothing
* Implement builtins: echo [-n], cd [rel,abs], pwd [args], export [args], uset [args], env , exit [args]
* readline() can cause memory leaks, which doesn't have to be fixed. (alternatives?)
* What are bashes special characters/variables? (~, *) [bash - special char](https://mywiki.wooledge.org/BashGuide/SpecialCharacters)
* & start the command before it as a background process.
* Accept command line arguments for running in interactive and non-interactive mode.

## How to convert a prompt into an action

Search terms:
* Lexical Analysis/ Tokenization / lexing
* Parser
* Interperter

> Lexical Analysis is the first phase of a compiler that takes the input as a source code written in a high-level language. The purpose of lexical analysis is that it aims to read the input code and break it down into meaningful elements called **tokens**. Those tokens are turned into building blocks for other phases of compilation.

Lexical Analysis is also known as a scanner. It breaks down the input into smaller parts called tokens. Tokens represent words (commands?), symbols, keywords, variables, numbers or punctuation.

> The output generated from Lexical Analysis are a sequence of tokens sent to the parser for syntax analysis.

Way to implement a Lexical Analyisis: [Deterministic Finite Automata](https://www.geeksforgeeks.org/introduction-of-finite-automata/).

Types Tokens:
* Identifiers
* Operators
* Constants
* Keywords
* Literals
* Punctuators
* Special Characters

Two phases, Scanning and Analyzing.

Sources:
1. [Introduction of Lexical Analysis](https://www.geeksforgeeks.org/introduction-of-lexical-analysis/)
2. [Introduction to Lexical Analyzer](https://www.youtube.com/watch?v=4nx8LEGy9kI)

## Construction

Build the shell in stages.

Stage one:
1. Display prompt and history.
2. Simple parser, just split the input into sections (spaces/tabs/newlines?) and the first word will be assumed as the command. (ignore comments)
3. Search and find for command based on PATH.
4. **cd**, **pwd** and **echo** implemented.
5. Catch signals for interactive mode.
6. Run in both interactive and non-interactive mode.
6. Proper clean up and test cases.

Stage two:
1. Extending the Lexical (handle pipes)


The biggest and most time consuming will be the Lexical Analysis, Tokenizer, and parser. 
Second biggest will be implementing the different features like the |, || , and &&.


### BONUS
&& and || with parenthesis for priorities.
|| double pipe is the operation of executing the left command and if it fails have it execute the right command (like an OR)
|| Only execute the command if the left command fails

**Example:**
```bash
cat file-not-found || echo 'I will execute!'
cat file-exist || echo 'I will not execute!'
```

&& follows up the command left if it successfully ran otherwise don't

Wildcards * should work for the current working directory

## Notes

getenv(char *), stdlib, get enviroment variable

> POSIX.1 does not allow this three-argument form, so to be portable it is best to write main to take two arguments, and use the value of environ. [link](https://www.gnu.org/software/libc/manual/html_node/Program-Arguments.html)

Use the extern instead
```c
extern char** environ;
```

environment variables will be send along with execve because certain commands rely on it.

execve replaces the calling process with a new program, with newly init, stack, heap and (init uninit) data segments. BUT it retains the Process ID of the fork. Signal handlers are resetted.

argv is the same as the main argv (by convention the argv[0] should be the filename/command)

> **execve()** does not return on success, and the text, initialized
data, uninitialized data (bss), and stack of the calling process
are overwritten according to the contents of the newly loaded
program. [link](https://man7.org/linux/man-pages/man2/execve.2.html)
for the path to the command we will need to check if it starts with ./ (current dir) or without. 
If without find command in the PATH variable.

> *pathname* must be either a binary executable, or a script starting
> 
>	with a line of the form:
> ``` sh 
> #!interpreter [optional-arg]
> ```

## Minishell

For the interactive terminal executing a command:
1. Execute command/script/file if it using a relative or absolute path. (check access)
2. Find the command within the builtins (echo, etc);
3. Find the command by searching through the directories listed in PATH.

When running a shell scripts (`./some_script.sh`) we need to read the first line for the shebang and arguments, which tells us what interperter needs to be used, and use that to execute our shell script in.

> When a text file with a shebang is used as if it were an executable in a Unix-like operating system, the program loader mechanism parses the rest of the file's initial line as an interpreter directive. [wiki](https://en.wikipedia.org/wiki/Shebang_(Unix))

Shell script don't need to end on .sh.
A shell script without a shebang will default to an interpreter (bash?).

[shebang](https://medium.com/@jcroyoaun/a-deeper-view-into-the-shebang-for-linux-scripting-4a26395df49d)

> “The shebang line tells the operating system which interpreter to use to parse the remainder of a file or a script”
> 
> — Random quote found on Google

> Some typical shebang lines:
> 
> #!/bin/sh – Execute the file using the Bourne shell, or a compatible shell, assumed to be in the /bin directory
> #!/bin/bash – Execute the file using the Bash shell
> #!/usr/bin/pwsh – Execute the file using PowerShell
> #!/usr/bin/env python3 – Execute with a Python interpreter, using the env program search path to find it
> #!/bin/false – Do nothing, but return a non-zero exit status, indicating failure. > Used to prevent stand-alone execution of a script file intended for execution in a specific context, such as by the . command from sh/bash, source from csh/tcsh, or as a .profile, .cshrc, or .login file.
> 
> [wiki](https://en.wikipedia.org/wiki/Shebang_(Unix))

An interactive shell means that you can type in commands and get output back from those commands opposed to using the shell to run a script. Interactive shells also read in files like `.bashrc` and `.profile` during initialization, while a non-interative shell does not.

Running a shell script is done done within a non-interactive shell and runs the commands within the script and exits when finished.[link](https://unix.stackexchange.com/a/43389)

for the path to the command we will need to check if it starts with ./ (current dir) or without. If without find command in the PATH variable.

## readline
After readline process the string for quotes, empty lines etc.

rl_clear_history is to clear and free the history (this must be called at the end of our program minishell)

## heredoc

HereDoc (heredoc) is a section of code that acts as a separate file, it is a multiline string or file literal for sendng input streams to other commands and programs.

```sh
[COMMAND] <<[-] 'DELIMTER'
  Line 1
  Line 2
  ...
DELIMITER
```
**<<**			Redirection operator for forwarding a HereDoc tot he COMMAND
**-**			Tab suppression
**DELIMITER**	Possible delimiters **END**, **EOT**, **EOF**, or any multi char. Omit quotes on the first line to allow command and variable expansion.

HereDoc accepts the use of variables and reads them.

<< EOF starts heredoc for multi-inline text file
<<- EOF same as above but indentation at start is trimmed away

heredoc can expand variables and execute commands
putting the EOF into qoutes ignores the variables
Non-escaped $ variables will expand to the locally variables
Escaping $ variables will expand to the remote variables

[source - heredoc](https://phoenixnap.com/kb/bash-heredoc)

## termios

termios is a structure in C used for controlling terminal input/output behavior. It's part of the POSIX standard and provides a way to manipulate various aspects of terminal settings, such as input modes, output modes, control characters, and special signals. It’s commonly used for controlling terminal behavior in a more granular way compared to the default settings provided by the operating system. (ChatGPT - "What is termios in c?")

Steps for creating your own readline and getting a better understanding about termios: https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html

## need a subtitle

https://www.gnu.org/software/termutils/manual/termcap-1.3/html_chapter/termcap_2.html

## builtins

cd relies on HOME env variable if no args are given. (Does nothing if HOME is unset)

```sh
cd -
# same as above
cd "$OLDPWD" && pwd
```
