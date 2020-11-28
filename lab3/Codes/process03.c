#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
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
	  int sid;
  	  printf("\nI am the parent, my pid = %d and my parent's pid = %d\n\n", getpid(), getppid());	  	
  	  sid = wait(&stat_loc);
  	  if(!(stat_loc & 0x00FF))
  	    printf("\nA child with pid %d terminated with exit code %d\n", sid, stat_loc>>8);

          //if(WIFEXITED(stat_loc))
  	  //  printf("\nChild terminated normally with status %d", WEXITSTATUS(stat_loc));  
	}  

  printf("\nPID %d terminated\n\n", getpid());
return 0;
}
