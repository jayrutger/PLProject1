#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "lexer.h"
#include <string.h>
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
		else if(tokenType == ENDLINE)//FINISHED ONE LINE
		{

			int i=0;
			int n=0;
			//Register array printouts
			while(1)
			{
			//	int i=0;
			//	int n=0;
				char operandChecker = registerArray[i][0];
				printf("\n");
				printf("first value seen: ");
				printf("%s",registerArray[i]);
				printf("\n");
				//if it isnt an operation, which means an ID or number
				if(operandChecker != '+' && operandChecker != '-' && operandChecker != '/' && operandChecker != '*')
				{
					printf("R");
					printf("%d",n);
					printf(" = ");
					printf("%s",registerArray[i]);
					printf("\n");
					//Save as R0
					//if youre ON an ID/number, and your NEXT is an ID (not an operator) 
					char operandChecker2 = registerArray[i+1][0];
					//printf("Second value seen: ");
					//printf("%c",registerArray[i+1][0]);
					//printf("\n");
					if(operandChecker2 != '+' && operandChecker2 != '-' && operandChecker2 != '/' && operandChecker2 != '*')
					{
						if(registerArray[i+1][0]!= '+')
						{
				//			printf("SHOULD NOT BE HERE");
						}
						printf("R");
						printf("%d",n+1);
						printf(" = ");
						printf("%s",registerArray[i+1]);
						printf("\n");
						//Save as R1
						//Save R0, set hasPreviousTerm = 1, also possibly n++ for Rn
						//Loop to beginning	
						char operandChecker3 = registerArray[i+2][0];

				//		printf("Third value seen: ");
				//		printf("%s",registerArray[i+2]);
				//		printf("\n");
						if(operandChecker3 == '+'|| operandChecker3 == '-'|| operandChecker3 == '/'|| operandChecker3 == '*')
						{
							//n++?
							printf("R");
							printf("%d",n);
							printf(" = ");
							printf("R");
							printf("%d",n);
							printf("%c",operandChecker3);
							printf("R");
							printf("%d",n+1);
							printf("\n");
						//	printf("MADEITRHERE");
							n++;
							i+=3;
	
							//printf("\n");
						//	printf("next value seen: ");
						//	printf("%s",registerArray[i]);
						//	printf("\n");
						}
						else//if 2 IDs in a row, and third ISNT operation
						{
						/*	
							printf("R");
							printf("%d",n-1);
							printf(" = ");
							printf("R");
							printf("%d",n-1);
							printf("%c",operandChecker2);
							printf("R");
							printf("%d",n);
							printf("\n");
							break;
							*/
						}

						
					}
					else//first thing you land on is an ID, and then next is a operator
					{
						
							printf("R");
							printf("%d",n-1);
							printf(" = ");
							printf("R");
							printf("%d",n-1);
							printf("%c",operandChecker2);
							printf("R");
							printf("%d",n);
							printf("\n");
							n++;
							i+=2;
							
					}

				//break;
				//If youre on and ID/Number, and your NEXT is an
				if(registerArray[i][0]=='\0')
				 {
					break;
				 }
				}	
				else//if first thing seen is a OPERATION, use on your Rn(0) and Rn+1
				{
					//		printf("HUH");

							printf("R");
							printf("%d",n);
							printf(" = ");
							printf("R");
							printf("%d",n);
							printf("%c",operandChecker);
							printf("R");
							printf("%d",n+1);
							printf("\n");
							n++;

					break;
				}	
			}

			for(int k=0;k<15;k++)
			{
				if(k==0)
				{
					printf("*****[");
				}
				if(registerArray[k][0] == '\0')
				{
					break;
				}
				else
				{
					printf("%s",registerArray[k]);
					if(registerArray[k+1][0] == '\0')
					{

						printf("]*****");
						break;
					}
					else
					{
						printf(",");
					}
				}	
			}
			memset(&registerArray[0],0,sizeof(registerArray));
		}
		else if (tokenType == DONE)
		{
			checkArrayForDuplicates();
			printf("\nSuccess!\n");
			for(int i=0;i<15;i++)
			{

				//printed out original list of ID's
				//printf("%s",words[i]);
//				printf("%s",intStrings[i]);//prints ints
				if(i==insertionTracker-1)
				{
					printf("\n");
					break;
				}
				
				//printed out comma for list
			//	printf(",");
			}
			printf("\n");
			break;
		}

		/*for(int k=0;k<15;k++)
		{
			printf("%s",registerArray[k]);		
			printf(", ");
		}*/
		//printf(" END ");

	//	printf("%s\n",registerArray);
		//printf("%c",intStrings[1][0]);//prints ints
	/*	printf("%s","BE Word:");
		printf("%s",beforeEqualsWord);

		printf("\n");
		
		printf("%s","Register Word 1:");
		printf("%s",registerArray[0]);
		
		printf("\n");

		printf("%s","Register Word 2:");
		printf("%s",registerArray[1]);
		
		printf("\n");

		printf("%s","Register Word 3:");
		printf("%s",registerArray[2]);
		
		printf("\n");

		printf("%s","Register Word 4:");
		printf("%s",registerArray[3]);
		
		printf("\n");

		printf("%s","Register Word 5:");
		printf("%s",registerArray[4]);
		
		printf("\n");

		printf("%s","Register Word 6:");
		printf("%s",registerArray[5]);
		
		printf("\n");

		printf("%s","Register Word 7:");
		printf("%s",registerArray[6]);
		
		printf("\n");

		printf("%s","Register Word 8:");
		printf("%s",registerArray[7]);
		
		printf("\n");

		printf("%s","Register Word 9:");
		printf("%s",registerArray[8]);
		
		printf("\n");

		printf("%s","Register Word 10:");
		printf("%s",registerArray[9]);
		
		printf("\n");


		printf("%s","Register Word 11:");
		printf("%s",registerArray[10]);
		
		printf("\n");

		printf("%s","Register Word 12:");
		printf("%s",registerArray[11]);
		
		printf("\n");

		printf("%s","Register Word 13:");
		printf("%s",registerArray[12]);
		
		printf("\n");

		printf("%s","Register Word 14:");
		printf("%s",registerArray[13]);
		
		printf("\n");
	*/
	}

//		printf("%s","BE Word:");
//		printf("%s",beforeEqualsWord);
	fclose(fp);
	exit(EXIT_SUCCESS);
}
