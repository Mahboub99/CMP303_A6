#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <ctype.h>
#include <string.h>

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

void writer(int shmid, char *msg)
{
    void *shmaddr = shmat(shmid, (void *)0, 0);
    if (shmaddr == -1)
    {
        perror("Error in attach in writer");
        exit(-1);
    }
    conv(msg, strlen(msg));
    strcpy((char *)shmaddr, msg);
}

void reader(int shmid, char *msg)
{
    void *shmaddr = shmat(shmid, (void *)0, 0);
    if (shmaddr == -1)
    {
        perror("Error in attach in reader");
        exit(-1);
    }

    strcpy(msg, (char *)shmaddr);
    printf("\nreceived : %s\n", (char *)shmaddr);
}

/* arg for semctl system calls. */
union Semun
{
    int val;               /* value for SETVAL */
    struct semid_ds *buf;  /* buffer for IPC_STAT & IPC_SET */
    ushort *array;         /* array for GETALL & SETALL */
    struct seminfo *__buf; /* buffer for IPC_INFO */
    void *__pad;
};

void hold(int sem)
{
    struct sembuf p_op;

    p_op.sem_num = 0;
    p_op.sem_op = -1;
    p_op.sem_flg = !IPC_NOWAIT;

    if (semop(sem, &p_op, 1) == -1)
    {
        perror("Error in hold()");
        exit(-1);
    }
}

void release(int sem)
{
    struct sembuf v_op;

    v_op.sem_num = 0;
    v_op.sem_op = 1;
    v_op.sem_flg = !IPC_NOWAIT;

    if (semop(sem, &v_op, 1) == -1)
    {
        perror("Error in release()");
        exit(-1);
    }
}

int main()
{

    int mesid, shmid, semid1, semid2, send_val;
    key_t meskey, shmkey, semkey1, semkey2;

    meskey = ftok("keyfile", 'q');
    shmkey = ftok("keyfile", 'm');
    semkey1 = ftok("keyfile", 's');
    semkey2 = ftok("keyfile", 'p');

    mesid = msgget(meskey, 0666 | IPC_CREAT);
    shmid = shmget(shmkey, 4096, 0644 | IPC_CREAT);
    semid1 = semget(semkey1, 1, 0666 | IPC_CREAT);
    semid2 = semget(semkey2, 1, 0666 | IPC_CREAT);

    if (mesid == -1 || shmid == -1 || semid1 == -1 || semid2 == -1)
    {
        perror("Error in creat in client");
        exit(-1);
    }
    struct msgbuff messageDone;

    while (1)
    {
        char toShared[256];
        // hold in server to wait cleint sent
        hold(semid1);
        // the client had released now and hold the other
        reader(shmid, toShared);
        writer(shmid, toShared);
        // now realese so client can read
        release(semid2);

        char Done[10];
        strcpy(Done, "Done\n");
        messageDone.mtype = getpid() % 4;
        strcpy(messageDone.mtext, Done);

        send_val = msgsnd(mesid, &messageDone, sizeof(messageDone.mtext), !IPC_NOWAIT);

        if (send_val == -1)
            perror("Errror in send");
        else
            printf("%s", "message sent\n");
    }
    return 0;
}