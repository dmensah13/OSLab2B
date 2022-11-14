/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

bool has_hit = false; 
void handler(int signum)
{ //signal handler
  printf("Hello World!\n");
  signal(SIGALRM,handler);
  alarm(1);
  //exit(1); //exit after printing
}

int main(int argc, char * argv[])
{
  signal(SIGALRM,handler); //register handler to handle SIGALRM
  alarm(1); //Schedule a SIGALRM for 1 second
  while(has_hit == false){ //busy wait for signal to be delivered
   sleep(1);
   printf("Turing was right\n");
  }
  return 0; //never reached
}