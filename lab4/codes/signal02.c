#include <stdio.h>
#include <signal.h>

void handler(int signum);

void main()
{
  		/*
		 * Set the signal handler
		 */
  
  signal(SIGINT, handler);
  signal(SIGTSTP, handler);
  signal(SIGKILL, handler);

  while(1) { }       /* dummy wait */
 
}

	/*
	 * This the the signal handler for SIGINT signal 
	 */

void handler(int signum)
{
  printf("\nOUCH....Signal #%d received\n",signum);
  
  /* To reset the signal handler to default , uncomment the following line */
 
   //signal(SIGINT, SIG_IGN ); 
 
  /* To reset the signal handler to same handler if our system set it to default , uncomment the following line */
 
   signal(SIGINT, handler );
}

