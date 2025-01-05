#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int count = 0;
    char* text = strdup(argv[1]);
    char* word;
    while ((word = strsep(&text, " \t")) != NULL) {
        if (*word == '\0') /* skip multiple occurrences of delimiter */
            continue;
        printf("%s\n", word);
        count++;
    }
    printf("%d words found\n", count);
    exit(EXIT_SUCCESS);
}