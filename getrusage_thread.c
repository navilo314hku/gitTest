#define __USE_GNU 

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>              /* For timing */
#include <sys/time.h>            /* For timing */
#include <sys/resource.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <semaphore.h>           /* For timing */
struct rusage usage;

void *thr_func(void *arg) {//what do we want to pass in
    sleep(5);
    getrusage(RUSAGE_THREAD,&usage);//store the global var usage
    return;
}
int main(){
    pthread_t thr;
    pthread_create(&thr,NULL,&thr_func,NULL);
    pthread_join(thr,NULL);
    printf("Program completed - user: %.4f s, system: %.4f s\n",// user time and system time
        (usage.ru_utime.tv_sec + usage.ru_utime.tv_usec/1000000.0),
        (usage.ru_stime.tv_sec + usage.ru_stime.tv_usec/1000000.0));
        return 0;
}