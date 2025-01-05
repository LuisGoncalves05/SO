#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 2048

int main(int argc, char** argv) {
    if (argc != 3) {
        perror("Usage: ./a.out file_src file_dst");
        exit(EXIT_FAILURE);
    }

    FILE* file_src = fopen(argv[1], "r");
    FILE* file_dst = fopen(argv[2], "w");

    char buffer[BUFFER_SIZE];
    size_t nchars;
    while ((nchars = fread(buffer, sizeof(char), BUFFER_SIZE, file_src))) {
        fwrite(buffer, sizeof(char), nchars, file_dst);
    }

    fclose(file_src);
    fclose(file_dst);
}