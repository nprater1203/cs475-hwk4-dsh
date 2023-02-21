/*
 * dsh.h
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

#include <stdbool.h>

#define MAXBUF 256
#define HISTORY_LEN 100

// TODO: Your function prototypes below

/**
 * Splits the cmdline in seperate words with delim of spaces
 *
 * @param	*str	     Pointer to the list of employees
 * @param	*char	     Delimiter for the split
 * @param   *numOfWords  Number of words given in the command line
 */
char** split(char *str, char *delim, int *numOfWords);

bool checkFile(char* fileName);

void pathFile(char* tempPath);