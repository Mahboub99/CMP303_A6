#include <unistd.h>
#include <stdio.h>

int main()
{
  int pid, x=3;
  
  printf("\nmy pid = %d\n", getpid());
  pid = fork();
  
  if (pid == -1)
  	perror("error in fork");
  	
  else if (pid == 0)
 	{ 
	   x=7;
  	   printf("\nI am the child, my pid = %d and my parent's pid = %d, and the value of x = %d\n\n", getpid(), getppid(), x);

  	}   
  else 	
  	{
          x=19;
  	  printf("\nI am the parent, my pid = %d and my parent's pid = %d, and the value of x = %d\n\n", getpid(), getppid(), x);	  
	}  

  printf("\n Finish: PID:%d, X:%d", getpid(),x);
return 0;
}
