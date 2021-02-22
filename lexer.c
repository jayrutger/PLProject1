#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "main.h"
#include "lexer.h"
/*
EOS = '\0';
NUM =  256;
DIV= 257;
MOD= 258;
ID= 259;
BEGIN= 300;
END= 301;
DONE= 260;
NOT_FOUND= 0;
ERROR= 666;
ENDLINE= 123
EQUALS =11;
OPERATOR= 911;
*/
int getTokenType()
{
	while(1){
		//EOF CHECKER
		if(lengthOfFile <= lookahead)
		{
			return DONE;
		}

		if(fileContents[lookahead] == '~')
		{
			while(1)
			{
				if(fileContents[lookahead] == '\n')
				{
					printf("%c",fileContents[lookahead]);
					lookahead++;//Move it over one more
					lineno++;
					return COMMENT;//Not used
					break;
				}
				else
				{
					printf("%c",fileContents[lookahead]);
					lookahead++;
				}
			}
		}
		if(fileContents[lookahead] == 'b')
		{

			if(lookahead+4 >= lengthOfFile)
			{
				//cant be begin, continue on
			}
			else//if there is space for "begin"
			{
				if( fileContents[lookahead+1] == 'e' && 
				fileContents[lookahead+2] == 'g' && fileContents[lookahead+3] == 'i' && 
				fileContents[lookahead+4] == 'n')
				{
					printf("%c",fileContents[lookahead]);
					printf("%c",fileContents[lookahead+1]);
					printf("%c",fileContents[lookahead+2]);
					printf("%c",fileContents[lookahead+3]);
					printf("%c",fileContents[lookahead+4]);
					lookahead+=5;
					return BEGIN;
				}
			}	
		}

		//ch = fileContents[lookahead];	
		if(fileContents[lookahead] == 'e')
		{
			if(lookahead+3 >= lengthOfFile)
			{
				//cant be begin, continue on
			}
			else//if there is space for "end"
			{
				if( fileContents[lookahead+1] == 'n' && 
				fileContents[lookahead+2] == 'd' && fileContents[lookahead+3] == '.')
				{
					printf("%c",fileContents[lookahead]);
					printf("%c",fileContents[lookahead+1]);
					printf("%c",fileContents[lookahead+2]);
					printf("%c",fileContents[lookahead+3]);
					lookahead+=4;
					return END;
				}
			}	
		}

		if(fileContents[lookahead] == ' ' || fileContents[lookahead] == '\t')
		{
			//do nothing
			printf("%c",fileContents[lookahead]);
			lookahead++;
		}	
		else if(fileContents[lookahead] == '\n')
		{
			printf("%c",fileContents[lookahead]);
			lineno++;
			lookahead++;
		}
		else if(isdigit(fileContents[lookahead]))
		{
		//	printf("%c",fileContents[lookahead]);
			return recurseThroughNumber();
		}
		else if(isalpha(fileContents[lookahead]))
		{
		//	printf("%c",fileContents[lookahead]);
			return recurseThroughSymbol();
		}
		else if(fileContents[lookahead] == ';')
		{
			printf("%c",fileContents[lookahead]);
			lookahead++;
			return ENDLINE;
		}
		else if(fileContents[lookahead] == '=')//Can only have 1!
		{		
			printf("%c",fileContents[lookahead]);
			lookahead++;
			return EQUALS;
		}

		else if (fileContents[lookahead] == '+' || fileContents[lookahead] == '-' || fileContents[lookahead] == '/' || fileContents[lookahead] == '*')
		{
			printf("%c",fileContents[lookahead]);
			lookahead++;
			return OPERATOR;
		}
		else if(fileContents[lookahead] == '(' || fileContents[lookahead] == ')')
		{
			//printf("OH FUCK");
			lookahead++;
			return OPERATOR;
		}
		else
		{
			if(fileContents[lookahead]== ' ')
			{
				printf("HERE");
			}
			else
			{
				printf("UFUCKCF");
			}
		}
	}
}

int recurseThroughNumber()
{
	char ch = (char) fileContents[lookahead];
	if(isdigit(ch))
	{
		printf("%c",fileContents[lookahead]);
		lookahead++;
		return recurseThroughNumber();	
	}
	else if(isalpha(ch) || ch=='_' )
	{
		//Cannot start with a number!
		printf("invald");
		return ERROR;
	}
	else//is an operator?
	{
		return NUM;
	}
}

int recurseThroughSymbol()
{
	char ch = (char) fileContents[lookahead];
	if(isalpha(ch) || isdigit(ch) || ch == '_')
	{
		if(ch=='_')
		{
			numUnderscores++;
			if(numUnderscores > 1)
			{
				return ERROR;
				//No more than 1 underscore in a row
			}
		}

		else
		{
			numUnderscores=0;
		}
		printf("%c",fileContents[lookahead]);
		lookahead++;
		return recurseThroughSymbol();
		}	
	
		else
		{
			//No more underscores in a row
			if(numUnderscores>0)
			{
				return ERROR;
			}
			else
			{
				return ID;
			}
	
		}

}
