all:  template getArg getRV rusageTest jacobi_sema jacobi_seq

template: jacobi_template.c
	gcc -pthread -o template jacobi_template.c
step: step.c 
	gcc -o step step.c
getRV: getReturnValue.c
	gcc -o getRV getReturnValue.c
pointer_arr: pointer_arr.c
	gcc -o pointer_arr pointer_arr.c
getrusage_thread: getrusage_thread.c
	gcc -pthread -o getrusage_thread getrusage_thread.c
template: jacobi_template.c
	gcc -pthread -o jacobi_template jacobi_template.c
getArg: getArg.c
	gcc -pthread -o getArg getArg.c
rusageTest: rusageTest.c
	gcc -o rusageTest rusageTest.c
jacobi_sema: jacobi_sema.c
	gcc -pthread -o jacobi_sema jacobi_sema.c
jacobi_seq: jacobi_seq.c
	gcc -o jacobi_seq jacobi_seq.c