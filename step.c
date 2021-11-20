
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
int getStep(int row, int thr_count){//pass in number of row to find the step
    return (row/thr_count);
}
int main(){
    int row=200;
    int thr_count=3;
    printf("%d\n",getStep(row,thr_count));
}