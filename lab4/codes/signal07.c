#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

#define STDIN_FILENO 0
#define STDOUT_FILENO 1

void handler(int signum);

void main()
{
  int n;
  char line[100];
  /*
		 * Set the signal handler for Alarm signal
	*/

  signal(SIGALRM, handler);

  write(STDOUT_FILENO, "\nEnter a text (timeout after 10 secs):", 39);

  alarm(10); /* enable alarm */

  if ((n = read(STDIN_FILENO, line, 100)) < 0)
  {
    strcpy(line, "\nDEFAULT\n"); /* will be reached only if read is interrupted*/
  }

  alarm(0); /* disable alarm */

  write(STDOUT_FILENO, line, n);

  exit(0);
}
/*
	 * This the the signal handler for SIGALRM signal 
	 */

void handler(int signum)
{

  printf("\n\n TimeOut......\n");
}
