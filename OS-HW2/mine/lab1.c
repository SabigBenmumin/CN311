#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 4

char NAME[] = {"Kittiphan", "Jantaprayoon"};
char university[] = {"Thammasat school of Engineering"};

void *PrintKub(void *threadid){
    long tid;
    tid = (long)threadid;
    if(tid == 1){
        printf("Sabig");
        pthread_exit(NULL);
    }
}

int main(int argc, char *argv[]){
    pthread_t thread[NUM_THREADS];
    int rc;
    long t;
    for(t=0; t < NUM_THREADS; t++){
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, PrintKub, (void *)t)
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    pthread_exit(NULL);
}
