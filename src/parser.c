#include "lexer.h"
#include "parser.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include <math.h>

#define IS_OPERATOR(op) (((op) == TK_PLUS) || ((op) == TK_MINUS) || ((op) == TK_STAR) || ((op) == TK_SLASH) || ((op) == TK_END) || ((op) == TK_RPAREN))

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
    float64_t result = term(p);

    if (isnan(result))
        return NAN;

    while (p->current.type == TK_PLUS || p->current.type == TK_MINUS) {
        token_t op = p->current;
        advance(p);

        float64_t right = term(p);

        if (isnan(right))
            return NAN;

        if (op.type == TK_PLUS)
            result += right;
        else if (op.type == TK_MINUS)
            result -= right;
    }

    if (!IS_OPERATOR(p->current.type)) {
        error(p->current.offset, "Invalid operator. Expected one of these: (+ - * /)");
        return NAN;
    }

    return result;
}

static float64_t term(parser_t *p) {
    float64_t result = factor(p);

    if (isnan(result))
        return NAN;

    while (p->current.type == TK_STAR || p->current.type == TK_SLASH) {
        token_t op = p->current;
        advance(p);

        float64_t right = factor(p);

        if (isnan(right))
            return NAN;

        if (op.type == TK_STAR)
            result *= right;
        else if (op.type == TK_SLASH) {
            if (right == 0) {
                error(op.offset, "Cannot divide by zero.");
                return NAN;
            }

            result /= right;
        }
    }

    if (!IS_OPERATOR(p->current.type)) {
        error(p->current.offset, "Invalid operator. Expected one of these: ('+', '-', '*', '/').");
        return NAN;
    }

    return result;
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

            if (isnan(inside))
                return NAN;

            if (!match(p, TK_RPAREN)) {
                error(p->current.offset, "Missing ')' at end of expression.");
                return NAN;
            }

            return inside;
        }

        case TK_MINUS: {
            advance(p); // '-'
            float64_t operand = factor(p);

            if (isnan(operand))
                return NAN;

            return -operand;
        }

        default: {
            error(p->current.offset, "Unexpected token. Expected number or '-'.");
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
