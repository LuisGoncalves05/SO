#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    for (int i = 0; i < 4; i++) {
        fork(); //2(i=0) 4(i=1) 8(i=2) 16(i=3)
        printf("%d\n", getpid());
    }
    exit(EXIT_SUCCESS);
}