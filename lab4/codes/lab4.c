#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

void handler(int signum);

int x, idx = 73;
int childIdx;
int a[2];
void main(int args, char **argv)
{

    signal(SIGUSR1, handler);

    int arr[args - 2];
    int n = args - 2;
    x = atoi(argv[1]);

    for (int i = 2; i < args; i++)
        arr[i - 2] = atoi(argv[i]);

    int pid;
    printf("\nI am the parent, my pid = %d and my parent's pid = %d\n", getpid(), getppid());

    for (int i = 0; i < 2; i++)
    {

        pid = fork();
        a[i] = pid;
        if (pid == -1)
        {
            perror("error in fork");
        }
        else if (pid == 0)
        {
            //child

            if (i == 0)
            {

                for (int j = 0; j < n / 2; j++)
                {
                    ;
                    if (arr[j] == x)
                    {
                        childIdx = i + 1;
                        idx = j + 1;
                    }
                }
                printf("\nI am the child %d, my pid = %d and my parent's pid = %d\n", i + 1, getpid(), getppid());
            }
            else
            {
                for (int j = n / 2 + 1; j < n; j++)
                {

                    if (arr[j] == x)
                    {
                        childIdx = i + 1;
                        idx = j + 1;
                    }
                }
                printf("\nI am the child %d, my pid = %d and my parent's pid = %d\n", i + 1, getpid(), getppid());
            }
            //exit(idx);
            if (idx == 73)
            {

                sleep(3);
                printf("\nthe child%d had been terminated\n", i + 1);
                raise(SIGINT);
            }
            else
            {
                kill(getppid(), SIGUSR1);
                exit(idx);
            }
        }
    }

    sleep(5);
    int stat_loc;
    for (int i = 0; i < 2; i++)
    {
        pid = wait(&stat_loc);
        if (!(stat_loc & 0x00FF))
            printf("\nA child with pid %d exit with code %d\n", pid, stat_loc >> 8);
    }
    printf("\nValue Not found\n");
}
void handler(int signum)
{

    int pid, stat_loc;

    pid = wait(&stat_loc);
    int i = (a[0] == pid) ? 1 : 2;
    if (!(stat_loc & 0x00FF))
        printf("\nchild%d : found value %d at postion %d\n", i, x, stat_loc >> 8);

    killpg(getpid(), SIGKILL);
    signal(SIGUSR1, handler);
}