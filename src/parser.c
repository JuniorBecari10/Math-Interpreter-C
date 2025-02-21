#include "lexer.h"
#include "parser.h"
#include "chunk.h"

parser_t new_parser(char *source) {
    return (parser_t) {
        .lexer = new_lexer(source),
    };
}

void free_parser(parser_t *p) {
    free_chunk(&p->chunk);
}
