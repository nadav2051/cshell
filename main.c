
#include "prompt.h"
#include "iomanip.h"
#include "syscall.h"
#include <signal.h>
#define MAX_USER_INPUT 510


int get_user_input(int return_code,char* user_input) { 
	//prints the formatted prompt
	char tempInput[MAX_USER_INPUT];
	char* prompt = get_prompt_string(return_code);
	printf("%s", prompt);
	scanf("%[^\n]", user_input);

	strncpy(tempInput, user_input, MAX_USER_INPUT);
	//checks to see if exit was called.
	if (user_input == NULL || (int)*user_input == 0) {
		while(getchar() != '\n');
		return 0;
	}
	else if(compare_input_to_word(input_to_token(tempInput, " ")[0],"exit") == 1) {
		exit(0);
	}

	else {
		//breaks the input into array of strings seperated by the delimiter - " ".
		return_code = execute(user_input); 
	}
		//empties the buffer of newline characters.
	while(getchar() != '\n');

	//frees the space we've allocated for the prompt
	free(prompt);
	return return_code;	
}

int main() {
	signal(SIGINT, SIG_IGN);
	int return_code = 0;
	char *user_input = (char*)malloc(sizeof(char)*MAX_USER_INPUT);
	user_input = (char*)memset(user_input,MAX_USER_INPUT*sizeof(char), 0);


	while(1) {
		return_code = get_user_input(return_code, user_input);
		strcpy(user_input,"");
	}

}