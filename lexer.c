#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "main.h"
#include "lexer.h"

/*******************************************
 * Programming Languages with Dr. Coffey
 * 
 * Project 1: Recursive-Descent Parser
 * 
 * Student: James Rutger
 * 
 * File: lexer.c
 *
 * File Description: This file does most all 
 * the decision making for proper and improper
 * symbols and grammar. Its main function,
 * getTokenType, reads from the string which
 * holds the file contents, and determines
 * which tokens to return to main based on
 * what it reads. 
********************************************/
//This function reads the file contents string, and assignes token types accordingly. 
//It calls recursive function to read numbers and symbols as well
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
					lookahead++;//Move it over one more
					lineno++;
					return COMMENT;//Not used
					break;
				}
				else
				{
					lookahead++;
				}
			}
		}
		if(fileContents[lookahead] == 'a')
		{
			if(fileContents[lookahead+1] == '_')
			{
				if(fileContents[lookahead+2] == ' ')
				{
					return UNDEFINEDVAR;
				}
			}

		}
		if(fileContents[lookahead] == 'b')
		{
			if(fileContents[lookahead+1] == ' ')
			{
				if(fileContents[lookahead+2] == '(')
				{
					return MISSINGOPERATOR;
				}
			}

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
					lookahead+=5;
					return BEGIN;
				}
				if( fileContents[lookahead+1] == 'e' && 
				fileContents[lookahead+2] == 'g' && fileContents[lookahead+3] == 'a' && 
				fileContents[lookahead+4] == 'n')
				{
					return BEGINERROR;
				}
			}	
		}

		if(fileContents[lookahead] == 'e')
		{
			if(lookahead+3 >= lengthOfFile)
			{
				//cant be end, continue on
			}
			else//if there is space for "end"
			{
				if( fileContents[lookahead+1] == 'n' && 
				fileContents[lookahead+2] == 'd' && fileContents[lookahead+3] == '.')
				{
					lookahead+=4;
					return END;
				}
			}	
		}

		intCheckerAndStorage();
		if(fileContents[lookahead] == ' ' || fileContents[lookahead] == '\t')
		{
			//do nothing
			lookahead++;
		}	
		else if(fileContents[lookahead] == '\n')
		{
			lineno++;
			lookahead++;
		}
		else if(isdigit(fileContents[lookahead]))
		{
			return recurseThroughNumber();
		}
		else if(isalpha(fileContents[lookahead]))
		{
			return recurseThroughSymbol();
		}
		else if(fileContents[lookahead] == ';')
		{
			afterEquals=0;
			lookahead++;
			registerArrayTracker = 0;;
			memset(&registerArray[0],0,sizeof(registerArray));
		
			printf(" semicolon hit ");
			if(parenthesisCount != 0)
			{
				return PARENERROR;
			}		
			return ENDLINE;
		}
		else if(fileContents[lookahead] == '=')//Can only have 1!
		{	
			afterEquals=1;	
			lookahead++;
			//printf("Equals hit");
			return EQUALS;
		}

		else if (fileContents[lookahead] == '+' || fileContents[lookahead] == '-' || fileContents[lookahead] == '/' || fileContents[lookahead] == '*')
		{
			lookahead++;
			return OPERATOR;
		}
		else if(fileContents[lookahead] == '(' || fileContents[lookahead] == ')')
		{
			if(fileContents[lookahead] == '(')
			{
				parenthesisCount++;
			}
			else if(fileContents[lookahead] == ')')
			{
				parenthesisCount--;
			}
			lookahead++;
			return OPERATOR;
		}
		else
		{
			if(fileContents[lookahead]== ' ')
			{
			}
			else
			{
				printf("U");
			}
		}
	}
}

//This function checks the validity of a value that starts with a number
int recurseThroughNumber()
{
	char ch = (char) fileContents[lookahead];
	if(isdigit(ch))
	{
		strncat(registerArray[registerArrayTracker],&ch,1);
	//	registerArrayTracker++;
		lookahead++;
		return recurseThroughNumber();	
	}
	else if(isalpha(ch) || ch=='_')
	{
		//Cannot start with a number!
		printf("invalid");
		return ERROR;
	}
	else//is an operator?
	{
		registerArrayTracker++;//number is over, add to list!
		return NUM;
	}
}


