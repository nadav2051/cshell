#include "prompt.h"


char* get_hostname() { 
	char temp_hostname[MAX_HOSTNAME_LENGTH]; 
	char* hostname;								
	
	//Grabbing the hostname into a MAX_HOSTNAME_LENGTH size array.
	gethostname(temp_hostname, MAX_HOSTNAME_LENGTH); 
	//Allocating the minimal memory needed to store the string.
	hostname = (char*)malloc(sizeof(char)*strlen(temp_hostname));
	//copies the temp_hostname into the hostname (minimal) char array.
	strcpy(hostname, temp_hostname);
	return hostname;
}


char* get_username() { 
	char temp_username[MAX_USERNAME_LENGTH]; 
	char* username;								
	
	//Grabbing the hostname into a MAX_USERNAME_LENGTH size array.
	getlogin_r(temp_username, MAX_USERNAME_LENGTH); 
	//Allocating the minimal memory needed to story the string.
	username = (char*)malloc(sizeof(char)*strlen(temp_username));
	//copies the temp_username into the username (minimal) char array.
	strcpy(username, temp_username);
	return username;
}

char* get_prompt_string(int return_code) { 
	char* hostname = get_hostname();
	char* username = get_username();
	char tempString[(strlen(hostname) + strlen(username) + 2)];
	char* prompt = (char*)malloc(sizeof(char)*(strlen(hostname) + strlen(username) + 2));
	
	sprintf(tempString,"%d %s@%s$ ",return_code ,username, hostname); 

	strcpy(prompt, tempString);
	//Freeing the char arrays allocated with malloc in get_hostname()
	//and get_username()

	free(hostname);
	free(username);
	//returns the correct prompt of format user@host$
	return prompt;
}
