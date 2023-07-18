#include "lexer.h"

Token new_token(TokenType type, char lexeme[100], double value, int pos) {
  Token t;

  t.type = type;
  strcpy(t.lexeme, lexeme);
  t.value = value;
  t.pos = pos;

  return t;
}

Token end_token(int pos) {
  return new_token(End, "", 0, pos);
}
