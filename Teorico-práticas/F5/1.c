#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    fork();
    //2
    fork();
    //4
    fork();
    //8
    printf("%d\n", getpid());
    exit(EXIT_SUCCESS);
}

//8