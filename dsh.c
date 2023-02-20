/*
 * dsh.c
 *
 *  Created on: Aug 2, 2013
 *      Author: chiu
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

// TODO: Your function definitions (declarations in dsh.h)

char** split(char *str, char *delim, int* numOfWords)
{
    int numTokens = 0;
    char* temp = malloc(MAXBUF);
    temp = str;
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

    char** split2DArray = (char*) malloc(numTokens+1);

    for(i = 0; i <= numTokens; i++)
    {
        split2DArray[i] = malloc(MAXBUF);
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

    for(i = 0; i < numTokens+1; i++)
    {
        printf("Index %d = %s\n", i,split2DArray[i]);
    }

    return split2DArray;
}
