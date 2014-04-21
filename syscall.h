#ifndef syscall_H
#define syscall_H
#include "iomanip.h"
#include <fcntl.h> // Gives us the user permissions macro's
#include <stdio.h> // Gives us the fprintf() functionality
#define CALL_FAILURE 255
#define OUTPUT_REDIRECTION_FAILURE 254
#define OUTPUT_REDIRECTION_CHAR '>'
#define OUTPUT_REDIRECTION_STRING ">"
#define PREMISSIONS 0644

/* free_2d_array():
   recieves a 2d array and its size and free that memory that was allocated to it using malloc.
*/
void free_2d_array(char** arr, int size);


/* execute_to_file(): 
   this function will be called when execute() will recognize a '>' (output redirection operator)
   in its input, this functions breaks down the output to two using '>' as a token.
   the left side of the token is expected to be arguments, and the right side is expected to be
   a filename to write it to.
   if a file does not exist, it will create a new one with PREMISSIONS as its premissions, if the file
   does exist, it will append the output to that file.
   uses execvp() and fork() to make sure the child process does not take over the parent system space.
   if there was a problem with either the file creation(open()) or output redirection(dup2()),
   a fitting error message will be printed out to stderr and the return value will be 
   OUTPUT_REDIRECTION_FAILURE (254).
*/	
int execute_to_file(char* input);
	

/* execute():
   recieves a string, breaks it down to tokens using space as a delimiter, the first token is expected to be
   the correct system call, and the following tokens are expected to be its arguments, if one of the arguments is 
   idetified to be '>', the function wil recognize the need for output redirection and call execute_to_file().
   otherwise it will spawn a child process using fork() to execute the call, wait untill it done, and then
   return the value of the child process call to the calling function.
   in case of error with the fork() or the execvp() command, a fitting message will be printed and
   the return code will be CALL_FAILURE (255).
*/
int execute(char* argv);


#endif