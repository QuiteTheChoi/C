int factorialn (int num, int ans) {
	if (num == 0) {
		return ans;
	}
	else {
		if (ans*num < ans) {
			fprintf(stderr,"Overflow detected");
			return 0;
		}
		return factorialn(num-1,ans*num);
	}
}

int factorial (int num) {
	return factorialn(num,1);
}

int nCr(int n, int r) {
	int ans;
	int ans = (int) factorial(n)/(factorial(r)*factorial(n-r));
	return ans;
}

int main(int argc, char** argv) {
	if (argc < 1) {
		fprintf(stderr,"Not enough arguments");
		return 0;
	}
	else if (argc > 1) {
		fprintf(stderr,"Too many arguments");
		return 0;
	}
	
	int n = atoi(argv[1]);
	
	printf("(1 + x)^%d = 1 ",n);
	
	int i = 1, fact;
	for (i; i <= n; i++) {
		fact = nCr(10,i);
		printf(" + %d*x^%d",fact,i);
	}
	printf("\n");
	
	return 0;
}
	


