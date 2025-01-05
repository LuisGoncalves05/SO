#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("usage: cat filename\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 1; i < argc; i++) {
        int fd = open(argv[1], O_RDONLY);
        if (fd == -1) {
            printf("error: cannot open %s\n", argv[1]);
            exit(EXIT_FAILURE);
        }

        off_t offset = lseek(fd, 0, SEEK_END);

        for (int i = 1; i <= offset; i++) {
            lseek(fd, -i, SEEK_END);
            char c[1];
            read(fd, c, 1);
            write(STDOUT_FILENO, c, 1);
        }

        close(fd);
    }

    exit(EXIT_SUCCESS);
}
