all:   getrusage  jacobi_seq jacobi_sema

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
jacobi_sema: jacobi_sema.c
	gcc -pthread -o jacobi_sema jacobi_sema.c
jacobi_seq: jacobi_seq.c
	gcc -o jacobi_seq jacobi_seq.c
getrusage: getrusage.c
	gcc -o getrusage getrusage.c
