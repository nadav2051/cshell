#ifndef prompt_H
#define prompt_H


#include <stdio.h> // Gives the functionality of sprintf()
#include <stdlib.h> // Gives the functionality of memory allocation
#include <string.h> // Gives the functionality of strlen()/strcpy()
#define MAX_HOSTNAME_LENGTH 255
#define MAX_USERNAME_LENGTH 255


/*	get_hostname():
	Uses unistd.h function "gethostname()", but instead of using constant length
	of array, it will make a new array with the minimal memory required and return it.
*/
char* get_hostname();

/*	get_username():
	Uses unistd.h function "getlogin_r()" that returns the username, but instead of using constant length
	of array, it will make a new array with the minimal memory required and return it.
*/
char* get_username();

/*	get_prompt_string(int):
	uses "get_hostname()" and "get_username()" and the passed int parameter to generate
	a prompt for the user in the form of "0 username@hostname:"
*/
char* get_prompt_string(int);

#endif