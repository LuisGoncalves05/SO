#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    for (int i = 3; i < argc; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            execlp("gcc", "gcc", "-Wall", "-c", argv[i], NULL);
            exit(EXIT_SUCCESS);
        } else {
            printf("[pid:%d]compiling %s\n", pid, argv[i]);
        }
    }

    for (int i = 1; i < argc; i++) wait(NULL);

    char *arguments[argc + 1];
    arguments[0] = "gcc";

    for (int i = 3; i < argc; i++) {
        char* dot = strstr(argv[i], ".");
        *(dot+1) = 'o';
        arguments[i - 2] = argv[i];
    }

    arguments[argc - 2] = "-o";
    arguments[argc - 1] = argv[2];
    arguments[argc] = NULL;

    execvp("gcc", arguments);

    printf("Program was compiled\n");

    exit(EXIT_SUCCESS);
}