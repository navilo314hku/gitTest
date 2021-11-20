#include <stdio.h>
int main(){
  int arr[]={1,2,3};
	
	int len=(int)(sizeof(arr)/sizeof(arr[0]));
	int *p;
	for(p=&arr[0];p<=&arr[len-1];p++){
		printf("%d\n",*p);
	}
	return 0;
}