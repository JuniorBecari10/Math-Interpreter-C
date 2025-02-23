#include "lexer.h"
#include "token.h"

#include <ctype.h>
#include <string.h>
#include <inttypes.h>

static token_t number(lexer_t *l);
static void skip_whitespace(lexer_t *l);
static char peek(lexer_t *l, uint32_t offset);
static char advance(lexer_t *l);
static token_t new_token(lexer_t *l, tokentype_t type);
static token_t error_token(lexer_t *l, char *message);
static token_t end_token();

lexer_t new_lexer(char *source) {
    return (lexer_t) {
        .source = source,

        .start = source,
        .current = source,

        .len = strlen(source),
    };
}
token_t next_token(lexer_t *l) {
    skip_whitespace(l);
    l->start = l->current;

    char c = advance(l);

    #define TOKEN(tk) return tk; break;
    
    switch (c) {
        case '\0': TOKEN(end_token());

        case '+': TOKEN(new_token(l, TK_PLUS));
        case '-': TOKEN(new_token(l, TK_MINUS));
        case '*': TOKEN(new_token(l, TK_STAR));
        case '/': TOKEN(new_token(l, TK_SLASH));

        case '(': TOKEN(new_token(l, TK_LPAREN));
        case ')': TOKEN(new_token(l, TK_RPAREN));

        default: {
            if (isdigit(c))
                return number(l);
            
            return error_token(l, "Unknown character.");
        }
    }

    #undef TOKEN
}

static token_t number(lexer_t *l) {
    while (isdigit(peek(l, 0)))
        advance(l);
    
    if (peek(l, 0) == '.' && isdigit(peek(l, 1))) {
        advance(l);

        while (isdigit(peek(l, 0)))
            advance(l);
    }

    return new_token(l, TK_NUMBER);
}

static void skip_whitespace(lexer_t *l) {
    while (isspace(peek(l, 0)))
        advance(l);
}

static char peek(lexer_t *l, uint32_t offset) {
    if (l->current + offset >= l->source + l->len)
        return '\0';
    else
        return *(l->current + offset);
}

static char advance(lexer_t *l) {
    if (l->current >= l->source + l->len)
        return '\0';
    else
        return *(l->current++);
}

static token_t new_token(lexer_t *l, tokentype_t type) {
    return (token_t) {
        .pos = l->start,
        .len = l->current - l->start,
        .offset = l->start - l->source,
        .type= type,
    };
}

// 'len' does not reflect the length of the message.
static token_t error_token(lexer_t *l, char *message) {
    return (token_t) {
        .pos = message,
        .len = 0,
        .offset = l->start - l->source,
        .type = TK_ERROR,
    };
}

static token_t end_token() {
    return (token_t) {
        .pos = NULL,
        .len = 0,
        .offset = 0,
        .type = TK_END,
    };
}
