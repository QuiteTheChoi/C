#include <stdio.h>

struct point {
	int x;
	int y;
};
int main () {
	struct point Q = {{3},{5}};
	printf("%d %d\n", Q.x,Q.y);
	return 0;
}