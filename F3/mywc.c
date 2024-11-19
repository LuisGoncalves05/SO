#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        exit(EXIT_FAILURE);
    }

    const char mode = argv[1][1];

    FILE *file = fopen(argv[2], "r");
    if (file == NULL) {
        exit(EXIT_FAILURE);
    }

    size_t chars = 0, lines = 0, words = 0, buffer_size = 0;
    ssize_t nchars = 0;
    char *buffer = NULL;
    while (-1 != (nchars = getline(&buffer, &buffer_size, file))) {
        for (size_t i = 0; i < nchars; i++) {
            if (i > 0 &&
               (buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t') &&
               (buffer[i-1] != ' ' && buffer[i-1] != '\n' && buffer[i-1] != '\t')) {
                words++;
               }
            if (buffer[i] == '\n') {
                lines++;
            }
        }
        chars += nchars;
    }
    free(buffer);

    if (mode == 'c') {
        printf("%lu\n", chars);
    } else if (mode == 'w') {
        printf("%lu\n", words);
    } else if (mode == 'l') {
        printf("%lu\n", lines);
    }

    fclose(file);
    exit(EXIT_SUCCESS);
}
