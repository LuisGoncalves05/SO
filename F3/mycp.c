#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 2048

int main(int argc, char *argv[]) {
    if (argc != 2) {
        exit(EXIT_FAILURE);
    }
    FILE* file_read = fopen(argv[1], "r");
    FILE* file_write = fopen(argv[2], "wc");

    if (!(file_read && file_write)) exit(EXIT_FAILURE);

    size_t read_len;
    char *line = (char*)malloc(BUFFER_SIZE);
    read_len = fread(line, sizeof(char), BUFFER_SIZE, file_read);
    fwrite(line, sizeof(char), read_len, file_write);

    fclose(file_read);
    fclose(file_write);

    exit(EXIT_SUCCESS);
}