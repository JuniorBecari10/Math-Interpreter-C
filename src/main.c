#include <stdio.h>

#include "token.h"
#include "lexer.h"

int main(void) {
    char *source = "1.45 + 1.4";
    lexer_t lexer = new_lexer(source);

    for (token_t tk = next_token(&lexer); tk.type != TK_END; tk = next_token(&lexer)) {
        printf("%.*s\n", tk.len, tk.pos);
    }
}

static void repl() {

}
