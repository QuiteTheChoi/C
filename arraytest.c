#include <stdio.h>

int main()
{
	int array[10],i;
	
	for (i = 0; i <=11 ; i++)
	{
		array[i]=0; /*code should never terminate*/
		printf("test \n");
			
	}
	printf("%d \n", sizeof(array)/sizeof(int));
	return 0;
}
	
