#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/time.h>
#include<pthread.h>
#include<unistd.h>
#include"tree.h"

void *timer(void *arg)
{
  struct timeval start, end;

  gettimeofday(&start,NULL);
  /* do something */
  sleep(10); 

  gettimeofday(&end,NULL);

  printf("%ld.%06ld\n", (end.tv_sec - start.tv_sec), (end.tv_usec - start.tv_usec));

  /*return from thread */
  pthread_exit(0);
}
