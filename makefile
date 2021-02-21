all: main.c main.h lexer.c lexer.h
	gcc -g -Wall -o main main.c main.h lexer.c lexer.h

clean:
	$(RM) main
