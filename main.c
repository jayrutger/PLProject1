#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "lexer.h"
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
	       	printf("\n");

	while(1){
		int tokenType = getTokenType();

		if(tokenType == UNDERSCOREERROR)
		{
			printf("\nSyntax Error! Underscore at the end of a symbol");
			//display expected argument
	       		printf("\n");
			break;
		}
		if(tokenType == BEGINERROR)
		{
			printf("\nSyntax Error! Begin Mispelled!");
			//display expected argument
	       		printf("\n");
			break;
		}
		if(tokenType == PARENERROR)
		{
			printf("\nSyntax Error! Parenthesis expected!");
			//display expected argument
	       		printf("\n");
			break;
		}

		if(tokenType == MISSINGOPERATOR)
		{
			printf("\nSyntax Error! Missing operator");
			//display expected argument
	       		printf("\n");
			break;
		}
		else if(tokenType == ERROR) {
			printf("Syntax error expected: ");
			//display expected argument
	       		printf("\n");
			break;
		}
		else if (tokenType == DONE)
		{
			checkArrayForDuplicates();
			printf("\n Success!\n");
			for(int i=0;i<15;i++)
			{
				printf(words[i]);
				if(i==insertionTracker-1)
				{
					printf("\n");
					break;
				}
				printf(",");
			}
			break;
		}
	}

	fclose(fp);
	exit(EXIT_SUCCESS);
}
