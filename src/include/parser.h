#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "chunk.h"

typedef struct {
    lexer_t lexer;
    chunk_t chunk;
} parser_t;

parser_t new_parser(char *source);
void free_parser(parser_t *p);

#endif
