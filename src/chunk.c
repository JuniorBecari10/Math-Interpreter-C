#include "chunk.h"

#include <stdio.h>

#define GROW_FACTOR 2
#define INITIAL_CAP 10

chunk_t new_chunk() {
    return (chunk_t) {
        .code = malloc(INITIAL_CAP * sizeof(uint8_t)),
        .len = 0,
        .cap = INITIAL_CAP,
    };
}

void free_chunk(chunk_t *c) {
    free(c->code);
    
    c->code = NULL;
    c->len = 0;
    c->cap = 0;
}

void write_chunk(chunk_t *c, uint8_t element) {
    if (c->cap < c->len + 1) {
        uintptr_t new_cap = c->cap * GROW_FACTOR;
        
        c->code = realloc(new_cap);
        c->cap = new_cap;
    }

    c->code[c->len++] = element;
}

#undef GROW_FACTOR
#undef INITIAL_CAP
