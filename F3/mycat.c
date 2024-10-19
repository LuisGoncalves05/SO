#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            exit(EXIT_FAILURE);
        }

        char *buffer[BUFFER_SIZE];
        size_t nchars;
        do {
            nchars = fread(buffer, sizeof(char), BUFFER_SIZE, file);
            fwrite(buffer, sizeof(char), nchars, stdout);
        } while (nchars);

        fclose(file);
    }
    exit(EXIT_SUCCESS);
}