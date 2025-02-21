#include "lexer.h"
#include "parser.h"
#include "chunk.h"

parser_t new_parser(char *source) {
    return (parser_t) {
        .lexer = new_lexer(source),
        .chunk = new_chunk(),
    };
}

chunk_t parse(parser_t *p) {

}
