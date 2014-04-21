#include "iomanip.h"

int char_isin_string(char* input, char ch) { 
	char* p = input;
	//If the string doesn't contain a terminating char -> core dumped!	
	while ((*p++) != '\0') 
		if(*p == ch)
			return 1;

		return 0;
	}

int compare_input_to_word(char* input, char* word) {
	char* token;
	char templine[strlen(input)+1];
	//copies the input into a temp char*, so we don't ruin our user input
	strcpy(templine,input);
	//uses strtok() to get explode the string delimited by spaces.
	//if after the first strtok use, we no longer have string to manipulate,
	//that means that string contained only one expression without spaces in the middle.
	//we compare that expression to word, if it's the same returns 1.
	token = (char*)strtok(templine," ");
	if ((strcmp(word,token) == 0) && (strtok(NULL," ") == NULL)) {
		return 1;
	}
	return 0;
}


int count_delimited_words(char* line, char delim) { //Count how many words exist while using delim
	int i = 0;										//as a delimiter.
	int word = 0;
	while (line[i] != '\0') { //Runs untill the string is terminated
		if (line[i++] == delim) { //Each time we find a delimiter, we increase word by one.
			word++;
			while(line[i] == delim) //after we found a delimiter, we 'eat' all the delimiter
				i++; 				//chars untill the first non-delimiter char appears
		}
	}
	return ++word;
}


char** input_to_token(char* token_string, char* delim) {
	int words = count_delimited_words(token_string,' '); //The amount of words we'll need to hold
	char** return_token = (char**)malloc(sizeof(char*)*(words)+1); //malloc'ing the exact number of memory we'll need
	int i = 0;
	char *token = NULL; //temp token

	token = (char*)strtok(token_string, delim); //extracts the first word using delim as delimiter
	while (token != NULL) { //While there are still words to extracts (no words -> token == null)
		return_token[i] = (char*)malloc(sizeof(char)*strlen(token)+1); //Allocating a string in the size of the word we need to store
		strcpy(return_token[i],token); //copies the token into the string array.
		token = (char*)strtok(NULL, delim); //Grabs the next token.
		i++; //increments i, which indicates which index of the return_token array we'll store next.
	}
	return_token[i] = NULL;
	return return_token;
}
