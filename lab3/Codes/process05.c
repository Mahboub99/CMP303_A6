#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

void main()
{
  int pid, stat_loc;
  
  printf("\nmy pid = %d\n", getpid());
  pid = fork();
  
  if (pid == -1)
  	perror("error in fork");
  	
  else if (pid == 0)
 	{ 
  	   printf("\nI am the child, my pid = %d and my parent's pid = %d\n\n", getpid(), getppid());
  	}   
  else 	
  	{
  	  printf("\nI am the parent, my pid = %d and my parent's pid = %d\n\n", getpid(), getppid());	  	
  	  sleep(20);
  	  pid = wait(&stat_loc);
  	  if(!(stat_loc & 0x00FF))
  	    printf("\nA child with pid %d terminated with exit code %d\n", pid, stat_loc>>8);
	}  

  printf("\nPID %d terminated\n\n", getpid());
}
