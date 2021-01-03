#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

const int MAXN = 256;

struct msgbuff
{
    long mtype;
    char mtext[256];
};

int up_id, down_id, send_val, rec_val;
key_t key_up_id, key_down_id;

void handler(int signum);

int main()
{
    signal(SIGINT, handler);

    key_up_id = ftok("keyfile", 65);
    key_down_id = ftok("keyfile", 66);

    up_id = msgget(key_up_id, 0666 | IPC_CREAT);
    down_id = msgget(key_down_id, 0666 | IPC_CREAT);

    if (up_id == -1 || down_id == -1)
    {
        perror("Error in create");
        exit(-1);
    }
    printf("Message Queue ID = %d\n", up_id);

    struct msgbuff toUpMessage;
    struct msgbuff fromDownMessage;

    while (1)
    {

        char tobesend[256];
        scanf("%s", tobesend);
        toUpMessage.mtype = getpid() % 4; /*any number*/
        strcpy(toUpMessage.mtext, tobesend);

        send_val = msgsnd(up_id, &toUpMessage, sizeof(toUpMessage.mtext), !IPC_NOWAIT);

        if (send_val == -1)
            perror("Errror in send");
        else
            printf("%s", "message sent\n");

        rec_val = msgrcv(down_id, &fromDownMessage, sizeof(fromDownMessage.mtext), 0, !IPC_NOWAIT);

        if (rec_val == -1)
            perror("Error in receive");
        else
            printf("\nMessage received: %s\n", fromDownMessage.mtext);
    }
    return 0;
}
void handler(int signum)
{
    printf("\nOUCH....Signal #%d received\n", signum);
    msgctl(up_id, IPC_RMID, (struct msqid_ds *)0);
    msgctl(down_id, IPC_RMID, (struct msqid_ds *)0);

    exit(1);
    signal(SIGINT, handler);
}
