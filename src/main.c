#include <stdio.h>

#include "token.h"
#include "parser.h"

int main(void) {
    char *source = "1.45 + 1.4";
    parser_t parser = new_parser(source);
    chunk_t chunk = parse(&parser);

    free_chunk(&chunk);
}

static void repl() {

}
