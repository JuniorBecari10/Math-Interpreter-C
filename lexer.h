#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>

#include "token.h"

typedef struct {
  Token tokens[100];
  bool had_error;
} LexerResult;

typedef struct Lexer {
  char input[100];
  int input_len;
  int cursor;

  bool had_error;

  // methods

  void (*advance)(struct Lexer*);
  bool (*is_at_end)(struct Lexer*);
  bool (*prev_is_at_end)(struct Lexer*);
  char (*prev)(struct Lexer*);
  char (*ch)(struct Lexer*);
  void (*skip_whitespace)(struct Lexer*);
  Token (*next_token)(struct Lexer*);
  void (*report_error)(struct Lexer*, char*, char*, int);
} Lexer;

Lexer new_lexer(char input[100]);

void lexer_advance(Lexer *self);
bool lexer_is_at_end(Lexer *self);
bool lexer_prev_is_at_end(Lexer *self);
char lexer_prev(Lexer *self);
char lexer_ch(Lexer *self);
void lexer_skip_whitespace(Lexer *self);
Token lexer_next_token(Lexer *self);
void lexer_report_error(Lexer *self, char *msg, char *code, int pos);

bool is_number(char c);
void slice(const char* str, char* result, size_t start, size_t end);

LexerResult lexer_lex(char *input);

#endif
