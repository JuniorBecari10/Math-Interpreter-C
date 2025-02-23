#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <inttypes.h>
#include <string.h>

#define INITIAL_SIZE 64

typedef double float64_t;

char *input(const char *prompt) {
    printf("%s", prompt); // Print the prompt

    size_t size = INITIAL_SIZE;
    char *buffer = malloc(size);
    if (!buffer) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    size_t len = 0;
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (len + 1 >= size) { // Resize if needed
            size *= 2;
            char *new_buffer = realloc(buffer, size);
            
            if (!new_buffer) {
                free(buffer);
                printf("Memory reallocation failed\n");
                exit(1);
            }

            buffer = new_buffer;
        }

        buffer[len++] = (char)c;
    }

    buffer[len] = '\0'; // Null-terminate the string
    return buffer;
}

float64_t parse_f64(char *str, size_t len) {
    char temp[len + 1];

    memcpy(temp, str, len);
    temp[len] = '\0';

    return strtod(temp, NULL);
}

void pretty_print(float64_t num) {
    if (num == (int64_t)num) {
        printf("< %ld\n", (int64_t)num);
    } else {
        printf("< %.2f\n", num);
    }
}
