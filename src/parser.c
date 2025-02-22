#include "lexer.h"
#include "parser.h"
#include "chunk.h"

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

typedef double float64_t;

static float64_t term(parser_t *p);
static float64_t factor(parser_t *p);

static void advance(parser_t *p);
static bool match(parser_t *p, tokentype_t type);

parser_t new_parser(char *source) {
    lexer_t l = new_lexer(source);
    return (parser_t) {
        .lexer = l,
        .chunk = new_chunk(),
        .current = next_token(&l),
    };
}

float64_t parse(parser_t *p) {
    float64_t res = term(p);

    while (p->current.type == TK_PLUS || p->current.type == TK_MINUS) {
        tokentype_t op = p->current.type;
        advance(p);

        float64_t right = term(p);
        res = (op == TK_PLUS)
            ? res + right
            : res - right;
    }

    return res;
}

static float64_t term(parser_t *p) {
    float64_t res = factor(p);

    while (p->current.type == TK_STAR || p->current.type == TK_SLASH) {
        tokentype_t op = p->current.type;
        advance(p);
        
        float64_t right = factor(p);
        res = (op == TK_PLUS)
            ? res * right
            : res / right;
    }

    return res;
}

static float64_t factor(parser_t *p) {
    switch (p->current.type) {
        case TK_NUMBER: {
            char *buffer = (char *)malloc(p->current.len + 1);

            if (buffer == NULL)
                exit(1);
            
            memcpy(buffer, p->current.pos, p->current.len);
            buffer[p->current.len] = '\0';

            float64_t value = atof(buffer);
            free(buffer);

            advance(p);
        }

        case TK_LPAREN: {
            advance(p);
            float64_t inside = parse(p);

        }

        default: {
            // TODO: handle error
        }
    }
}

// ---

static void advance(parser_t *p) {
    p->current = next_token(&p->lexer);
}

static bool match(parser_t *p, tokentype_t type) {
    advance(p);
    return p->current.type == type;
}
