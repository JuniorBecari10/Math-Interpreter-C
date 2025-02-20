#include "lexer.h"
#include "parser.h"

parser_t new_parser(char *source) {
    return (parser_t) {
        .lexer = new_lexer(source),
    };
}