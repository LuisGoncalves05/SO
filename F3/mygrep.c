#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(const int argc, char** argv) {
    if (argc != 3) {
        exit(EXIT_FAILURE);
    }

    FILE* file = fopen(argv[2], "r");
    size_t line_buffer_size = 0;
    ssize_t line_size;
    char* line = NULL;
    size_t line_num = 0;
    const char* string = argv[1];
    const size_t string_length = strlen(string);

    int string_index = 0;
    int appearances = 0;
    int allocated_appearances = BUFFER_SIZE / sizeof(int);
    int* lines = malloc(BUFFER_SIZE);
    int* columns = malloc(BUFFER_SIZE);

    while ((line_size = getline(&line, &line_buffer_size, file)) != -1) {
        line_num++;
        if (appearances < allocated_appearances) {
            for (int column = 0; column < line_size - 1; column++) {
                if (line[column] == string[string_index]) {
                    string_index++;
                } else {
                    string_index = 0;
                }
                if (string_index == string_length) {
                    lines[appearances] = line_num;
                    columns[appearances] = column - string_length + 2;
                    appearances++;
                }
            }
        } else {
            const int new_buffer_size = 2*(allocated_appearances * sizeof(int));
            allocated_appearances *= 2;
            int* temp = malloc(new_buffer_size);
            memcpy(temp, lines, allocated_appearances * sizeof(int));
            free(lines);
            lines = temp;
            temp = malloc(new_buffer_size);
            memcpy(temp, columns, allocated_appearances * sizeof(int));
            free(columns);
            columns = temp;
        }
    }

    printf("[");
    if (appearances) {
        printf("%d:%d", lines[0], columns[0]);
    }
    for (int index = 1; index < appearances; index++) {
        printf(", %d:%d", lines[index], columns[index]);
    }
    printf("]\n");

    free(lines);
    free(columns);
}