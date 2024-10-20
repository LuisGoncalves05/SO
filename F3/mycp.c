#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 2048

int main(int argc, char *argv[]) {
    if (argc != 3) {
        exit(EXIT_FAILURE);
    }
    FILE* file_read = fopen(argv[1], "r");
    FILE* file_write = fopen(argv[2], "w");

    if (!(file_read && file_write)) exit(EXIT_FAILURE);

    size_t read_len;
    do {
        char *line[BUFFER_SIZE];
        read_len = fread(line, sizeof(char), BUFFER_SIZE, file_read);
        fwrite(line, sizeof(char), read_len, file_write);
    } while (read_len);

    fclose(file_read);
    fclose(file_write);

    exit(EXIT_SUCCESS);
}