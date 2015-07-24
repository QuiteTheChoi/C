#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "nCr.h"
#include "formula.h"

numState curr_state = undetermined;

int checkInt(char* ptr) {
	while (*ptr != '\0') {
		if (curr_state == mightBeDecFirstNum) {
			if ((*ptr >= '0' && *ptr <= '9') && strlen(ptr) == 1) {
				return 0;
			}
			else if (*ptr >= '1' && *ptr <= '9') {
				curr_state = mightBeDec;
			}
			else {
				return 1;
			}			
		}
		else {
			if (*ptr >= '0' && *ptr <= '9') {
			}
			else {
				return 1;
			}
		}
		ptr++;
	}		
	return 0;
}

int main(int argc, char** argv) {
	struct timeval start, end;
	gettimeofday(&start, NULL);
	
	if (argc < 2) {
		fprintf(stderr,"Not enough arguments\n");
		return 0;
	}
	else if (argc > 2) {
		fprintf(stderr,"Too many arguments\n");
		return 0;
	}
	if (strcmp(argv[1],"-h") == 0) {
		printf("Usage: formula <positive integer>\n");
		return 0;
	}	
		
	curr_state = mightBeDecFirstNum;
	if (checkInt(argv[1]) == 1) {
		fprintf(stderr,"Input not in positive integer form\n");
		return 0;
	}	
	int n = atoi(argv[1]);
	
	if (factorial(n) == 0) {
		fprintf(stderr,"Overflow detected\n");
		return 0;
	}
	
	printf("(1 + x)^%d = 1",n);
	
	int i = 1, fact;
	for (i; i <= n; i++) {
		fact = nCr(n,i);
		printf(" + %d*x^%d",fact,i);
	}
	printf("\n");
	gettimeofday(&end, NULL);
	
	printf("%ld microseconds\n", ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));

	return 0;
}
	


