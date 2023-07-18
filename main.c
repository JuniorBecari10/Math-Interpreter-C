#include <stdio.h>
#include <string.h>

#include "lexer.h"

double eval(char *input);

int main() {
  char input[100];
  double result;

  printf("Math Interpreter\n");
  printf("Type 'exit' to exit.\n\n");

  while (1) {
    printf("> ");
    fflush(stdin);
    scanf("%s", input);

    if (strcmp(input, "exit") == 0) break;

    if (strlen(input) >= 100) {
      printf("Input length passes the limit of 100 characters.\n");
      continue;
    }

    result = eval(input);
    printf("< %f\n", result);
  }

  return 0;
}

double eval(char *input) {
  LexerResult res = lexer_lex(input);
  printf("%s\n", res.tokens[0].lexeme);

  return 0;
}
