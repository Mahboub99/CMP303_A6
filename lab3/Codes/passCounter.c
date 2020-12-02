#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>

int *read_ints(const char *file_name, int *S)
{

    FILE *file = fopen(file_name, "r");
    fscanf(file, "%d", &(*S));
    int *arr;
    int i = 0;
    while (!feof(file))
    {
        int a, b;
        fscanf(file, "%d", &a);
        fscanf(file, "%d", &b);

        arr[i++] = a + b;
    }
    fclose(file);

    return arr;
}

int main(int argc, char **argv)
{
    int pid, stat_loc = 0;
    int N, P, S;
    char *path = argv[1];
    sscanf(argv[2], "%d", &N);
    sscanf(argv[3], "%d", &P);

    int *grade = read_ints(path, &S);
    int *status;
    int group = S / N, rem = S % N;

    printf("Expected output:\n");
    int *pIds;
    int ans[N];
    for (int i = 0; i < N; i++)
    {
        pid = fork();
        pIds[i] = pid;
        if (pid == -1)
            perror("error in fork");

        else if (pid == 0)
        {

            int cnt = 0;
            for (int j = i * group, k = 0; k < group + ((i == N - 1) ? rem : 0); j++, k++)
                cnt += (grade[j] >= P);

            //printf("%d\n", i);
            exit(cnt);
        }
        else
        {

            pid = wait(&stat_loc);
            //printf("%d ", pid);
            for (int j = 0; j < N; j++)
            {
                if (pid == pIds[j])
                {
                    ans[j] = stat_loc >> 8;
                    printf("%d ", stat_loc >> 8);
                }
            }
            printf("\n");
        }
    }
    return 0;
}
