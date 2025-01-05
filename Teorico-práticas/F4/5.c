#include <stdio.h>
#include <sys/fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <utime.h>

int main(int argc, char* argv[]) {
    if (access(argv[1], F_OK) == 0) {
    /* file exists - insert code to change last access date */
        time_t timer;
        time(&timer);

        struct utimbuf times;
        times.actime = timer;
        times.modtime = timer;

        int res = utime(argv[1], &times);
        if (res == -1) {
            fprintf(stderr, "%s: couldn't set time\n", argv[0]);
            exit(EXIT_FAILURE);
        }

    } else {
    /* file does not exist - create it with given access permissions */
        mode_t perms = 0644;
        int fd = open(argv[1], O_CREAT|O_WRONLY, perms);
        close(fd);
    }
    exit(EXIT_SUCCESS);
}