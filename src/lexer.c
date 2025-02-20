#include "lexer.h"
#include "token.h"

#include <string.h>

lexer_t new_lexer(char *source) {
    return (lexer_t) {
        .source = source,
        .ptr = source,
        .len = strlen(source),
    };
}
token_t next_token(lexer_t *l) {
    char c = advance(l);
    
    switch (c) {
        case '\0':
            return end_token();
            break;

        
    }
}

static char advance(lexer_t *l) {
    if (l->ptr >= l->source + l->len)
        return '\0';
    else
        return *l->ptr++;
}

static token_t new_token(tokentype_t type) {
    
}
