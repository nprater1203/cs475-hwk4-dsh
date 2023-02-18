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
	int numOfWords = 0;
	// char cmd[] = "git add .";
	// //printf("HERE");
	// char **terms = split(cmd, " ",&numOfWords);
	// printf("Words = %d\n", numOfWords);
	// bool n = true;

	// //Test split function
	// // print out all the tokens
	// // printf("%s\n", terms[i]);
	// // i++;
	// for(int i = 0; i <= numOfWords; i++)
	// {
  	// 	printf("Word in %d - %s\n", i,terms[i]);
	// }
	// free(terms);

	while(notDone)
	{
		printf("dsh> ");

 		fgets(cmdline, MAXBUF, stdin);  // reads up to 256 characters into the buffer

		//  // this creates num pointers to strings
 		// char **array = (char**) malloc(num * sizeof(char*));

 		// // this loops through each array element and instantiates
 		// // an array of chars of length: CAPACITY
 		// for (int i = 0; i < num; i++) {
   		// 	array[i] = (char*) malloc(CAPACITY * sizeof(char));
		//  }

 		// // now I can assign strings to individual array elements
 		// for (int i = 0; i < num; i++) {
   		// 	strcpy(array[i], "hello world");
 		// }	
		bool notOut = true;
		int i = 0;
		while(cmdline[i] != '\0' && notOut){
			if(cmdline[i] == '\n')
			{
				cmdline[i] = '\0';
				notOut = false;
			}
			i++;
		}



		//printf("CMDLINE: %ssds",cmdline);

		char **terms = split(cmdline, " ",&numOfWords);
		//printf("NUMWORDS: %d\n", numOfWords);
		//tok = strtok(cmdline," ");

		if(strcmp(cmdline,"\n") != 0)
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
		
			else if(strcmp(cmdline,"pwd") == 0)
			{
				char cwd[256];
				getcwd(cwd,sizeof(cwd));
				printf("%s\n",cwd);
			}
			else if(strcmp(cmdline,"exit") == 0)
			{
				notDone = false;
			}
			else
			{


				//char* tok = malloc(256); 
				//tok = strtok(cmdline," ");
				if(strcmp(terms[0],"ls") == 0 )
				{
					// for(int i = 0; i <= numOfWords; i++)
					// {
					// 	printf("Term %d: %s\n",i,terms[i]);
					// }
					
					char* path = "/bin/ls";
					// char* args[numOfWords];
					// for(int j = 0; j < numOfWords; j++)
					// {
					// 	printf("HERE: %s\n", terms[j+1]);
					// 	if(strcmp(terms[j+1],"\0") != 0){
					// 		strcpy(args[0],terms[j+1]);
					// 	}
					// }
					// args[numOfWords-1] = "\0";

					
					execv(path,terms);
					//tok = strtok(cmdline,NULL);
					//printf("%s", cmdline);
				}
				else if(strcmp(terms[0],"cat") == 0)
				{
					char* path = "/bin/cat";
					execv(path,terms);
				}
				else if(strcmp(terms[0],"gcc") == 0){

				}
				else
				{
					printf("In here");
					char* cwd = malloc(512);
					getcwd(cwd,512);

					if(strcmp(terms[0],"cd") == 0)
					{
						if(strcmp(terms[1], "\0") != 0)
						{
							printf("CWD Before: %s\n", cwd);
							char* chPath = malloc(512);
							strcpy(chPath,cwd);
							strcat(chPath,"/");
							strcat(chPath,terms[1]);

							chdir(chPath);
							getcwd(cwd,512);
							printf("CWD After %s\n", cwd);

						}
			
					}
					else
					{

						//printf("temp: %sdfd",path);
						char* fullPath = malloc(512);
						strcpy(fullPath,cwd);
						strcat(fullPath,"/");
						strcat(fullPath,cmdline);


						printf("Full Path: %s\n",fullPath);
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
				}
				
				//if(cmdline[0])
			}
		}
		


		



	}

	// free(line);



	return 0;
}
