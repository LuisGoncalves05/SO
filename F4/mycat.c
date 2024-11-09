#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("No file was specified\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < argc; i++) {
        int fd = open(argv[i], O_RDONLY);
        if (fd == -1) {
            printf("Can't open file\n");
            exit(EXIT_FAILURE);
        }
        ssize_t nbytes;
        char buffer[BUFFER_SIZE];
        do {
            nbytes = read(fd, buffer, BUFFER_SIZE);
            if (nbytes == -1) {
                printf("Can't read file\n");
                exit(EXIT_FAILURE);
            }
            write(STDOUT_FILENO, buffer, nbytes);
        } while (nbytes > 0);
        close(fd);
    }
    exit(EXIT_SUCCESS);
}