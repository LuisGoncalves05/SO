#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[]) {
    FILE* record = fopen("record.txt", "w");
    for( ; ; ) {
        /* give prompt, read command and null terminate it */
        fprintf(stdout, "$ ");
        char buf[1024];
        char* command = fgets(buf, sizeof(buf), stdin);
        fwrite(command, strlen(command), sizeof(char), record);
        fflush(record);

        if(command == NULL) break;
        
        command[strlen(buf) - 1] = '\0';
        if(strcmp(command, "exit") == 0) exit(EXIT_SUCCESS);

        char* args[64];
        size_t idx = 0;
        if (strstr(command, "history")) {
            args[idx++] = "tail";

            if (strlen(command) > 7) {
                char* num_arg = command + 8;
                if (*num_arg != '\0' && isdigit(*num_arg)) {
                    char* start = malloc(strlen(num_arg) + 3 + 1);
                    strcpy(start, "-n ");
                    strcpy(start + 3, num_arg);
                    start[strlen(num_arg) + 3] = 0;
                    args[idx++] = start;
                }
            }

            args[idx++] = "record.txt";
        } else {
            char* token = strtok(command, " ");
            while (token) {
                args[idx++] = strdup(token);
                token = strtok(NULL, " \t");
            }
        }
        args[idx] = NULL;

        /* call fork and check return value */
        pid_t pid = fork();
        if(pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if(pid == 0) {
            /* child */
            execvp(args[0], args);
            perror("execvp"); exit(EXIT_FAILURE);
        }
        /* shell waits for command to finish before giving prompt again */
        int retv = waitpid(pid, NULL, 0);
        if (retv == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
    }
    printf("\n");
    fclose(record);
    exit(EXIT_SUCCESS);
}