#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "lexer.h"

/*******************************************
 * Class: Programming Languages with Dr. Coffey

 * Project 1: Recursive-Descent Parser

 * Student: James Rutger
 
 * File: main.c
 
 * File Description: Main handles much of the
 * token status returns from the lexer file.
 * Main also does the file I/O taking in
 * the a1-a8 files and storing them into
 * a single string from which I read from
 * to do my work.
********************************************/
int main(int argc, char** argv)
{
	char * cmdInput = argv[1];
	FILE * fp;
	int c;
	fp = fopen(cmdInput,"r");
	if(fp == NULL){

		exit(EXIT_FAILURE);
	}
	do
	{
		c = fgetc(fp);
		if(feof(fp))
		{
			break;
		}
		fileContents[lengthOfFile]=c;
		lengthOfFile++;
	}while(1);

		printf("compiling ");
	       	printf("%s",cmdInput);

	while(1){
		int tokenType = getTokenType();
		
		if(tokenType == UNDEFINEDVAR)
		{
			printf("\nSyntax Error! Undefined variable found\n");
			//display expected argument
	       		printf("\n");
			break;
		}
		if(tokenType == UNDERSCOREERROR)
		{
			printf("\nSyntax Error! Underscore at the end of a symbol\n");
			//display expected argument
	       		printf("\n");
			break;
		}
		if(tokenType == BEGINERROR)
		{
			printf("\nSyntax Error! Begin Mispelled!\n");
			//display expected argument
	       		printf("\n");
			break;
		}
		if(tokenType == PARENERROR)
		{
			printf("\nSyntax Error! Parenthesis expected!\n");
			//display expected argument
	       		printf("\n");
			break;
		}

		if(tokenType == MISSINGOPERATOR)
		{
			printf("\nSyntax Error! Missing operator\n");
			//display expected argument
	       		printf("\n");
			break;
		}
		else if(tokenType == ERROR) {
			printf("Syntax error expected: \n");
			//display expected argument
	       		printf("\n");
			break;
		}
		else if (tokenType == DONE)
		{
			checkArrayForDuplicates();
			printf("\nSuccess!\n");
			for(int i=0;i<15;i++)
			{
				printf("%s",words[i]);
//				printf("%s",intStrings[i]);//prints ints
				if(i==insertionTracker-1)
				{
					printf("\n");
					break;
				}
				printf(",");
			}
			printf("\n");
			break;
		}
		//printf("%c",intStrings[1][0]);//prints ints
	}

	fclose(fp);
	exit(EXIT_SUCCESS);
}
