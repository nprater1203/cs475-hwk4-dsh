/*
 * dsh.c
 *
 *  Created on: Aug 2, 2013
 *      Author: chiu
 */

/*
	Name: Nicholas Prater
	Course: CS 481 OS
	Professor: Dr. Chiu
	Date: 2/20/23
*/

#include "dsh.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <errno.h>
#include <err.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include "builtins.h"


char** split(char *str, char *delim, int* numOfWords)
{
    int numTokens = 0;
    char* temp = malloc(MAXBUF);
    strcpy(temp,str);
    int i = 0;
    while(temp[i] != '\0')
    {
        //printf("IS DELIM? -- %c\n", temp[i]);
        if(temp[i] == *delim)
        {
            numTokens++;
        }
        i++;
    }

   *numOfWords = numTokens;

   //printf("NumTokens = %d", numTokens);

    char** split2DArray = (char**) malloc(numTokens+1 * sizeof(char*));

    for(i = 0; i <= numTokens; i++)
    {
        //printf("%d\n", i);
        split2DArray[i] = (char*) malloc(MAXBUF* sizeof(char));
    }

    i = 0;
    char* tok = malloc(MAXBUF);
    if(numTokens != 0){
        tok = strtok(temp,delim);
        strcpy(split2DArray[i], tok);
        //printf("2D Array: %s\n", split2DArray[i]);
        bool notOverflow = true;
        i++;
        while(tok != NULL && notOverflow){
            //printf("I: %d\n", i);
            tok = strtok(NULL, " ");
            //printf("TOK: %s\n", tok);
            strcpy(split2DArray[i], tok);
            //printf("2D Array: %s\n", split2DArray[i]);
            i++;
            if(i > numTokens)
            {
                notOverflow = false;
            }

        }
    }
    else{
        strcpy(split2DArray[0],str);
    }

    split2DArray[numTokens+1] = NULL;

    // for(i = 0; i < numTokens+1; i++)
    // {
    //     printf("Index %d = %s\n", i,split2DArray[i]);
    // }

    free(temp);
    //free(tok);
    // for(int a = 0; a <= numTokens; a++)
	// {
	// 	free(split2DArray[a]);
	// }
	// free(split2DArray);
    return split2DArray;



}

bool checkFile(char* fileName)
{
    char* tempPath = fileName;
    if(fileName[0] != '/'){
        pathFile(fileName);
    }

    char* fullpath = fileName;

    //printf("Full path: %s\n", fullpath);
    if (access(fullpath, F_OK | X_OK) == 0) 
	{
		//printf("File exists\n");
        return true;
	}
	else
	{
		printf("ERROR: %s not found!\n",tempPath);
        return false;
	}


}

void pathFile(char* path)
{
    char cwd[MAXBUF];
    char* chPath = malloc(MAXBUF*sizeof(char));
    getcwd(cwd,sizeof(cwd));


    strcpy(chPath,cwd);
	strcat(chPath,"/");
	strcat(chPath,path);

    //printf("Path: %s\n", chPath);

    strcpy(path,chPath);
    //printf("Path after copy: %s\n", path);

    free(chPath);
    

}
