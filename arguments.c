#include <stdio.h>

int main (int argc, char** argv) {
	int i;
	for (i = 0; i < argc; i++) {
		fprintf(stdout,"This is string %d: %s. \n", i, argv[i]);
		fprintf(stdout, "The first character: %c. \n", argv[i][0]);
	}
	return 0;
}
