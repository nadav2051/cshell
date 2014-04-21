#include "syscall.h"
#include <signal.h>

void free_2d_array(char** arr, int size) {
	int i = 0;
	for (; i < size ; i++) {
		free(arr[i]);
	}
	free(arr);
}

int execute_to_file(char* input) { //expects	 a string in the format of: "arguements > filename".
	pid_t child_pid, tpid; //holds the pid of the child process.
	char** tokens; // will hold the tokens after we split it using ">" as delimiter
	char** arguments; //will hold the arguements after we split it from the original string.
	int child_status; //status of child the child process spawned using fork()
	int file_descriptor; //fd of the opened file.
	int stdout_b=dup(1); //saving the fd of stdout, to restore it after we wrote the input to file.
	int argument_count;
	//tokens[0] -> arguments, tokens[1] -> filename
	tokens = input_to_token(input,OUTPUT_REDIRECTION_STRING); //Seperates the arguements and the filename (arguments < filename )
	tokens[1] = strtok(tokens[1], " ");

	if ((file_descriptor = open(tokens[1], O_CREAT | O_APPEND | O_WRONLY, PREMISSIONS)) < 0) {
		fprintf(stderr, "Error occured while trying to open the file.\n");
		return OUTPUT_REDIRECTION_FAILURE;
	}
	//As said earlier, tokens[0] is a string contains the arguments, now we split the arguments
	//using space as a delimiter.
	argument_count = count_delimited_words(tokens[0], ' ');
	arguments = input_to_token(tokens[0], " ");

	if(dup2(file_descriptor, 1) < 0) {
		fprintf(stderr,"Error occured while writing to file.\n");
		//free_2d_array(tokens, args);
		return OUTPUT_REDIRECTION_FAILURE;
	}

	child_pid = fork();
	if (child_pid == 0) { //In child process
		child_status = execvp(*arguments,arguments);
		fprintf(stderr, "%s: command not found.\n",*arguments);
		dup2(stdout_b,1); //Returning the output to stdout
		close(file_descriptor); //Close the file_descriptor stream we opened (writing to file)
		exit(CALL_FAILURE);
	}
	else {
		while(wait(&child_status) != child_pid); //Waiting for child to finish
		dup2(stdout_b,1); //Returning the output to stdout
		close(file_descriptor);
		free_2d_array(arguments, argument_count);
		return (child_status>>8); //The child status need to be shifted by 8 bits to the right
								  //to get the correct number.
	}	
	return 0;
}

int execute(char* argv) { //Takes a string, tokenize it while using space as a delimiter.
	int arguments = count_delimited_words(argv, ' ');
	char** tokens; 
	pid_t child_pid, tpid; 
	int child_status;
	if (char_isin_string(argv, OUTPUT_REDIRECTION_CHAR)) //If '>' is in the string, the output should be to file instead of 
		return execute_to_file(argv);//stdout.
	else {

		tokens = input_to_token(argv," "); //tokenize the string using space as a delimiter

		child_pid = fork(); //forking a child process

		if (child_pid == 0) { // in child process
			signal(SIGINT, SIG_DFL);
			execvp(*tokens,tokens); 
			fprintf(stderr,"%s: command not found.\n",*tokens);
			free_2d_array(tokens, arguments);
			exit(CALL_FAILURE);
		}
		else { //parent process
			while(wait(&child_status) != child_pid);
			free_2d_array(tokens, arguments);
		return (child_status >> 8); //The child status need to be shifted by 8 bits to the right
								  //to get the correct number.
		}	
	}
}