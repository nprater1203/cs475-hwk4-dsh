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
#include "builtins.h"

// TODO: Your function definitions (declarations in dsh.h)

char** split(char *str, char *delim)
{
    int numTokens = 0;
    char* temp = malloc(MAXBUF);
    temp = str;
    int i = 0;
    while(temp[i] != '\0')
    {
        if(temp[i] == *delim)
        {
            numTokens++;
        }
        i++;
    }

    char* split2DArray[numTokens+2];

    for(int i = 0; i <= numTokens; i++)
    {
        split2DArray[i] = malloc(MAXBUF);
    }

    char* tok = malloc(MAXBUF);

    for(int i = 0; i <= numTokens; i++)
    {
        tok = strtok(temp,delim);
        printf("Tok: %s ", tok);
        strcpy(split2DArray[i], tok);
    }

    return split2DArray;
}