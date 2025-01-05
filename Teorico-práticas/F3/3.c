#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 2048

int main(int argc, char* argv[]) {
    FILE* file = fopen(argv[1], "r");
    if ( file == NULL ) {
        printf("error: could not open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    int nchars = fread(buffer, sizeof(char), BUFFER_SIZE, file);
    while (nchars > 0) {
        fwrite(buffer, sizeof(char), nchars, stdout);
        nchars = fread(buffer, sizeof(char), BUFFER_SIZE, file);
    }

    fclose(file);
    exit(EXIT_SUCCESS);
}
