#ifndef TOKEN_H
#define TOKEN_H

#include <string.h>

typedef enum {
  Number,
  Never,
  Error,
  End,

  Plus,
  Minus,
  Star,
  Slash,

  LParen,
  RParen
} TokenType;

typedef struct {
  TokenType type;
  char lexeme[100];
  double value;
  int pos;
} Token;

Token new_token(TokenType type, char lexeme[100], double value, int pos);
Token end_token(int pos);

#endif
