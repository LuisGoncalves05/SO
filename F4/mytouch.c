#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <utime.h>
#include <time.h>
#include <sys/stat.h>


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (access(argv[1], F_OK) != -1) {
        int file = open(argv[1], O_RDONLY);
        if (file == -1) {
            fprintf(stderr, "NO MORE MEMORY BRO but i said it was fine\n");
            exit(EXIT_FAILURE);
        }
        time_t rawtime;
        time(&rawtime);
        struct utimbuf times;
        times.actime = rawtime;
        times.modtime = rawtime;
        int res = utime(argv[1], &times);
        if (res == -1) {
            fprintf(stderr, "%s: couldn't set time\n", argv[0]);
            close(file);
            exit(EXIT_FAILURE);
        }
        close(file);
    } else {
        int file = open(argv[1], O_CREAT | O_WRONLY, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
        if (file == -1) {
            fprintf(stderr, "NO MORE MEMORY BRO but i created it\n");
            exit(EXIT_FAILURE);
        }
        time_t rawtime;
        time(&rawtime);
        struct utimbuf times;
        times.actime = rawtime;
        times.modtime = rawtime;
        int res = utime(argv[1], &times);
        if (res == -1) {
            fprintf(stderr, "%s: couldn't set time\n", argv[0]);
            close(file);
            exit(EXIT_FAILURE);
        }
        close(file);
    }
    exit(EXIT_SUCCESS);
}