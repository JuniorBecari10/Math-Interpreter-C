all: compile run

compile:
	gcc main.c lexer.c token.c -o main.exe

run:
	./main.exe
