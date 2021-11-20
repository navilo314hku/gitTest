
#define _GNU_SOURCE
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


/****************Global****************************/

#define MAX(a,b) ((a)>(b)?(a):(b))
#define EPSILON 0.001            /* Termination condition */

char *filename;                  /* File name of output file */

/* Grid size */
int M = 200;                     /* Number of rows */
int N = 200;                     /* Number of cols */
long max_its = 1000000;          /* Maximum iterations, a safe bound to avoid infinite loop */
double final_diff;               /* Temperature difference between iterations at the end */
int step;                        /* how much row each thread need to compute, except the last thread*/
int thr_count = 5;

/* shared variables between threads */
/*************************************************************/
double** u;                   /* Previous temperatures */
double** w;                   /* New temperatures */
                  


// (1) Add your variables here





/**************************************************************/

int main (int argc, char *argv[])
{  
 
   int      its;                 /* Iterations to converge */
   double   elapsed;             /* Execution time */
   struct timeval stime, etime;  /* Start and end times */
   struct rusage usage;
   void printdiffsArr(double diffs[]);
   void allocate_2d_array (int, int, double ***);
   void initialize_array (double ***);
   void print_solution (char *, double **);
   int  find_steady_state (void);
   int getStep(int row, int thr_count);//get how many rows each Thr need to process
   double getMaxDiff(double* p,int arrLen);//get the max diff among all diffs return from the threads
   /* For convenience of other problem size testing */
   if ((argc == 1) || (argc == 4)) {
      if (argc == 4) {
         M = atoi(argv[1]);
         N = atoi(argv[2]);
         thr_count = atoi(argv[3]);
      } // Otherwise use default grid and thread size
   } else {
     printf("Usage: %s [ <rows> <cols> <threads ]>\n", argv[0]);
     exit(-1);
   }

   printf("Problem size: M=%d, N=%d\nThread count: T=%d\n", M, N, thr_count);
   step=getStep(M,thr_count);
   /* Create the output file */
   filename = argv[0];
   sprintf(filename, "%s.dat", filename);

   allocate_2d_array (M, N, &u);
   allocate_2d_array (M, N, &w);
   initialize_array (&u);
   initialize_array (&w);

   gettimeofday (&stime, NULL);
   its = find_steady_state();
   gettimeofday (&etime, NULL);

   elapsed = ((etime.tv_sec*1000000+etime.tv_usec)-(stime.tv_sec*1000000+stime.tv_usec))/1000000.0;

   printf("Converged after %d iterations with error: %8.6f.\n", its, final_diff);
   printf("Elapsed time = %8.4f sec.\n", elapsed);

   getrusage(RUSAGE_SELF, &usage);
   printf("Program completed - user: %.4f s, system: %.4f s\n",
      (usage.ru_utime.tv_sec + usage.ru_utime.tv_usec/1000000.0),
    (usage.ru_stime.tv_sec + usage.ru_stime.tv_usec/1000000.0));
   printf("no. of context switches: vol %ld, invol %ld\n\n",
  		  usage.ru_nvcsw, usage.ru_nivcsw);

   print_solution (filename, w);
}

/* Allocate two-dimensional array. */
int getStep(int row, int thr_count){//pass in number of row to find the step
    return (row/thr_count);
}
void allocate_2d_array (int r, int c, double ***a)
{
   double *storage;
   int     i;
   storage = (double *) malloc (r * c * sizeof(double));
   *a = (double **) malloc (r * sizeof(double *));
   for (i = 0; i < r; i++)
      (*a)[i] = &storage[i * c];
}

/* Set initial and boundary conditions */
void initialize_array (double ***u)
{
   int i, j;

   /* Set initial values and boundary conditions */
   for (i = 0; i < M; i++) {
      for (j = 0; j < N; j++)
         (*u)[i][j] = 25.0;      /* Room temperature */
      (*u)[i][0] = 0.0;
      (*u)[i][N-1] = 0.0;
   }

   for (j = 0; j < N; j++) {
      (*u)[0][j] = 0.0;
      (*u)[M-1][j] = 1000.0;     /* Heat source */
   }
}

/* Print solution to standard output or a file */
void print_solution (char *filename, double **u)
{
   int i, j;
   char sep;
   FILE *outfile;

   if (!filename) { /* if no filename specified, print on screen */
      sep = '\t';   /* tab added for easier view */
      outfile = stdout;
   } else {
      sep = '\n';   /* for gnuplot format */
      outfile = fopen(filename,"w");
      if (outfile == NULL) {
         printf("Can't open output file.");
         exit(-1);
      }
   }

   /* Print the solution array */
   for (i = 0; i < M; i++) {
      for (j = 0; j < N; j++)
         fprintf (outfile, "%6.2f%c", u[i][j], sep);
      fprintf(outfile, "\n"); /* Empty line for gnuplot */
   }
   if (outfile != stdout)
      fclose(outfile);

}

double getMaxDiff(double* p,int arrLen){
    double max=p[0];
    for(int i=0;i<arrLen;i++){
        if (p[i]>max){
            max=p[i];
        }
    }
    return max;
}
void printdiffsArr(double diffs[]){
   printf("diffs[] is: \n");
   for (int i=0;i<thr_count;i++){
      printf("%f  ",diffs[i]);
   }
}
/* Entry function of the worker threads */
void *thr_func(void *arg) {//what do we want to pass in

   int thr_index=*(int*)arg;//store the current thread index
   //free(arg);
   printf("DB: receive index %d\n",thr_index);
   //e.g thr_index=0
   int start_row,end_row;
   //find the start row of current thread based on thread id
   start_row=step*thr_index;
   //if this is not the last thread
   if(thr_index!=thr_count-1){
      end_row=start_row+step;}
   //else(it is the last thread, set end_row as the last row)
   else {end_row=M-1;}
   //printf("start row of T%d: %d\n",thr_index,start_row);
  // printf("end row of T%d: %d\n",thr_index,end_row);


// (2) Add the worker's logic here
   //calculate new temp for once
   int i=1,j=1; 
   printf("DB: start for loop\n");
   double diff=0;
   for (i = 1; i < M-1; i++) {
         for (j = 1; j < N-1; j++) {
            w[i][j] = 0.25 * (u[i-1][j] + (u)[i+1][j] + (u)[i][j-1] + (u)[i][j+1]);
            if (fabs((w)[i][j] - (u)[i][j]) > diff)
               diff = fabs((w)[i][j] - (u)[i][j]);
         }
      } 
   return 1;
//((void*)result);

}


int find_steady_state (void)//main thread 
{
   //declare array of thread
   pthread_t threads[thr_count];
   //used to store the return value (diff) from the threads
   double diffs[thr_count];
   double *p=&(diffs[0]);//point p into the array: diffs
   double maxDiff;//to store the max diff among all the diffs returned by threads 
   //create threads
   for (int i=0;i<thr_count;i++){
      /*i is changing during this for loop, 
      and we can't ensure desired i can be passed to the thread function
      so we need to use memory allocation for passing i to each thread */
      int *a=malloc(sizeof(int));
      a=&i;
      if(pthread_create(&threads[i],NULL,&thr_func,a)!=0){
         return 1;//error in thread creation
      }
      //sleep(1);
   }
   //wait for all threads complete computation 
   for(int i=0;i<thr_count;i++){
      if(pthread_join(threads[i],(void**)&diffs[i])!=0){
         return 2;//error in thread join 
      }
   }

   //determine whether reach the eqm state 
   //1. find the max diff among all the diffs
   printf("print diffs[]\n");
   printdiffsArr(diffs);
   maxDiff=getMaxDiff(p,thr_count);

   

}
