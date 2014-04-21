nadavlv
Nadav Luzzato 301600185

DESCRIPTION:
--------------------------------------------------------------
The program simulates a shell, it support system function calls
using execvp() to execute them and fork() to spawn child processes to avoid the new process from taking over the parent process space, the shell functions as a normal shell.

The prompt is as follows:
[return code from previous function call] [username]@[hostname]$ 

Correct usage: 
0 user@hostname$ [function_name] [arguments]
arguments are expected to be seperated by a space char.

The shell also support output redirection, in order to redirect the output of a function call into a file.

Correct output redirection usage: 
0 user@hostname$ [function_name] [arguments] > [filename]

COMPILIATION:
--------------------------------------------------------------
In order to compile the program, simply run 'make' in order to use the makefile.

RUNNING:
--------------------------------------------------------------
After compiling the program using the 'make' command - type in the terminal './cshell'

PROGRAM FILES:
--------------------------------------------------------------
iomanip.c/iomanip.h - contains string manipulation functions.

prompt.c/prompt.h - contains the functions used to craft our formatted prompt string.

syscall.c/syscall.h - contains the functions used to execute a system called, split into two
					  cases, either the command will print to stdout (execute()), or the 
					  command will print to a file (execute_to_file()).

main.c - entry point of the program.

REQUIRED INPUT
--------------------------------------------------------------
Any input is acceptable.
In case of unrecognized function call, the return code is 255 and the expected output is:
"[function name]: command not found."
In order to terminate the program, an "exit" command is expected.

OUTPUT EXPLANATION
--------------------------------------------------------------
When directing output to a file, if for some reason the file creation has failed, or the output redirection has failed, a proper error will be printed out and the return code will be 254.

In case of fuction call failure, the return code will be 255, and the message "[functionname]: command was not found".

In any other case, the output will be printed to either stdout or the file we chooses, and the return code will change according to that function return code.

Successful call return code is usually 0.

