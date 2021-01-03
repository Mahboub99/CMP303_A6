#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

struct msgbuff
{
    long mtype;
    char mtext[70];
};

void do_parent(key_t msgqid)
{
    int send_val;
    char str[] = "\nMessage from parent to child: I am drowning, help meeee...!!\n";
    struct msgbuff message;

    message.mtype = 7; /* arbitrary value */
    strcpy(message.mtext, str);

    sleep(5);
    send_val = msgsnd(msgqid, &message, sizeof(message.mtext), !IPC_NOWAIT);

    if (send_val == -1)
        perror("Errror in send");
}

void do_child(key_t msgqid)
{
    int rec_val;
    struct msgbuff message;

    /* receive all types of messages */
    rec_val = msgrcv(msgqid, &message, sizeof(message.mtext), 0, !IPC_NOWAIT);

    if (rec_val == -1)
        perror("Error in receive");
    else
        printf("\nMessage received: %s\n", message.mtext);

    msgctl(msgqid, IPC_RMID, (struct msqid_ds *)0);
}

int main()
{
    pid_t pid;
    key_t msgqid;

    msgqid = msgget(IPC_PRIVATE, 0644); // or msgget(12613, IPC_CREATE | 0644)
    if (msgqid == -1)
    {
        perror("Error in create");
        exit(-1);
    }
    printf("msgqid = %d\n", msgqid);

    pid = fork();
    if (pid == 0)
        do_child(msgqid);
    else if (pid != -1)
        do_parent(msgqid);
    else
    {
        perror("Error in fork");
        exit(-1);
    }
    return 0;
}
