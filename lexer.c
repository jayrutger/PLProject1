#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "lexer.h"
int lexer()
{
	int symbol =  fileContents[lookahead];
	lookahead++;
	return symbol;

}

