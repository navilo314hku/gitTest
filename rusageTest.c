#define _GNU_SOURCE
#define __USE_GNU 
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>              /* For timing */
#include <sys/time.h>            /* For timing */
#include <sys/resource.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>
int main (int argc, char *argv[]){
    struct rusage usage; 
    sleep(5);
    
    
	double userTime=(double)usage.ru_utime.tv_sec+(double)usage.ru_utime.tv_usec/1000000.0;
    double sysTime=(double)usage.ru_stime.tv_sec+(double)usage.ru_stime.tv_usec/1000000.0;
  //  userTime=(usage.ru_utime.tv_sec + usage.ru_utime.tv_usec/1000000.0);
  //  sysTime=  (usage.ru_stime.tv_sec + usage.ru_stime.tv_usec/1000000.0);
    printf("Program completed - user: %.4f s, system: %.4f s\n",userTime,sysTime);
    return 0;

}
