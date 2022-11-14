/* timer.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

bool has_hit = false; 
clock_t t;
double cpu_time_used;
int alarm_count = 0;

void catch_handler(int signum)
{
  t = clock() - t;
  cpu_time_used = (((double)(t))/CLOCKS_PER_SEC) * 10000;
  printf("Number of Alarms Occured: %d\n", alarm_count);
  printf("Number of Seconds Passed During Execution: %f\n", cpu_time_used);
  exit(1);
}

void handler(int signum)
{ //signal handler
  signal(SIGINT, catch_handler);
  printf("Hello World!\n");
  signal(SIGALRM,handler);
  alarm(1);
  alarm_count += 1;
  //exit(1); //exit after printing
}

int main(int argc, char * argv[])
{
  t = clock();
  signal(SIGINT, catch_handler);
  signal(SIGALRM,handler); //register handler to handle SIGALRM
  alarm(1); //Schedule a SIGALRM for 1 second
  alarm_count += 1;
  while(has_hit == false){ //busy wait for signal to be delivered
   sleep(1);
   printf("Turing was right\n");
  }
  return 0; //never reached
}