#include "token.h"
#include <stdio.h>

token_t error_token(const char *message) {
    return (token_t) {
        .pos = message,
        .len = 0,
        .offset = 0,
        .type = TK_ERROR,
    };
}

token_t end_token() {
    return (token_t) {
        .pos = NULL,
        .len = 0,
        .offset = 0,
        .type = TK_END,
    };
}
