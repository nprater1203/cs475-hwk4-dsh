/*
 * main.c
 *
 *  Created on: Mar 17 2017
 *      Author: david
 */

/*
	Name: Nicholas Prater
	Course: CS 481 OS
	Professor: Dr. Chiu
	Date: 2/20/23
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include "dsh.h"

int main(int argc, char **argv)
{
	char cmdline[MAXBUF]; // stores user input from commmand line
	bool notDone = true;
	char cwd[256];
	char* chPath = malloc(512);
	char* fullPath = malloc(512);
	bool isFile = true;

	char **terms;

	int numOfWords = 0;
	bool amp = false;


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

		terms = split(cmdline, " ",&numOfWords);

		if(strcmp(cmdline,"\n") != 0)
		{
			if(strcmp(cmdline,"pwd") == 0)
			{
				getcwd(cwd,sizeof(cwd));
				printf("%s\n",cwd);
			}
			else if(strcmp(terms[0],"cd") == 0)
			{
				//printf("Term 1: %sdfnjdfn\n", terms[1]);
				if(terms[1] != NULL)
				{
					getcwd(cwd,sizeof(cwd));
					//printf("CWD Before: %s\n", cwd);

					strcpy(chPath,cwd);
					strcat(chPath,"/");
					strcat(chPath,terms[1]);

					if(chdir(chPath) != 0)
					{
						printf("Path given is not a directory...");
					}
				}
				else
				{
					char* homeDir = getenv("HOME");
					//printf("Home dir = %s\n", homeDir);
					chdir(homeDir);
				}
		
			}
			else if(strcmp(cmdline,"exit") == 0)
			{
				notDone = false;
			}
			else
			{
				printf("In child\n");
				//printf("0 Term: %s\n", terms[0]);
				int ind = 0;
				char lastChar;
				while(cmdline[ind] != '\0')
				{
					if(cmdline[ind+1] == '\0')
					{
						lastChar = cmdline[ind];
					}
					ind++;
				}
				//printf("Last Char = %c\n",lastChar);

				//printf("File: %s\n", cmdline);

				// if(cmdline[0] == '/'){
				// 	if (access(cmdline, F_OK | X_OK) == 0) 
				// 	{
				// 		printf("File exists\n");
				// 	}
				// 	else
				// 	{
				// 		printf("ERROR FIRST: %s not found!\n",terms[0]);
				// 	}
				// }
				// else
				// {
				// 	getcwd(cwd,sizeof(cwd));

				// 	strcpy(fullPath,cwd);
				// 	strcat(fullPath,"/");
				// 	strcat(fullPath,terms[0]);
				// 	if (access(cmdline, F_OK | X_OK) == 0) 
				// 	{
				// 		printf("File exists\n");
				// 	}
				// 	else
				// 	{
				// 		printf("ERROR: %s not found!\n",terms[0]);
				// 	}

				// }

				if(lastChar == '&')
				{
						//printf("IN HERE");
					amp = true;
					terms[ind-1] = NULL;
					//printf("File here: %s\n", cmdline);
					isFile = checkFile(terms[0]);
					//printf("isFile = %d", isFile);
				}

				//char* tok = malloc(256); 
				//tok = strtok(cmdline," ");
				if(isFile)
				{
					int pid = fork();
					if(pid)
					{
						printf("parent waiting\n");
						if(!amp)
						{
							wait(&pid);
						}

					}
					else
					{
						printf("child running\n");
						fflush(stdin);
						//sleep(1);

						// // printf("0 Term: %s\n", terms[0]);

						
						// }
						if(strcmp(terms[0],"ls") == 0 )
						{					
							char* path = "/bin/ls";
							// for(int b = 0; b <= numOfWords; b++)
							// {
							// 	printf("%d Term: %s\n", b, terms[b]);
							// }
							execv(path,terms);
						}
						else if(strcmp(terms[0],"cat") == 0)
						{
							char* path = "/bin/cat";
							// if(terms[1][0] != '/')
							// {
							// 	pathFile(terms[1]);
							// }
							if(execv(path, terms) != 0)
							{
								printf("File given does not exist");
							}
						}
						else if(strcmp(terms[0],"gcc") == 0)
						{
							char* path = "/bin/gcc";
							execv(path,terms);
						}
						else
						{
							//printf("In here");
							if(checkFile(terms[0]))
							{
								execv(terms[0],terms);
							}

						}
							
						exit(0);

					}
				}
				
			}	
		}
	}
	free(chPath);
	free(fullPath);

	for(int a = 0; a <= numOfWords; a++)
	{
		free(terms[a]);
	}
	terms = NULL;


	return 0;
}


					
						// getcwd(cwd,sizeof(cwd));

						// char* fullPath = malloc(512);
						// strcpy(fullPath,cwd);
						// strcat(fullPath,"/");
						// strcat(fullPath,cmdline);


						// printf("Full Path: %s\n",fullPath);
						// if (access(fullPath, F_OK | X_OK) == 0) 
						// {
						// 	printf("File exists\n");

						// 	//exec and fork 
						// 	execv(terms[0],terms);



    					// 	// File exists and is executable! Can run!
						// }
						// else
						// {
						// 	printf("%s not found!\n", cmdline);
   					 	// 	// No good! File doesn't exist or is not executable!
    					// 	// Alert user and re-prompt
						// }

						// free(fullPath);
					