#include <stdio.h>
#include <float.h>

#include "lexer.h"
#include "token.h"

Lexer new_lexer(char input[100]) {
  Lexer l;

  strcpy(l.input, input);
  l.input_len = strlen(input);
  l.cursor = 0;
  l.had_error = false;

  l.advance = lexer_advance;
  l.is_at_end = lexer_is_at_end;
  l.prev_is_at_end = lexer_prev_is_at_end;
  l.prev = lexer_prev;
  l.ch = lexer_ch;
  l.skip_whitespace = lexer_skip_whitespace;
  l.next_token = lexer_next_token;
  l.report_error = lexer_report_error;

  return l;
}

void lexer_advance(Lexer *self) {
  self->cursor++;
}

bool lexer_is_at_end(Lexer *self) {
  return self->cursor >= self->input_len;
}

bool lexer_prev_is_at_end(Lexer *self) {
  return self->cursor > self->input_len;
}

char lexer_prev(Lexer *self) {
  if (self->prev_is_at_end(self)) return 0;

  return self->input[self->cursor - 1];
}

char lexer_ch(Lexer *self) {
  if (self->is_at_end(self)) return 0;

  return self->input[self->cursor];
}

void lexer_skip_whitespace(Lexer *self) {
  while (self->ch(self) == ' ') self->advance(self);
}

Token lexer_next_token(Lexer *self) {
  self->skip_whitespace(self);

  if (self->is_at_end(self)) return end_token(self->cursor);

  TokenType type = Never;

  switch (self->ch(self)) {
    case '+': type = Plus; break;
    case '-': type = Minus; break;
    case '*': type = Star; break;
    case '/': type = Slash; break;

    case '(': type = LParen; break;
    case ')': type = RParen; break;
  }

  if (type == Never) {
    if (is_number(self->ch(self))) {
      int pos = self->cursor;
      self->advance(self);

      while (is_number(self->ch(self))) self->advance(self);

      char lexeme[100];
      slice(self->input, lexeme, pos, self->cursor);

      double res = DBL_MAX;
      sscanf(lexeme, "%lf", &res);

      if (res == DBL_MAX) {
        self->report_error(self, "Couldn't parse number.", self->input, pos);
      }

      return new_token(Number, lexeme, res, pos);
    }

    // type is still never
    self->report_error(self, "Couldn't identify token.", self->input, self->cursor);
    type = Error;
  }

  self->advance(self);

  char s[2] = { self->prev(self), '\0' };
  return new_token(type, s, 0, self->cursor - 1);
}

void lexer_report_error(Lexer *self, char *msg, char *code, int pos) {
  self->had_error = true;

  printf("\nError: %s\n", msg);
  printf(" %s\n", code);

  for (int i = 0; i <= pos; i++) {
    printf(" ");
  }

  printf("^\n");
}

// Helper

bool is_number(char c) {
  return (c >= '0' && c <= '9') || c == '.';
}

void slice(const char* str, char* result, size_t start, size_t end)
{
    strncpy(result, str + start, end - start);
}

// Global

LexerResult lexer_lex(char *input) {
  Lexer l = new_lexer(input);
  Token tokens[100];
  Token tk = l.next_token(&l);
  int cursor = 0;

  while (tk.type != End) {
    tokens[cursor] = tk;
    cursor++;
    tk = l.next_token(&l);
  }

  LexerResult res;
  memcpy(res.tokens, tokens, sizeof(Token));
  res.had_error = l.had_error;

  return res;
}
