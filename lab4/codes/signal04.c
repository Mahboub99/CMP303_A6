#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

void handler(int signum);

void main()
{
  int i;
		/*
		 * Set the signal handler 
		 */
  
  signal (SIGUSR1, handler);

  printf("\nmy pid = %d\n", getpid());
	
  sleep(4);
  for(i = 0; i < 3 ; i++)
   {
    printf("\n Sending SIGUSR1 signal to the process %d\n", getpid());
    raise(SIGUSR1);
    sleep(2);
   }

  printf("\nPID %d terminated\n\n", getpid());
}
	/*
	 * This the the signal handler for SIGUSR1 signal 
	 */

void handler(int signum)
{
 static int counter = 0;
 
 printf("My Pid is [%d], and i have got signal #%d, Counter=%d\n",getpid(), signum, ++counter);
  
  /* Install the signal handler again to trap SIGUSR1 again */
  /*  signal (SIGUSR1, handler); */ 
}

