#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include "counter.h"

#define THRESHOLD 1024

/* structs */
void* contador(void *);


/* start_routine header */
counter_t counter;
int MAXCNT;
int NUMTHREADS;
int numxThread ;

/* Global variables */
pthread_mutex_t lock; 

int main(int argc, char *argv[]) { 

    /* get the command's line parameters */
    pthread_mutex_init(&lock, NULL);
    MAXCNT = atoi(argv[1]);
    NUMTHREADS = atoi(argv[2]);


    /* Declaration of struct timeval variables */
    struct timeval tinicial, tfinal;
    long timeFull;


    /* Initializing conter */
    init(&counter, THRESHOLD);


    /* Threads handlers */
    pthread_t thr[NUMTHREADS];

/* Thread creation */
    numxThread = MAXCNT/NUMTHREADS;

    /* Time starts counting */
    gettimeofday(&tinicial, NULL);


    /* Creating a Threads */
    
    for(int i = 0; i < NUMTHREADS; i++){
       pthread_create(&thr[i], NULL, &contador,(void *)&i );
    }
   

    /* Threads joins */   
    for (int i = 0; i < NUMTHREADS; i++){
        pthread_join(thr[i],NULL);
    }


    /* Time stops counting here */    
    int fin_counter = get(&counter);


    /* get the end time */
     gettimeofday(&tfinal, NULL);
    

    /* get the elapset time (end_time - start_time) */
     timeFull = (tfinal.tv_sec - tinicial.tv_sec)*1000 + (tfinal.tv_usec - tinicial.tv_usec)/1000.0;


    /* print the results (number threads employed, counter value, elasep time) */
    printf("Numero de hilos corridos: %d | Resultado del contador: %d | tiempo transcurrido: %ld milisegundos \n",NUMTHREADS, fin_counter, timeFull);


    return 0;

}

/* start_routine definition */
void* contador( void* arg ){
    pthread_mutex_lock(&lock);  
    int contador_concurente = get(&counter);
    if(contador_concurente+1024 < MAXCNT){
       for(int i = 0; i < numxThread ; i++) {
            update(&counter,(int)pthread_self(),1);
        }
    }
    pthread_mutex_unlock(&lock);
    return 0;
}




