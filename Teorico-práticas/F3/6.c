#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    /* open file, exit on error */
    FILE* file = fopen(argv[1], "r");
    if ( file == NULL ) {
        printf("error: could not open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    /* read file, line by line */
    ssize_t read;
    size_t size = 0;
    char* line = NULL;
    int lineno = 1;
    while ((read = getline(&line, &size, file)) != -1) {
        printf("[%5d]: %s", lineno, line);
        lineno++;
    }
    /* free line */
    free(line);
    /* close file */
    fclose(file);
    /* return gracefully */
    exit(EXIT_SUCCESS);
}
