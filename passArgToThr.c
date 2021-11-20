#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>              /* For timing */
#include <sys/time.h>            /* For timing */
#include <sys/resource.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>
int primes[10]={2,3,5,7,11,13,17,19,23,29};
void* routine(void* arg){
    int index=*(int *)arg;
    printf("%d ",primes[index]);

}
int main(){
    pthread_t th[10];
    for (int i=0;i<10;i++){
        pthread_create(&th[i],NULL,&routine,&i);
        sleep(1);
    }
    for (int i=0;i<10;i++){
        pthread_join(th[i],NULL);
    }
    return 0;
}