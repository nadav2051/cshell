#ifndef iomanip_H
#define iomanip_H
#include <stdlib.h> // includes the memory allocation functionality
#include <string.h> // includes the string manipulation functionality (strlen/strcpy/strtok)

/* 	char_isin_string():
	scans an input string for a specific char - will only work if the string ends with terminating char.
	return value of 1 - char is in the input string.
	return value of 0 - char isn't in the input string.
*/
int char_isin_string(char* input, char ch); 

/*	compare_input_to_word():
	take an input string, and  word string, checks if the space-trunctuated (trunc spaces from the beginning
	and the end of the string) input equals to the word.
	return value of 1 - input equals to word.
	return value of 0 - input doesn't equal to word.
*/
int compare_input_to_word(char* input, char* word);


/* 	count_delimited_words():
	counts the words in a string delimited by a specific char.
	return value is the number of delimited words - used to determine the array size we will use
*/
int count_delimited_words(char* line, char delim);


/* 	input_to_token():
	uses the count_delimited_words() method to determine the array size we'll need,
	then splits the words into an array (seperated by the delim).
*/
char** input_to_token(char* token_string, char* delim);
#endif