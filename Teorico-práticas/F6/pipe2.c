#include <sys/wait.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
    char buf[BUFFER_SIZE];
    int sockets[2], retv;
    retv = socketpair(AF_UNIX, SOCK_STREAM, 0, sockets);
    if (retv == -1) { perror("socketpair"); exit(EXIT_FAILURE); }
    retv = fork();
    if (retv == -1) { perror("fork"); exit(EXIT_FAILURE); }

    if (retv > 0) { /* parent */
        close(sockets[1]);

        char string1[BUFFER_SIZE];
        int fd = open(argv[1], O_RDONLY);
        if (fd == -1) exit(EXIT_FAILURE);

        int nbytes;
        while ((nbytes = read(fd, string1, BUFFER_SIZE))){
            write(sockets[0], string1, nbytes);
            nbytes = read(sockets[0], buf, BUFFER_SIZE);
            write(STDOUT_FILENO, buf, nbytes);
        }

        close(sockets[0]);

        retv = wait(NULL);
        if (retv == -1) { perror("wait"); exit(EXIT_FAILURE); }
    } else { /* child */
        close(sockets[0]);

        char string2[BUFFER_SIZE];

        int nbytes;
        while ((nbytes = read(sockets[1], string2, BUFFER_SIZE))){
            int i = 0;
            while (string2[i++]) {
                string2[i] = toupper(string2[i]);
            }
            write(sockets[1], string2, nbytes);
        }

        close(sockets[1]);
        exit(EXIT_SUCCESS);
    }
}
