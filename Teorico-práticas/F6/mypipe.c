#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define READ_END 0
#define WRITE_END 1

int main (int argc, char* argv[]) {
    char cmd1[128];
    int idx1 = 0;

    char* token = strsep(&argv[1], "|");
    for (int i = 0; i < strlen(token); i++) {
        cmd1[idx1++] = token[i];
    }
    cmd1[idx1] = 0;

    char cmd2[128];
    int idx2 = 0;
    token = strsep(&argv[1], "|");
    for (int i = 0; i < strlen(token); i++) {
        cmd2[idx2++] = token[i];
    }
    cmd2[idx2] = 0;

    char* cmd1v2[8];
    char* trash_ptr2 = cmd1;
    int idx1v2 = 0;
    while ((token = strsep(&trash_ptr2, " "))) {
        if (*token) cmd1v2[idx1v2++] = token;
    }
    cmd1v2[idx1v2] = NULL;
    
    char* cmd2v2[8];
    trash_ptr2 = cmd2;
    int idx2v2 = 0;
    while ((token = strsep(&trash_ptr2, " "))) {
        if (*token) cmd2v2[idx2v2++] = token;
    }
    cmd2v2[idx2v2] = NULL;


    for (int i = 0; cmd1v2[i]; i++) {
        printf("%s\n", cmd1v2[i]);
    }

    for (int i = 0; cmd2v2[i]; i++) {
        printf("%s\n", cmd2v2[i]);
    }

    int fd[2];
    pid_t pid;
    if (pipe(fd) < 0) {
        /* pipe error */
    }
    if ((pid = fork()) < 0) {
        /* fork error */
    }
    if (pid > 0) {
        close(fd[READ_END]);
        dup2(fd[WRITE_END], STDOUT_FILENO); /* stdout to pipe */
        close(fd[WRITE_END]);
        /* parent writes to the pipe */
        if (execvp(cmd1v2[0], cmd1v2) < 0) {
        /* exec error */
        }
    } else {
        close(fd[WRITE_END]);
        dup2(fd[READ_END], STDIN_FILENO); /* stdin from pipe */
        close(fd[READ_END]);
        if (execvp(cmd2v2[0], cmd2v2) < 0) {
        /* exec error */
        }
    }
}