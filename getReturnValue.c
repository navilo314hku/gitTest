#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
void* roll_dice(){
    int value=(rand()%6)+1;
    int *resultPtr=malloc(sizeof(int));
    *resultPtr =value;//modify the value of resultPtr as value
    return (void*) resultPtr;//return the resultPtr with void* casting 
}
int main(){
    int*resPtr;
    srand(time(NULL));
    pthread_t th;
    if(pthread_create(&th,NULL,&roll_dice,NULL)!=0){
        return 1;//error in thread create
    }
    if (pthread_join(th,(void**)&resPtr)!=0){//pass the address of the pointer 
        return 2;
    }
    printf("Main res: %p\n",resPtr);
    printf("Result: %d\n",*resPtr);
    free(resPtr);

}