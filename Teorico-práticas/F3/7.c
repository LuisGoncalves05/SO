#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char opt;
    /*
    c-001
    w-010
    l-100
    */
    unsigned mode = 0;

    while ((opt = getopt(argc, argv, "cwl")) != -1) {
        switch (opt) {
        case 'c':
            mode |= 1;
            break;
        case 'w':
            mode |= 2;
            break;
        case 'l':
            mode |= 4;
            break;
        default: /* '?' */
            fprintf(stderr, "Usage: %s [-c|-w|-l] filename\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (optind == 1 || optind != argc - 1) {
        fprintf(stderr, "Usage: %s [-c|-w|-l] filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE* file = fopen(argv[optind], "r");
    int chars = 0, words = 0, lines = 0;

    size_t buff_size;
    char* buffer = NULL;
    ssize_t read_chars;
    while ((read_chars = getline(&buffer, &buff_size, file)) != -1) {
        lines++;
        chars += read_chars;

        char* text = strdup(buffer);
        char* word;
        while ((word = strsep(&text, " \t"))) {
            if (*word == '\0') continue;
            words++;
        }
    }

    if (mode % 2) printf("%u ", chars);
    if ((mode >> 1) % 2) printf("%u ", words);
    if ((mode >> 2) % 2) printf("%u ", lines);
    printf("\n");

    fclose(file);
    exit(EXIT_SUCCESS);
}
