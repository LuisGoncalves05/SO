#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
    struct stat information;
    long byte_total = 0;
    long block_total = 0;
    if (argc < 2) {
        printf("No files given\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < argc; i++) {
        if (stat(argv[i], &information) == -1) {
            printf("Couldn't retrieve information\n");
            exit(EXIT_FAILURE);
        }
        byte_total += information.st_size;
        block_total += information.st_blocks;
        printf("Size: %li\nDisk blocks: %li\nLast Change: %sUID: %i\n",
            information.st_size, information.st_blocks, ctime(&information.st_atime), information.st_uid);
    }
    printf("\nByte total: %li\nBlock Total: %li\n", byte_total, block_total);
}