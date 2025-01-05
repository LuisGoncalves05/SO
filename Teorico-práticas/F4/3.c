#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char* argv[]) {
    struct stat info;
    if (argc < 2) {
        fprintf(stderr, "usage: %s file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    size_t size = 0;
    size_t blocks = 0;

    for (int i = 1; i < argc; i++) {
        int retv = stat(argv[i], &info);
        if (retv == -1) {
            fprintf(stderr, "fsize: Can't stat %s\n", argv[1]);
            exit(EXIT_FAILURE);
        }
        size += info.st_size;
        blocks += info.st_blocks;
        char* time = ctime(&info.st_atime);
        time[strlen(time) - 1] = 0;
        printf("Last modified: %s, UID: %u\n", time, info.st_uid);
    }

    printf("Size: %d bytes, disk_blocks: %d\n", (int)size, (int)blocks);
    exit(EXIT_SUCCESS);
}