#include <stdio.h>

int main() 
{ 
  int array[10],i; 

  printf ("array: %p, &i: %p\n"); 
  printf ("i is offset %d from array\n", &i - array);

  for (i = 0; i <=10 ; i++) 
  { 
    printf ("%d: Writing 0 to address %p\n", i, &array[i]); 
    /*if (i == 10)
		continue;*/
	array[i]=0; /*code should never terminate*/ 
	
  } 
  return 0; 
} 
