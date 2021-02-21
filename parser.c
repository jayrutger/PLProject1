
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "lexer.h"
#include "parser.h"


int parser()
{
	int symbol =  fileContents[lookahead];
	lookahead++;
	return symbol;

}

