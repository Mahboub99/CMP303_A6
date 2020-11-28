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
    	   while(1){}
  	}   
  else 	
  	{
  	  printf("\nI am the parent, my pid = %d and my parent's pid = %d\n\n", getpid(), getppid());	  	
	  while(1){}	
	}

  printf("\nPID %d terminated\n\n", getpid());
}
