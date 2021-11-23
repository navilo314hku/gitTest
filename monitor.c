/*program description
• Filename: monitor.c
• Student’s name: Lo Ngai Chak
• Student Number: 3035685859
• Development platform: MacOS, test with workbench2
• Remark – describe how much you have completed
In my program, I am able to finish all the parts except supporting pipeline.
So, my program could execute single program with any number of commmand arguments.
My program will then display the details of program execution(real, user, system) time,
page fault, child pid, child termination status

Also, the parent process will not be kill under SIGINT signal, but my child 
process program will be killed under SIGINT signal. 

Implementation idea: 
Parent process of the program will first check whether there are programs to be 
executed. And if there are programs to be executed, parent process will generate
a child process which will execute the program with execvp() .

Parent process will then wait the child process program to be terminated by function
wait4(), which allow the parent to get the child process information especially the 
time (by struct rusage)



*/

#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/wait.h> 
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <string.h>
const char* TerminationStatus(int status);

int main(int argc, char* argv[]){
	int fd[2];//used for sending start time from child to parent process
	int execSucess;	
	if (argc>1){//if there is a program to be executed
		//printf("There are %d command argument for the monitor\n",argc);
		char* progArgv[argc-1];// this array of string will be passed to the prog to be exec
		for (int i=0;i<argc-1;i++){//update the entity of progArgv by the 2nd element to the last element of argv
			printf("i=%d\n",i);
			progArgv[i]=argv[i+1];
			progArgv[i]=argv[i+1];
		}
		progArgv[argc-1]=NULL;
		//split the argv into prog1Argv, prog2Argv
		for (int i=0;i<argc-1;i++){

		}
		if (pipe(fd)==-1){//open a pipe
			printf("Error occured with opening pipe\n");
			return 1;
		}
		int pid=fork();//create child process
		
		if(pid<0){//case: failed in creating child process
			printf("Fork() failed\n");
			exit(-1);
		}
		else if(pid==0){//child process
			printf("child process created\n");
			//Process with id: 12557 created for the command: xxxxx
			printf("Process with id: %d created for the command: %s\n",getpid(),argv[1]);
			close(fd[0]);//close read end of pipe
			struct timeval progStartTime;
			gettimeofday(&progStartTime,NULL);	//get wallclock time
			//send the start time of the prog to the parent 
			write(fd[1],&progStartTime,sizeof(progStartTime));//write start time to the pipe
			close(fd[1]);//end of writing to the pipe, close pipe
			if (execvp(argv[1], progArgv)==-1){
				execSucess=-1;//failed in exec prog
				printf("exec: : No such file or directory\n");
				return 1;
			}
				
			else{execSucess=1;}//success in exec program 

			printf("execvp() Failed"); 
			exit(-1);
		}
		else 
		{	
		// Parent Process
			//handle sigint and sent sigint to the child process 
			int status;
			int options;
			struct timeval start,finish;//for calculate the usertime
			long page_fault;
			long context_switch;
			struct rusage rus; //GET system,user time and  context switch 

			signal(SIGINT,SIG_IGN);//ignore sigint signal 
			wait4(pid,&status,options,&rus);//wait for child terminate 
			gettimeofday(&finish,NULL);	//get wallclock time
			read(fd[0],&start,sizeof(start));//read the wallclock start time of the prog from the pipe
			close(fd[0]);//close the read end of pipe;
			close(fd[1]);//close the write end of pipe
			//calculation of real, user, system times 
			double realFinishTime = (double)finish.tv_sec+ (double)finish.tv_usec*1e-6;
			double realStartTime=(double)start.tv_sec+(double)start.tv_usec*1e-6;
    		double realTime=realFinishTime-realStartTime;
    		double userTime=(double)rus.ru_utime.tv_sec+(double)+rus.ru_utime.tv_usec*1e-6;
    		double sysTime=(double)rus.ru_stime.tv_sec+(double)+rus.ru_stime.tv_usec*1e-6;

    		printf("The command \"%s\" is interrupted by the signal number = %d %s\n",
    			argv[1],status,TerminationStatus(status));//print child termination status 

    		printf("real: %.3f s, user: %.3f s, system: %.3f s\n",realTime,userTime,sysTime);//print time detail
			printf("no. of page faults: %ld\n",page_fault);
			printf("no. of context switches: %ld\n",context_switch);

			printf("\n");
		}
	}
	//else no program to be exec 
	return 0;
}

const char* TerminationStatus(int status){
	if (status==0) return "";
	else if (status==1) return "(SIGHUP)";
	else if (status==2) return "(SIGINT)";
	else if (status==3) return "(SIGQUIT)";
	else if (status==4) return "(SIGILL)";
	else if (status==5) return "(SIGTRAP)";
	else if (status==6) return "(SIGABRT)";
	else if (status==8) return "(SIGFPE)";
	else if (status==11) return "(SIGSEGV)";
	else if (status==13) return "(SIGPIPE)";
	else if (status==14) return "(SIGALRM)";
	else if (status==2) return "(SIGTERM)";
	else return "";

}














