#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define LINESIZE 256

int main(int argc, char* argv[]) {
    int fd[2];
    pid_t pid;
    if (pipe(fd) == -1) { perror("pipe"); exit(EXIT_FAILURE); }
    if ((pid = fork()) == -1) { perror("fork"); exit(EXIT_FAILURE); }

    // Read on 0, write on 1

    if (pid > 0) { /* parent */
        close(fd[0]);

        int arg = open(argv[1], O_RDONLY);
        if (arg < 0) exit(EXIT_FAILURE);

        char line[LINESIZE];
        int nbytes;
        while((nbytes = read(arg, line, LINESIZE)) > 0) {
            write(fd[1], line, nbytes);
        }
        close(fd[1]);

        if (wait(NULL) == -1) { perror("wait"); exit(EXIT_FAILURE); }

    } else { /* child */
        close(fd[1]);

        char line[LINESIZE];

        int nbytes;
        while((nbytes = read(fd[0], line, LINESIZE)) > 0) {
            write(STDOUT_FILENO, line, nbytes);
        }
        close(fd[0]);
    }
    exit(EXIT_SUCCESS);
}
