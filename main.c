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
	char cwd[256];
	int numOfWords = 0;


	while(notDone)
	{
		printf("\ndsh> ");

 		fgets(cmdline, MAXBUF, stdin);  // reads up to 256 characters into the buffer
	
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

		char **terms = split(cmdline, " ",&numOfWords);

		if(strcmp(cmdline,"\n") != 0)
		{
			if(cmdline[0] == '/')
			{				
				printf("File: %s\n", cmdline);
				if (access(cmdline, F_OK | X_OK) == 0) 
				{
					printf("File exists\n");
				}
				else
				{
					printf("ERROR: File doesn't exist. Try again...\n");
				}
			}
		
			else if(strcmp(cmdline,"pwd") == 0)
			{
				getcwd(cwd,sizeof(cwd));
				printf("%s\n",cwd);
			}
			else if(strcmp(terms[0],"cd") == 0)
			{
				if(strcmp(terms[1], "\0") != 0)
				{
					getcwd(cwd,sizeof(cwd));
					//printf("CWD Before: %s\n", cwd);
					char* chPath = malloc(512);

					strcpy(chPath,cwd);
					strcat(chPath,"/");
					strcat(chPath,terms[1]);

					chdir(chPath);
					free(chPath);
				}
				else
				{
					printf("In here");
					chdir("~");
				}
		
			}
			else if(strcmp(cmdline,"exit") == 0)
			{
				notDone = false;
			}
			else
			{

				//char* tok = malloc(256); 
				//tok = strtok(cmdline," ");
				int pid = fork();
				if(pid)
				{
					
					wait(&pid);

				}
				else
				{
					// int ind = 0;
					// char lastChar;
					// while(cmdline[ind] != '\0')
					// {
					// 	if(cmdline[ind+1] == '\0')
					// 	{
					// 		lastChar = cmdline[ind];
					// 	}
					// 	ind++;
					// }
					printf("Last Char = %s",terms[numOfWords-1]);

					if(strcmp(terms[numOfWords-1],"&") == 0)
					{
						getcwd(cwd,sizeof(cwd));

						char* fullPath = malloc(512);
						strcpy(fullPath,cwd);
						strcat(fullPath,"/");
						strcat(fullPath,cmdline);


						printf("Full Path: %s\n",fullPath);
						if (access(fullPath, F_OK | X_OK) == 0) 
						{
							printf("File exists\n");

							//exec and fork 
							execv(terms[0],terms);



    						// File exists and is executable! Can run!
						}
						else
						{
							printf("%s not found!\n", cmdline);
   					 		// No good! File doesn't exist or is not executable!
    						// Alert user and re-prompt
						}

						free(fullPath);
					
					}
					else if(strcmp(terms[0],"ls") == 0 )
					{					
						char* path = "/bin/ls";
						execv(path,terms);
					}
					else if(strcmp(terms[0],"cat") == 0)
					{
						char* path = "/bin/cat";
						execv(path,terms);
					}
					else if(strcmp(terms[0],"gcc") == 0)
					{
						char* path = "/bin/gcc";
						execv(path,terms);
					}
						
					exit(0);

				}
				
			}	
		}
	}

	return 0;
}
