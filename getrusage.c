#define __USE_GNU 
#include <sys/resource.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <limits.h>              /* For timing */
#include <sys/time.h>            /* For timing */
int main(){
    struct rusage rus;
    double sysTime, userTime;
    sleep(5);
    getrusage(RUSAGE_SELF, &rus);//get time information
     userTime=(double)rus.ru_utime.tv_sec+(double)rus.ru_utime.tv_usec*1e-6;
     sysTime=(double)rus.ru_stime.tv_sec+(double)rus.ru_stime.tv_usec*1e-6;
    printf("Program completed - user: %.4f s, system: %.4f s\n",userTime,sysTime);// user time and system time
        
        return 0;
}