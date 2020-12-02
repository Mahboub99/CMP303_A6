#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

void handler(int signum);

void main()
{
    signal(SIGUSR1, handler);
    int pid = fork();
    if (pid == -1)
        perror("error in forking");
    else if (pid == 0)
    {
        printf("\ni am child and my pid %d\n", getpid());
        //raise(SIGUSR1);
        exit(100);
    }
    sleep(5);
    raise(SIGUSR1);
    printf("\nnow i am the parent and my  = %d\n ", getpid());
}

void handler(int signunm)
{

    int pid, stat_loc;

    pid = wait(&stat_loc);
    if (!(stat_loc & 0x00FF))
        printf("\nI am called with the process %d with value %d\n", pid, stat_loc >> 8);
}