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

int tokenval;
int lookahead;
int lineno;
int numUnderscores;


int getTokenType();
int recurseThroughNumber();
int recurseThroughSymbol();

#endif
