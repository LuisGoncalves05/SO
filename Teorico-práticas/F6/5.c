#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int flag = 1;
static void inthandler() {
    printf("\nHandled it!\n");
    flag = 0;
}

int main(int argc, char* argv[]) {
    printf("my PID is %d\n", getpid());

    if (signal(SIGINT, inthandler) == SIG_ERR) {
        fprintf(stderr, "Can't catch SIGINT: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    /* enter potentially infinite loop ... */
    while(flag) {
        pause();
    }
    
    exit(EXIT_SUCCESS);
}