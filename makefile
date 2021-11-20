all:  template

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