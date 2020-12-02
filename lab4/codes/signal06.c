#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>

void handler(int signum);

main()
{
  int pid, i;
		/*
		 * Set the signal handler SIGUSR1
		 */
  
  signal (SIGUSR1, handler);

  printf("\nmy pid = %d\n", getpid());
  pid = fork();
  
  if (pid == -1)
  	perror("error in fork");
  	
  else if (pid == 0)
 	{ 
  	   printf("\nI am the child, my pid = %d and my parent's pid = %d\n\n", getpid(), getppid());
  	   sleep(10);

	}   
  else 	
  	{
  	  printf("\nI am the parent, my pid = %d and my parent's pid = %d\n\n", getpid(), getppid());	  	
  	  sleep(5);
          for(i = 0; i < 3 ; i++)
           {
            printf("\n Sending SIGUSR1 signal to the process group %d\n",getpgrp());
            killpg(getpgrp(), SIGUSR1);
            sleep(2);
           }

 	}  

  printf("\nPID %d terminated\n\n", getpid());
}
	/*
	 * This the the signal handler for SIGUSR1 signal 
	 */

void handler(int signum)
{
 
  printf("My Pid is [%d], and i have got signal #%d\n",getpid(), signum);
  
  /* signal( SIGUSR1, handler); */
}

