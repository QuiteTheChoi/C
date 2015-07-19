#include <stdio.h>
#include <stdlib.h>

int num[200];

int add(int x, int y) {
	return (x + y);
}

int compute_fib(int n) {
	int i;
	if (num[n] == -1) {   //line 22/23
		if (n == 0){     //line 32
			i = 0;//goto line 54
		}
		else if (n == 1) {   //line 37 && .L7
			i = 1;
		}
		else {			//.L10
			i = add(compute_fib(n-2),compute_fib(n-1));	
		}
	}
	
	num[n] = i;
	return num[n];	
}	

int main(int argc, char** argv) {
    int n = atoi(argv[1]), i;
	
	for (i = 0; i<= 199; i++) {
		num[i] = -1;
	}
	
	printf("%d\n", compute_fib(n));
 	return 0;
} 