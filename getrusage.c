#define __USE_GNU 
#include <sys/resource.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>              /* For timing */
#include <sys/time.h>            /* For timing */
int main(){
    struct rusage usage;

    getrusage(RUSAGE_THREAD, &usage);//get time information
    printf("Program completed - user: %.4f s, system: %.4f s\n",// user time and system time
        (usage.ru_utime.tv_sec + usage.ru_utime.tv_usec/1000000.0),
        (usage.ru_stime.tv_sec + usage.ru_stime.tv_usec/1000000.0));
        return 0;
}