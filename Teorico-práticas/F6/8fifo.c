#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#define READ_END 0
#define WRITE_END 1

int main (int argc, char* argv[]) {
    char* myfifo = "/tmp/myfifo";
    int rv = mkfifo(myfifo, 0666);
    if (rv == -1) { perror("mkfifo"); exit(EXIT_FAILURE); }

    pid_t pid;
    if ((pid = fork()) < 0) {/* fork error */}

    if (argc != 2) {
        exit(EXIT_FAILURE);
    }

    char* cmd1 = strtok(argv[1], "|");
    char* cmd2 = strtok(NULL, "|");
    
    if (pid > 0) {
        /* parent */
        int fd = open(myfifo, O_WRONLY);
        if (fd == -1) { perror("open"); exit(EXIT_FAILURE); }

        char* args1[64];
        size_t idx1 = 0;
        char* token1 = strtok(cmd1, " ");
        while (token1) {
            args1[idx1++] = strdup(token1);
            token1 = strtok(NULL, " ");
        }
        args1[idx1] = NULL;
        
        dup2(fd, STDOUT_FILENO); /* stdout to fifo */
        /* parent writes to the fifo */
        if (execvp(args1[0], args1) < 0) {
        /* exec error */
        }
        close(fd);
    } else {
        /* child */
        int fd = open(myfifo,O_RDONLY);
        if (fd == -1) { perror("open"); exit(EXIT_FAILURE); }

        char* args2[64];
        size_t idx2 = 0;
        char* token2 = strtok(cmd2, " ");
        while (token2) {
            args2[idx2++] = strdup(token2);
            token2 = strtok(NULL, " ");
        }
        args2[idx2] = NULL;

        dup2(fd, STDIN_FILENO); /* stdin from fifo */
        if (execvp(args2[0], args2) < 0) {
            /* exec error */
        }

        close(fd);
    }
    unlink(myfifo);
    exit(EXIT_SUCCESS);
}
