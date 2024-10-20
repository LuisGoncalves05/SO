#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int find_len;
    int replace_len;
    char *find;
    char *replace;
} pair;

typedef struct {
    int index_start;
    int index_end;
    char *word_to_add;
    int word_len;
} change;

#define BUFFER_SIZE 1024

void substitute (char** line, ssize_t* line_size, const pair to_substitute) {
    const int find_len = to_substitute.find_len;
    const int replace_len = to_substitute.replace_len;
    const char *find = to_substitute.find;
    char *replace = to_substitute.replace;

    int changes_len = 0;
    change* changes = malloc(BUFFER_SIZE * sizeof(change));

    int find_idx = 0;

    for (int line_idx = 0; line_idx < *line_size; line_idx++) {
        if (find_idx == find_len) {
            change to_replace;
            to_replace.index_start = line_idx - find_len;
            to_replace.index_end = line_idx;
            to_replace.word_to_add = replace;
            to_replace.word_len = replace_len;
            changes[changes_len] = to_replace;
            changes_len++;
            find_idx = 0;
        }
        if ((*line)[line_idx] == find[find_idx]) {
            find_idx++;
        }
    }

    int line_index = 0;
    char* new_line = malloc(BUFFER_SIZE);

    int new_line_index = 0;

    int changes_index = 0;

    while (changes_index < changes_len) {
        change current = changes[changes_index];
        while (line_index < current.index_start) {
            new_line[new_line_index] = (*line)[line_index];
            new_line_index++;
            line_index++;
        }
        for (int i = 0; i < current.word_len; i++) {
            new_line[new_line_index] = current.word_to_add[i];
            new_line_index++;
        }
        changes_index++;
        line_index = current.index_end;
    }
    while (line_index <= *line_size) {
        new_line[new_line_index] = (*line)[line_index];
        new_line_index++;
        line_index++;
    }

    free(changes);
    free(*line);
    *line = new_line;
    *line_size = line_index;
}

int main (const int argc, char **argv) {
    pair words[argc-1];
    for (int i = 1; i < argc; i++) {
        int index = 0;
        int replace_index = -1;
        char current;
        pair result;
        result.find_len = -1;

        while ((current = argv[i][index]) != '\0') {
            if (current == '-') {
                result.find_len = index;
                replace_index = index+1;
            }
            index++;
        }

        if (result.find_len == -1) {
            printf("No - found, exiting.");
            exit(EXIT_FAILURE);
        }

        result.replace_len = index - 1 - result.find_len;
        result.find = argv[i];
        result.replace = argv[i] + replace_index;

        words[i-1] = result;
    }

    char *line = NULL;
    char **endline = &line;
    size_t buffer_allocated = 0;
    ssize_t nchars;
    while ((nchars = getline(&line, &buffer_allocated, stdin)) != -1) {
        for (int words_index = 0; words_index < argc - 1; words_index++) {
            substitute(endline, &nchars, words[words_index]);
        }
        printf("%s", *endline);
    }
    free(*endline);
}