#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "chunk.h"

// it will hold the chunk, but won't free it, because the caller when receiving it
// when calling 'parse' will get the responsibility of freeing it.
typedef struct {
    lexer_t lexer;
    chunk_t chunk;
} parser_t;

parser_t new_parser(char *source);
chunk_t parse(parser_t *p);

#endif
