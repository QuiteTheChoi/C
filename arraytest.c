#include <stdio.h>

int main()
{
	int array[10],i;
	for (i = 0; i <10 ; i++)
	{
		array[i]=0; /*code should never terminate*/
		
	}
	printf("%d", sizeof(array)/sizeof(int));
	return 0;
}
	