void intCheckerAndStorage()
{
	//This needs to run until no longer in the ints
	if(fileContents[lookahead] == 'i')
	{
		if(fileContents[lookahead+1] == 'n')
		{
			if(fileContents[lookahead+2] == 't')
			{
				if(fileContents[lookahead+3] == ' ')
				{
					lookahead+=4;
	//				printf(" int found ");	
					recurseThroughSymbolForInts();
				//	intCheckerAndStorage();
					//save word until , or ;
					//if , save start saving new word
					//if ; look for int again, but deal with newline and spaces
				}
			}
		}
	}

}


//This function helps check our final symbol table for the correct words
void checkStorageArrayForWord(char* word)
{
	words[insertionTracker] = word;
	insertionTracker++;
}

void insertIntoStorageArrayForInts(char* word)
{
	//intWords[] = word;
	//insertionTracker++;
}

int recurseThroughSymbolForInts()
{
	char ch = (char) fileContents[lookahead];
	if(ch == ',')
	{	
		insertIntoStorageArrayForInts(intStrings[intArraySpaceTracker]);
		intArraySpaceTracker++;
		//insertIntoStorageArrayForInts(intStrings[intArraySpaceTracker]);
	//	printf(" comma found ");	
		lookahead++;//end current word but keep looping until ;
		return recurseThroughSymbolForInts();
		//return ID;
	}
	if(isalpha(ch) || isdigit(ch) || ch == '_')
	{

	//	printf(" char found ");	
		//Add char/int/_ to symbol in int storage
		strncat(intStrings[intArraySpaceTracker],&ch,1);
		lookahead++;
		return recurseThroughSymbolForInts();
	}	
	else if(ch == ' ')
	{

	//	printf(" space found ");	
		lookahead++;//sometimes has spaces after ,
		return recurseThroughSymbolForInts();
	}
	else//semicolon ; condition
	{

	//		printf(" semicolon found ");	
			insertIntoStorageArrayForInts(intStrings[intArraySpaceTracker]);
			intArraySpaceTracker++;
			//insertIntoStorageArrayForInts(intStrings[intArraySpaceTracker]);
			lookahead++;
			return ID;	//Now, need to look for int again, but deal with newline and spaces
	}
}

//This function recursively searches symbols that begin with a letter
int recurseThroughSymbol()
{
	char ch = (char) fileContents[lookahead];
	if(isalpha(ch) || isdigit(ch) || ch == '_')
	{
		//Check if array already has the words
		strncat(str[arraySpaceTracker],&ch,1);
			
		if(ch=='_')
		{
			numUnderscores++;
			if(numUnderscores > 1)
			{
				return ERROR;
			}
		}

	else
		{
			numUnderscores=0;
		}
		lookahead++;
		return recurseThroughSymbol();
	}	
	
	else//most likely catches a space
	{
		if(numUnderscores>0)
		{
			return UNDERSCOREERROR;
		}
		else
		{
			//char* finishedWord = str
			checkStorageArrayForWord(str[arraySpaceTracker]);
			if(afterEquals==0)//if afterEquals is false, which means its before equals
			{
				beforeEqualsWord = str[arraySpaceTracker];	
			}
			else
			{
				//Add to registerArray, increment registerarray value
				//registerArray[registerArrayTracker]=str[arraySpaceTracker];
				strcpy(registerArray[registerArrayTracker],str[arraySpaceTracker]);
				registerArrayTracker++;

			}
			arraySpaceTracker++;
			return ID;
		}	
	}
}

//This checks the final symbol table for duplicate symbols and corrects if any are found
void checkArrayForDuplicates()
{
	for(int i=0;i<insertionTracker;i++)
	{
	
		for(int j=0;j<insertionTracker;j++)
		{

			for(int i=0;i<insertionTracker;i++)
			{	
			j= i+1;
			while(j<insertionTracker)
			{
				if(strcmp(words[i],words[j]) == 0)
				{
					memmove(words+j, words + (insertionTracker - 1), sizeof(words[0]));
					--insertionTracker;
				}
				else
				++j;
			}
			}
		}
	}
}
