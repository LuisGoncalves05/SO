#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[0], "r");
    if (file == NULL) {
        exit(EXIT_FAILURE);
    }

    char *buffer[BUFFER_SIZE];
    size_t nchars;
    do {
        nchars = fread(buffer, sizeof(char), BUFFER_SIZE, file);
    } while (nchars);

    fclose(file);
    exit(EXIT_SUCCESS);
}