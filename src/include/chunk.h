#include <inttypes.h>

typedef struct {
    uint8_t *code;
    uintptr_t len;
    uintptr_t cap;
} chunk_t;

chunk_t new_chunk();
void free_chunk(chunk_t *c);

void write_chunk(chunk_t *c, uint8_t element);
