#include <ctype.h>
#include <string.h>
#include <stdio.h>


int main(int argc, char *argv[]) {
    if (argc == 2) {
        size_t size = strlen(argv[1]);
        for (size_t i = 0; i < size; i++) {
            argv[1][i] = tolower(argv[1][i]);
        }
        printf("%s", argv[1]);
    } else if (argc == 3) {
        int res = 0;
        char* result = strstr(argv[1], argv[2]);
        while (result) {
            result = strstr(result+1, argv[2]);
            res++;
        }
        printf("%d\n", res);
    } else {
        return -1;
    }
}
