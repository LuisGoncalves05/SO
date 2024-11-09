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
        char buffer;
        int file_size = lseek(fd, 0, SEEK_END);
        int pos = file_size;
        do {
            pos = lseek(fd, pos, SEEK_SET);
            nbytes = read(fd, &buffer, 1);
            if (nbytes == -1) {
                printf("Can't read file\n");
                exit(EXIT_FAILURE);
            }
            write(STDOUT_FILENO, &buffer, nbytes);
            pos--;
        } while (pos >= 0);
        
    }
    exit(EXIT_SUCCESS);
}