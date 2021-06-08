
#include <stdio.h>
#include <stdlib.h>

int rfib(int arg);

int main(void){

  int results[5], i;
  int data[] = {3, 9, 18, 23, 25};
  int ndata  = 5;

	for(i=0; i<ndata; ++i){
	  printf("\ncalling fib with %d\n", data[i]);
	  results[i] = rfib(data[i]);
	  printf(" called fib with %d, result is %d\n", data[i], results[i]);
	}

	printf("\nFibonacci numbers:\n");
	for(i=0; i<ndata; ++i){
	  printf("   FIB of %d\t is %d\n", data[i], results[i]);
	}

	return 0;
}

int rfib(int arg){

  int fn1, fn2;


	if (arg == 0) return 0;
	
	if (arg == 1) return 1;
	
	fn1 = rfib (arg - 1);
	fn2 = rfib (arg - 2);
	return (fn1 + fn2);
}
