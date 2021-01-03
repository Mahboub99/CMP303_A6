#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>

const int MAXN = 256;

void conv(char *msg, int size)
{
    int i;
    for (i = 0; i < size; ++i)
        if (islower(msg[i]))
            msg[i] = toupper(msg[i]);
        else if (isupper(msg[i]))
            msg[i] = tolower(msg[i]);
}

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

    struct msgbuff fromUpMessage;
    struct msgbuff toDownMessage;

    while (1)
    {

        rec_val = msgrcv(up_id, &fromUpMessage, sizeof(fromUpMessage.mtext), 0, !IPC_NOWAIT);

        if (rec_val == -1)
            perror("Error in receive");
        else
            printf("\nMessage received: %s\n", fromUpMessage.mtext);

        char tobesend[256];
        strcpy(tobesend, fromUpMessage.mtext);
        conv(tobesend, strlen(tobesend));
        strcpy(toDownMessage.mtext, tobesend);
        toDownMessage.mtype = getpid() % 4;

        send_val = msgsnd(down_id, &toDownMessage, sizeof(toDownMessage.mtext), !IPC_NOWAIT);

        if (send_val == -1)
            perror("Errror in send");
        else
            printf("%s", "message sent\n");
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
