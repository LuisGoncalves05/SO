#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h> 

#define READ_END 0
#define WRITE_END 1

int main (int argc, char* argv[]) {
    int fd[2];
    pid_t pid;
    if (pipe(fd) < 0) {/* pipe error */}
    if ((pid = fork()) < 0) {/* fork error */}

    if (argc != 2) {
        exit(EXIT_FAILURE);
    }

    char* cmd1 = strtok(argv[1], "|");
    char* cmd2 = strtok(NULL, "|");
    
    if (pid > 0) {
        /* parent */
        close(fd[READ_END]);

        char* args1[64];
        size_t idx1 = 0;
        char* token1 = strtok(cmd1, " ");
        while (token1) {
            args1[idx1++] = strdup(token1);
            token1 = strtok(NULL, " ");
        }
        args1[idx1] = NULL;
        
        dup2(fd[WRITE_END], STDOUT_FILENO); /* stdout to pipe */
        close(fd[WRITE_END]);
        /* parent writes to the pipe */
        if (execvp(args1[0], args1) < 0) {
        /* exec error */
        }
    } else {
        /* child */
        close(fd[WRITE_END]);

        char* args2[64];
        size_t idx2 = 0;
        char* token2 = strtok(cmd2, " ");
        while (token2) {
            args2[idx2++] = strdup(token2);
            token2 = strtok(NULL, " ");
        }
        args2[idx2] = NULL;

        dup2(fd[READ_END], STDIN_FILENO); /* stdin from pipe */
        close(fd[READ_END]);
        if (execvp(args2[0], args2) < 0) {
            /* exec error */
        }
    }
}
