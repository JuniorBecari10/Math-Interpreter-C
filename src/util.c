#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <inttypes.h>
#include <string.h>

#define INITIAL_SIZE 64

typedef double float64_t;

char *input(const char *prompt) {
    printf("%s", prompt);

    size_t size = INITIAL_SIZE;
    char *buffer = malloc(size);

    if (buffer == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }

    // Read the stdin character by character until the first '\n', placing them in the heap,
    // and reallocating the buffer if needed.
    size_t len = 0;
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (len + 1 >= size) {
            size *= 2;
            char *new_buffer = realloc(buffer, size);
            
            if (new_buffer == NULL) {
                free(buffer);
                perror("Memory reallocation failed");
                exit(1);
            }

            buffer = new_buffer;
        }

        buffer[len++] = (char)c;
    }

    buffer[len] = '\0';
    return buffer;
}

float64_t parse_f64(char *str, size_t len) {
    char *temp = malloc(len + 1);

    if (temp == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }

    memcpy(temp, str, len);
    temp[len] = '\0';

    float64_t res = strtod(temp, NULL);

    free(temp);
    return res;
}

void pretty_print(float64_t num) {
    if (num == (int64_t)num) {
        printf("< %ld\n", (int64_t)num);
    } else {
        printf("< %.15g\n", num);
    }
}
