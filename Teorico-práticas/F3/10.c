#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024


typedef struct {
    int find_len;
    int replace_len;
    char* find;
    char* replace;
} pair_find_replace;

typedef struct {
    int idx_start;      //inclusive
    int idx_end;        //exclusive
    char* word_to_add;
    int word_len;
} change;


void substitute (char** line, size_t* line_size, const pair_find_replace to_substitute);
void* double_array (void* array, size_t element_size, size_t* max_items);


int main (const int argc, char **argv) {
    pair_find_replace replacement_pairs[argc -1];

    for (int argv_idx = 1; argv_idx < argc; argv_idx++) {
        int letter_idx = 0;
        int replace_idx = -1;
        char letter;
        pair_find_replace result;
        result.find_len = -1;

        do {
            letter = argv[argv_idx][letter_idx];
            if (letter == '-') {
                result.find_len = letter_idx;
                replace_idx = letter_idx+1;
            }
            letter_idx++;
        } while (letter != '\0');
        letter_idx--;

        if (result.find_len == -1) {
            printf("No - found, exiting.");
            exit(EXIT_FAILURE);
        }

        result.replace_len = letter_idx - replace_idx;
        result.find = argv[argv_idx];
        result.replace = argv[argv_idx] + replace_idx;

        replacement_pairs[argv_idx-1] = result;
    }

    char *line = NULL;

    char **substituted_line = &line;
    size_t buffer_allocated = 0;
    size_t chars_read = getline(&line, &buffer_allocated, stdin);
    while (chars_read != -1) {
        for (int replacement_pairs_idx = 0; replacement_pairs_idx < argc - 1; replacement_pairs_idx++) {
            substitute(substituted_line, &chars_read, replacement_pairs[replacement_pairs_idx]);
        }
        printf("%s", *substituted_line);
        chars_read = getline(&line, &buffer_allocated, stdin);
    }
    free(*substituted_line);
}

void* double_array (void* array, size_t element_size, size_t* max_items) {
    void* new_array = malloc(element_size * (*max_items) * 2);
    if (new_array == NULL || array == NULL) {
        if (new_array == NULL) {
            printf("Ran out of memory.");
        }
        if (array == NULL) {
            printf("No array to double.");
        }
        exit(EXIT_FAILURE);
    } 
    if (*max_items >= __SIZE_MAX__ / 2 + 1) {
        printf("18K PETABYTES MATE????.");
        exit(EXIT_FAILURE);
    }
    memcpy(new_array, array, (*max_items) * element_size);
    free(array);
    *max_items *= 2;
    return new_array;
}

void substitute (char** line_ptr, size_t* line_size, const pair_find_replace to_substitute) {
    const int   find_len    = to_substitute.find_len;
    const int   replace_len = to_substitute.replace_len;
    const char* find        = to_substitute.find;
    char*       replace     = to_substitute.replace;

    size_t   changes_len = 0;
    size_t   max_changes = BUFFER_SIZE;
    change*  changes     = (change*) malloc(max_changes * sizeof(change));
    if (changes == NULL) {
        printf("Ran out of memory.");
        exit(EXIT_FAILURE);
    }

    int find_idx = 0;

    for (int line_idx = 0; line_idx < *line_size; line_idx++) {

        if (find_idx == find_len) {
            change to_replace = {
                line_idx - find_len,    // idx_start (inclusive)
                line_idx,               // idx_end (exclusive)
                replace,                // word_to_add
                replace_len             // word_len
            };
            
            if (changes_len == max_changes) {
                changes = (change*) double_array((void*)changes, sizeof(change), &max_changes);
            }
            
            changes[changes_len] = to_replace;
            changes_len++;
            find_idx = 0;
        }

        if ((*line_ptr)[line_idx] == find[find_idx]) {
            find_idx++;
        }
    }

    int line_idx = 0;
    size_t new_line_max = BUFFER_SIZE;
    char* new_line = (char*)malloc(new_line_max * sizeof(char));
    if (new_line == NULL) {
        printf("Ran out of memory.");
        exit(EXIT_FAILURE);
    }
    int new_line_idx = 0;

    int changes_idx = 0;

    while (changes_idx < changes_len) {
        change current = changes[changes_idx];
        while (line_idx < current.idx_start) {
            if (new_line_idx == new_line_max) {
                new_line = (char*)double_array((void*)new_line, sizeof(char), &new_line_max);
            }
            new_line[new_line_idx] = (*line_ptr)[line_idx];
            new_line_idx++;
            line_idx++;
        }
        for (int i = 0; i < current.word_len; i++) {
            if (new_line_idx == new_line_max) {
                new_line = (char*)double_array((void*)new_line, sizeof(char), &new_line_max);
            }
            new_line[new_line_idx] = current.word_to_add[i];
            new_line_idx++;
        }
        changes_idx++;
        line_idx = current.idx_end;
    }
    while (line_idx <= *line_size) {
        if (new_line_idx == new_line_max) {
            new_line = (char*)double_array((void*)new_line, sizeof(char), &new_line_max);
        }
        new_line[new_line_idx] = (*line_ptr)[line_idx];
        new_line_idx++;
        line_idx++;
    }

    free(changes);
    free(*line_ptr);
    *line_ptr = new_line;
    *line_size = line_idx;
}