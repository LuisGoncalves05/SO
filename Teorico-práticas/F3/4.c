#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char** argv) {
    if (argc < 2) {
        perror("Usage: ./a.out filename1 filename2 ... filenamen");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        FILE* file = fopen(argv[i], "r");
        char buffer[BUFFER_SIZE];
        int nchars;
        while ((nchars = fread(buffer, sizeof(char), BUFFER_SIZE, file))) {
            fwrite(buffer, sizeof(char), nchars, stdout);
        }
        fclose(file);
    }

}