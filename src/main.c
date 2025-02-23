#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "token.h"
#include "parser.h"
#include "util.h"

static void repl();

int main(void) {
    repl();
}

static void repl() {
    printf("Math Interpreter C\n");
    printf("Write 'exit' to exit.\n");

    for (;;) {
        char *expr = input("> ");

        if (strcmp(expr, "exit") == 0) {
            free(expr);
            return;
        }
        else if (strcmp(expr, "") == 0)
            continue;

        parser_t parser = new_parser(expr);
        float64_t res = parse(&parser);

        if (!isnan(res))
            pretty_print(res);
        
        free(expr);
    }
}
