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
#include <signal.h>

const int MAXN = 256;

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
    strcpy((char *)shmaddr, msg);
}

void reader(int shmid)
{
    void *shmaddr = shmat(shmid, (void *)0, 0);
    if (shmaddr == -1)
    {
        perror("Error in attach in reader");
        exit(-1);
    }

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

    int mesid, shmid, semid1, semid2, rec_val;
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
        // hold in server to wait

        char toShared[256];
        scanf("%s", toShared);
        writer(shmid, toShared);

        release(semid1);
        hold(semid2);

        rec_val = msgrcv(mesid, &messageDone, sizeof(messageDone.mtext), 0, !IPC_NOWAIT);

        if (rec_val == -1)
            perror("Error in receive Done");

        printf("Message received from server: %s\n", messageDone.mtext);

        reader(shmid);
    }

    return 0;
}
