#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "main.h"
#include "lexer.h"

/*******************************************
 * Programming Languages with Dr. Coffey
 * 
 * Project 2: Recursive-Descent Parser Register Output
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
 * what it reads. For part 2 I added on tracker
 * for saving register words, and postfix terms,
 * aligning them in the right order before adding
 * them to their char arrays. 
********************************************/
//This function reads the file contents string, and assignes token types accordingly. 
//It calls recursive function to read numbers and symbols as well, and stores them into
//the register array
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
					if(fileContents[lookahead]=='\n')
					{
						if(fileContents[lookahead+1]=='i')
						{
							if(fileContents[lookahead+2]=='n')
							{
								if(fileContents[lookahead+3]=='t')
								{
									if(fileContents[lookahead+4]==' ')
									{
										if(fileContents[lookahead+5]=='a')
										{	
											if(fileContents[lookahead+6]==',')
											{
												return PARENERROR;
											}

										}
									}
								}
							}
						}

						else if(fileContents[lookahead+1] == ' ')
						{
							if(fileContents[lookahead+2] == ' ')
							{	
								if(fileContents[lookahead+5] == 't')
								{
									if(fileContents[lookahead+7] == 'a')										{
									if(fileContents[lookahead+8] == '_')
									{
										return MISSINGOPERATOR;
									}
								}
							}
						}	
					}
					}
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
		//	savedOperation='\0';//might not need?
			if(operationSaved == 1)//One remaining operation left to append
			{	
				afterEquals=0;
				lookahead++;
				strncat(registerArray[registerArrayTracker],&savedOperation,1);
				registerArrayTracker = 0;
				return ENDLINE;
			}
			else
			{
			afterEquals=0;
			lookahead++;
			registerArrayTracker = 0;
			if(parenthesisCount != 0)
			{
				return PARENERROR;
			}		
			return ENDLINE;
			}
		}
		else if(fileContents[lookahead] == '=')//Can only have 1!
		{	
			afterEquals=1;	
			lookahead++;
			return EQUALS;
		}

		else if (fileContents[lookahead] == '+' || fileContents[lookahead] == '-' || fileContents[lookahead] == '/' || fileContents[lookahead] == '*')
		{

	
			char ch1 = fileContents[lookahead];
			//Add operand to NEXT spot in registerArray, so to be after the second term (since it shows up b/w terms)
			char bSymbol = registerArray[registerArrayTracker][0];
		       	if(bSymbol == '+' || bSymbol == '-' || bSymbol == '*' || bSymbol== '/')
			{
				strncat(registerArray[registerArrayTracker+2],&ch1,1);
			}
			else
			{	
				strncat(registerArray[registerArrayTracker+1],&ch1,1);
			}
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
				if(operationSaved == 1)
				{

					//if operation has been saved, and end of parenth is reached, add saved op to end of register array
					char operandChecker = registerArray[registerArrayTracker][0];
					//Check place where youre about to fill out
					if(operandChecker == '+' || operandChecker == '-' || operandChecker == '/' || operandChecker == '*')
					{
						registerArrayTracker++;//Go to spot AFTER operand, since it got moved ahead. Avoids overwriting!
					}
					strncat(registerArray[registerArrayTracker],&savedOperation,1);
					savedOperation='\0';
					//might have to check if something is already there, like an operation already
					operationSaved =0;
				}
				else
				{
				}
				char afterLookahead = fileContents[lookahead+1];

		       		if(afterLookahead == '+' || afterLookahead == '-' || afterLookahead == '*' || afterLookahead== '/')
				{
					savedOperation = afterLookahead;
					operationSaved = 1;//will use as a flag to skip that operation from saving in register right now
					lookahead++;//we have seen through the next and handled it, so skip it
				}
				else if(afterLookahead == ' ')
				{
					char afterLookahead2 = fileContents[lookahead+2];
					printf("\n");
		       			if(afterLookahead2 == '+' || afterLookahead2 == '-' || afterLookahead2 == '*' || afterLookahead2 == '/')
					{

						savedOperation =afterLookahead2;
						operationSaved=1;
						lookahead+=2;//skip the whitespace and operation, we have handled it
					}

				}
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

//This function checks the validity of a value that starts with a number, and saves it to the register table
int recurseThroughNumber()
{
	char ch = (char) fileContents[lookahead];
	if(isdigit(ch))
	{
		char operandChecker = registerArray[registerArrayTracker][0];
		//Check place where youre about to fill out
		if(operandChecker == '+' || operandChecker == '-' || operandChecker == '/' || operandChecker == '*')
		{
			registerArrayTracker++;//Go to spot AFTER operand, since it got moved ahead. Avoids overwriting!
		}

		strncat(registerArray[registerArrayTracker],&ch,1);
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

//This function checks to see if the symbol was declared
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
					recurseThroughSymbolForInts();
				}
			}
		}
	}

}


//This function helps check our final symbol table for the correct words (project 1)
void checkStorageArrayForWord(char* word)
{
	words[insertionTracker] = word;
	insertionTracker++;
}

//Unused
void insertIntoStorageArrayForInts(char* word)
{
	//intWords[] = word;
	//insertionTracker++;
}

//This function searches through all declared ints and saves them for later reference
int recurseThroughSymbolForInts()
{
	char ch = (char) fileContents[lookahead];
	if(ch == ',')
	{	
		insertIntoStorageArrayForInts(intStrings[intArraySpaceTracker]);
		intArraySpaceTracker++;
		lookahead++;//end current word but keep looping until ;
		return recurseThroughSymbolForInts();
	}
	if(isalpha(ch) || isdigit(ch) || ch == '_')
	{

		strncat(intStrings[intArraySpaceTracker],&ch,1);
		lookahead++;
		return recurseThroughSymbolForInts();
	}	
	else if(ch == ' ')
	{

		lookahead++;//sometimes has spaces after ,
		return recurseThroughSymbolForInts();
	}
	else//semicolon ; condition
	{

			insertIntoStorageArrayForInts(intStrings[intArraySpaceTracker]);
			intArraySpaceTracker++;
			lookahead++;
			return ID;	//Now, need to look for int again, but deal with newline and spaces
	}
}

//This function recursively searches symbols that begin with a letter, and saved these words to the register array
int recurseThroughSymbol()
{
	char ch = (char) fileContents[lookahead];
	if(isalpha(ch) || isdigit(ch) || ch == '_')
	{
		char operandChecker = registerArray[registerArrayTracker][0];
		//Check place where youre about to fill out
		if(operandChecker == '+' || operandChecker == '-' || operandChecker == '/' || operandChecker == '*')
		{
			registerArrayTracker++;//Go to spot AFTER operand, since it got moved ahead. Avoids overwriting!
		}
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
			checkStorageArrayForWord(str[arraySpaceTracker]);
			if(afterEquals==0)//if afterEquals is false, which means its before equals
			{
				beforeEqualsWord = str[arraySpaceTracker];
				BEWordArray[beIndex] = str[arraySpaceTracker];
				beIndex++;	
			}
			else
			{
				//Add to registerArray, increment registerarray value
				strcpy(registerArray[registerArrayTracker],str[arraySpaceTracker]);
				registerArrayTracker++;

			}
			arraySpaceTracker++;
			return ID;
		}	
	}
}

//This checks the final symbol table for duplicate symbols and corrects if any are found (project 1)
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
