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
	bool isFile = true;
	char **terms;
	int numOfWords = 0;
	bool amp = false;


	while(notDone)
	{
		printf("\ndsh> ");

		// Reads up to 256 characters into the buffer
 		fgets(cmdline, MAXBUF, stdin);  
	
		bool notOut = true;
		int i = 0;
		// Take out the newline
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
				if(terms[1] != NULL)
				{
					getcwd(cwd,sizeof(cwd));
					char* chPath = malloc(512);

					strcpy(chPath,cwd);
					strcat(chPath,"/");
					strcat(chPath,terms[1]);

					if(chdir(chPath) != 0)
					{
						printf("Path given is not a directory...");
					}
					free(chPath);
				}
				else
				{
					char* homeDir = getenv("HOME");
					chdir(homeDir);
				}
		
			}
			else if(strcmp(cmdline,"exit") == 0)
			{
				notDone = false;
			}
			else
			{
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

				if(lastChar == '&')
				{
					amp = true;
					terms[ind-1] = NULL;
					//printf("File here: %s\n", cmdline);
					isFile = checkFile(terms[0]);
					//printf("isFile = %d", isFile);
				}
				if(isFile)
				{
					int pid = fork();
					if(pid)
					{
						// Parent 

						//printf("parent waiting\n");
						if(!amp)
						{
							wait(&pid);
						}

					}
					else
					{
						// Child

						//printf("child running\n");
						fflush(stdin);

						if(strcmp(terms[0],"ls") == 0 )
						{					
							char* path = "/bin/ls";
							if(execv(path,terms) != 0)
							{
								printf("Error: Invalid command\n");
							}
						}
						else if(strcmp(terms[0],"cat") == 0)
						{
							char* path = "/bin/cat";
							if(execv(path, terms) != 0)
							{
								printf("File given does not exist\n");
							}
						}
						else if(strcmp(terms[0],"gcc") == 0)
						{
							//printf("GCC HERE\n");
							char* path = "/bin/gcc";
							if(execv(path,terms) != 0)
							{
								printf("ERROR: Invalid command\n");
							}
						}
						else
						{
							if(checkFile(terms[0]))
							{
								if(execv(terms[0],terms) != 0)
								{
									printf("Error: Invalid Command");
								};
							}
						}
						
						exit(0);

					}
				}
				
			}	
		}
	}

	
	for(int a = 0; a <= numOfWords; a++)
	{
		free(terms[a]);
	}
	terms = NULL;


	return 0;
}
					