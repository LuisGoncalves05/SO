#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void handler1() { printf("caught SIGUSR1\n"); }
static void handler2() { printf("caught SIGUSR2\n"); }
static void handlerTstp() { printf("caught SIGTSTP\n"); }
static void handlerInt() { printf("caught SIGINT\n"); }
static void handlerHup() { printf("caught SIGHUP\n"); }
static void handlerKill() { printf("caught SIGKILL\n"); }


int main(int argc, char* argv[]) {
    printf("my PID is %d\n", getpid());
    if (signal(SIGUSR1, handler1) == SIG_ERR) {
        fprintf(stderr, "Can't catch SIGUSR1: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (signal(SIGUSR2, handler2) == SIG_ERR) {
        fprintf(stderr, "Can't catch SIGUSR2: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (signal(SIGTSTP, handlerTstp) == SIG_ERR) {
        fprintf(stderr, "Can't catch SIGTSTP: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (signal(SIGINT, handlerInt) == SIG_ERR) {
        fprintf(stderr, "Can't catch SIGINT: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (signal(SIGHUP, handlerHup) == SIG_ERR) {
        fprintf(stderr, "Can't catch SIGHUP: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (signal(SIGKILL, handlerKill) == SIG_ERR) {
        fprintf(stderr, "Can't catch SIGKILL: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    /* stick around ... */
    for ( ; ; )
    pause();
}