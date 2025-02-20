#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct {
    lexer_t lexer;
} parser_t;

parser_t new_parser(char *source);

#endif
