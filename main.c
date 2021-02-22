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
		printf("fuck");
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

	while(1){
		int tokenType = getTokenType();
		if(tokenType == ERROR) {
			printf("ERROR FOUND");
			break;
		}
		if (tokenType == DONE)
		{
			break;
		}
	}

	fclose(fp);
	exit(EXIT_SUCCESS);
}
