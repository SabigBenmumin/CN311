#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM_THREADS    4

char* NAME[] = {"Sabig", "Benmumin"};
char* university[] = {"Thammasat school of Engineering"};

void *PrintHello(void *threadid)
{

    long tid;
    tid = (long)threadid;

   if (tid == 2)
   {
    printf("Thread %ld: %s\n", tid, university[0]);
   }
   else if (tid == 3)
   {
    printf("Thread %ld: ", tid);
    printf("%d characters\n", (int)strlen(university[0]));
   }
   else
   {
    printf("Thread %ld: %s\n", tid, NAME[tid]);
   }
   pthread_exit(NULL);
}

int main(int argc, char argv[])
{
pthread_t threads[NUM_THREADS];
int taskids[NUM_THREADS];
int rc, t;

for(t=0;t<NUM_THREADS;t++) {
  taskids[t] = (int) malloc(sizeof(int));
  taskids[t] = t;
  printf("Creating thread %d\n", t);
  rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
  if (rc) {
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
    }
  }

pthread_exit(NULL);
}