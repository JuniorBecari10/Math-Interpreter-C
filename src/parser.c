#include "lexer.h"
#include "parser.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include <math.h>

#define IS_OPERATOR(op) (((op) == TK_PLUS) || ((op) == TK_MINUS) || ((op) == TK_STAR) || ((op) == TK_SLASH) || ((op) == TK_END))

#define EXPR(next_fn, tk_1, tk_2, op_1, op_2) \
    do {\
        float64_t res = next_fn(p);\
        if (isnan(res)) return NAN;\
\
        token_t op = p->current;\
        while (p->current.type == tk_1 || p->current.type == tk_2) {\
            advance(p);\
\
            float64_t right = next_fn(p);\
            if (isnan(right)) return NAN;\
\
            if (strcmp(#op_2, "/") == 0 && right == 0) {\
                error(op.offset, "Cannot divide by zero.");\
                return NAN;\
            }\
\
            res = (op.type == tk_1)\
                ? res op_1 right\
                : res op_2 right;\
        }\
\
        if (!IS_OPERATOR(op.type)) {\
            error(op.offset, "Unknown operator.");\
            return NAN;\
        }\
\
        return res;\
    } while (false)

typedef double float64_t;

static float64_t term(parser_t *p);
static float64_t factor(parser_t *p);

static void advance(parser_t *p);
static bool match(parser_t *p, tokentype_t type);
static void error(size_t offset, const char* message);

parser_t new_parser(char *source) {
    lexer_t l = new_lexer(source);
    return (parser_t) {
        .lexer = l,
        .current = next_token(&l),
    };
}

float64_t parse(parser_t *p) {
    EXPR(term, TK_PLUS, TK_MINUS, +, -);
}

static float64_t term(parser_t *p) {
    EXPR(factor, TK_STAR, TK_SLASH, *, /);
}

static float64_t factor(parser_t *p) {
    switch (p->current.type) {
        case TK_NUMBER: {
            float64_t value = parse_f64(p->current.pos, p->current.len);
            advance(p);

            return value;
        }

        case TK_LPAREN: {
            advance(p); // '('
            float64_t inside = parse(p);

            if (!match(p, TK_RPAREN)) {
                error(p->current.offset, "Missing ')' at end of expression.");
                return NAN;
            }

            return inside;
        }

        case TK_MINUS: {
            advance(p); // '-'
            float64_t operand = factor(p);

            return -operand;
        }

        default: {
            error(p->current.offset, "Unknown token.");
            return NAN;
        }
    }
}

// ---

static void advance(parser_t *p) {
    p->current = next_token(&p->lexer);
}

static bool match(parser_t *p, tokentype_t type) {
    bool res = p->current.type == type;
    advance(p);

    return res;
}

static void error(size_t offset, const char* message) {
    for (uint32_t i = 0; i < offset + 2; i++)
        putc(' ', stdout);
    
    putc('^', stdout);
    printf(" %s\n", message);
}
