#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <inttypes.h>

typedef struct {
    char *source;
    
    char *start;
    char *current;

    uintptr_t len;
} lexer_t;

lexer_t new_lexer(char *source);
token_t next_token(lexer_t *l);

#endif
