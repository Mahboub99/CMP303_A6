#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

void handler(int signum);

void main()
{
  int pid, i;
		/*
		 * Set the signal handler for child termination
		 */
  
  
  signal (SIGCHLD, handler);
  printf("\nmy pid = %d\n", getpid());
  pid = fork();
  
  if (pid == -1)
  	perror("error in fork");
  	
  else if (pid == 0)
 	{ 

  	   printf("\nI am the child, my pid = %d and my parent's pid = %d\n", getpid(), getppid());
  	   sleep(5);
	   exit(66);
	}   
  else 	
  	{

  	  printf("\nI am the parent, my pid = %d and my parent's pid = %d\n", getpid(), getppid());	  	
  	  sleep(100);   /* do anything */
          sleep(5);
    }  

	printf("\nPID %d terminated\n\n", getpid());
 
}
	/*
	 * This the the signal handler for SIGCHLD signal 
	 */

void handler(int signum)
{
 int pid, stat_loc;

 printf("Child has sent a SIGCHLD signal #%d\n",signum);

 pid = wait(&stat_loc);
 if(!(stat_loc & 0x00FF))
    printf("\nA child with pid %d terminated with exit code %d\n", pid, stat_loc>>8);

}

