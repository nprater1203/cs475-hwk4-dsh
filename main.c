/*
 * main.c
 *
 *  Created on: Mar 17 2017
 *      Author: david
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include "dsh.h"

int main(int argc, char **argv)
{
	char cmdline[MAXBUF]; // stores user input from commmand line
	bool notDone = true;
	char* tok = malloc(256*sizeof(char));
	char* path = malloc(256*sizeof(char));
	//int i = 0;

	//char *line = (char*) malloc(256); // create an empty buffer to store the input
	
	//split cmd on whitespace!
	char cmd[] = "git add .";
	char **terms = split(cmd, " ");

	//Test split function
	// print out all the tokens
	// int i = 0;
	// while (terms[i] != NULL) {
  	// 	printf("%s\n", terms[i]);
  	// 	i++;
	// }
	// free(terms);

	while(notDone)
	{
		printf("dsh> ");

 		fgets(cmdline, MAXBUF, stdin);  // reads up to 256 characters into the buffer

		 // this creates num pointers to strings
 		char **array = (char**) malloc(num * sizeof(char*));

 		// this loops through each array element and instantiates
 		// an array of chars of length: CAPACITY
 		for (int i = 0; i < num; i++) {
   			array[i] = (char*) malloc(CAPACITY * sizeof(char));
		 }

 		// now I can assign strings to individual array elements
 		for (int i = 0; i < num; i++) {
   			strcpy(array[i], "hello world");
 		}	
		bool notOut = true;
		while(cmdline[i] != '\0' && notOut){
			if(cmdline[i] == '\n')
			{
				cmdline[i] = '\0';
				notOut = false;
			}
			i++;
		}

		//printf("\n%s\n",cmdline);
		tok = strtok(cmdline," ");

		if(strcmp(tok,"\n") != 0)
		{
			if(cmdline[0] == '/')
			{				
				//path = strtok(cmdline,'\n');
				printf("File: %s\n", cmdline);
				if (access(cmdline, F_OK | X_OK) == 0) 
				{
					printf("File exists\n");

					//exec and fork 


    				// File exists and is executable! Can run!
				}
				else
				{
					printf("ERROR: File doesn't exist. Try again...\n");
   					 // No good! File doesn't exist or is not executable!
    				// Alert user and re-prompt
				}
			}
		
			else if(strcmp(cmdline,"pwd\n") == 0)
			{
				char cwd[256];
				getcwd(cwd,sizeof(cwd));
				printf("%s\n",cwd);
			}
			else if(strcmp(cmdline,"exit\n") == 0)
			{
				notDone = false;
			}
			else
			{
				char* tok = malloc(256); 
				tok = strtok(cmdline," ");
				if(strcmp(tok,"ls") == 0)
				{
					printf("In here\n");
					//tok = strtok(cmdline,NULL);
					printf("%s", cmdline);
				}
				else
				{
					char* cwd = malloc(512);
					getcwd(cwd,512);

					printf("temp: %sdfd",path);
					char* fullPath = malloc(512);
					strcpy(fullPath,cwd);
					strcat(fullPath,"/");
					strcat(fullPath,path);

					printf("Path: %s\n",fullPath);
					if (access(fullPath, F_OK | X_OK) == 0) 
					{
						printf("File exists\n");

						//exec and fork 


    					// File exists and is executable! Can run!
					}
					else
					{
						printf("ERROR: File doesn't exist. Try again...\n");
   					 	// No good! File doesn't exist or is not executable!
    					// Alert user and re-prompt
					}
				}
				
				//if(cmdline[0])
			}
		}

		



	}

	//free(line);



	return 0;
}
