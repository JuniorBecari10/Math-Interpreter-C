#ifndef TOKEN_H
#define TOKEN_H

#include <inttypes.h>

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
    uint32_t len;
    uint32_t offset;

    tokentype_t type;
} token_t;

#endif
