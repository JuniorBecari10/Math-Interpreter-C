#ifndef TOKEN_H
#define TOKEN_H

#include <stddef.h>

typedef enum {
    TK_NUMBER,

    TK_PLUS,
    TK_MINUS,
    TK_STAR,
    TK_SLASH,

    TK_LPAREN,
    TK_RPAREN,

    TK_ERROR,
    TK_END,
} tokentype_t;

typedef struct {
    char *pos;
    size_t len;
    size_t offset;

    tokentype_t type;
} token_t;

#endif
