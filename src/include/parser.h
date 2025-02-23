#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "lexer.h"

typedef double float64_t;

typedef struct {
    lexer_t lexer;
    token_t current;
} parser_t;

parser_t new_parser(char *source);
float64_t parse(parser_t *p);

#endif
