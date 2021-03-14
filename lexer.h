#ifndef LEXER_H
#define LEXER_H
#include <stdlib.h>
#include <stdio.h>

#define EOS '/0'
#define NUM 256
#define DIV 257
#define MOD 258
#define ID 259
#define BEGIN 300
#define END 301
#define DONE 260
#define NOT_FOUND 0
#define ERROR 666
#define ENDLINE 123
#define EQUALS 11
#define OPERATOR 911
#define COMMENT 777
#define PARENERROR 444
#define MISSINGOPERATOR 12
#define UNDERSCOREERROR 31
#define BEGINERROR 214
#define UNDEFINEDVAR 321

int insertionTracker;
int arraySpaceTracker;
int intArraySpaceTracker;
int tokenval;
int lookahead;
int lineno;
int numUnderscores;

char* words[99];
char* intWords[99];
char str[99][99];
char intStrings[99][99];
int parenthesisCount;

void checkStorageArrayForWord(char* word);
int getTokenType();
int recurseThroughNumber();
int recurseThroughSymbol();
void checkArrayForDuplicates();
void intCheckerAndStorage();
int recurseThroughSymbolForInts();

#endif
