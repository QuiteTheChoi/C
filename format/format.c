#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "format.h"

//Checks to make the bit string is 32 bits
int isBinary(char* ptr) {
	if (strlen(ptr) != 32)
		return 1;
	
	for (ptr; *ptr != '\0'; ptr++) {
		if (*ptr != '0' && *ptr != '1') 
			return 2;
	}
	
	return 0;
}

//Reverses the string
int reverseStr(char* str) {
   int i = strlen(str)-1;
   int j = 0;
   
   char temp;
   
   while (j < i ) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i--;
		j++;
   }
   
   return 0;
}

//Converts the bit string to two's complement integer
char* convertToInt(char* ptr) {
	int i = 0;
	int result = 0;
	int negative = 0;
	char* intResult = (char*) malloc(sizeof(char)*34);
	
	if (ptr[0] == '1') {
		negative = 1;
		reverseStr(ptr);
		char* temp = ptr;
		char* reverse = ptr;
		for (temp; *temp != '1' && *temp != '\0'; temp++) {
			*temp = '1';
		}
		if (*temp == '1') {
			*temp = '0';
		}
		reverseStr(ptr);
		
		for (reverse; *reverse != '\0'; reverse++) {
			if (*reverse == '1') {
				*reverse = '0';
			}
			else {
				*reverse = '1';
			}
		}
	}
	for (ptr; *ptr != '\0'; ptr++) {
		if (negative == 1) {
			result = result * 2 + ((*ptr - '0')*-1);
		}
		else {
			result = result * 2 + (*ptr - '0');
		}
	}
	
	if (result == 0) {
	intResult[0] = '0';
	intResult[1] = '\0';
	return intResult;
	}
	
	for (result; result != 0; result = result/10) {
		int b = result%10;
		if (b < 0) {
			b = b*-1;
		}
		intResult[i] = b + '0';
		i++;
	}
	
	if (negative == 1) {
		intResult[i] = '-';
		i++;
	}
	
	intResult[i] = '\0';
	reverseStr(intResult);
	return intResult;
}

//Converts the bit string to single precision floating-point format
char* convertToFloat(char* ptr) {
	int negative;
	int exp = 0;
	float mant = 1.0;
	int expAllOnes = 1;
	int mantHasOne = 0;
	int count = 1;
	
	char* floatResult = (char*) malloc(sizeof(char)*16);
	char* tempResult = floatResult;
		
	negative = ptr[0] -'0';
	int i = 1;
	for (i; i <= 8; i++) {
		if (ptr[i] == '0')
			expAllOnes = 0;
		exp = exp*2 + (ptr[i] - '0');
		
	}
	
	int min = 1;
	int max = 23;
	
	if (exp == 0) {
		min = 0;
		max = 22;
		mant = 0.0;
	}
	
	char* temp = &ptr[9];
	int j = min;
	for (j; j <= max; j++) {
		if (*temp == '1') {
			mant = mant + pow(2, (j*-1));
		}
		temp++;
	}
	
	if (exp == 255) {
		if (mant != 1.0) {
			printf("NaN\n");
			exit(0);
		}
		else {
			if (negative == 1) {
				printf("-inf\n");
				exit(0);
			}
			else {
				printf("inf\n");
				exit(0);
			}
			
		}
		
	}
	else if (exp == 0 && mant == 0.0) {
		if (negative == 0) {
			printf("0.0e0\n");
			exit(0);
		}
		else {
			printf("-0.0e0\n");
			exit(0);
		}
	}	
	
	float ans = mant*pow(2,(exp-127));
	int exponent = 0;
	float mantissa = ans;
	exponent = log10(mantissa);
	
	if (exponent < 0) {
		exponent--;
		int expTemp = exponent;
		while (expTemp != 0) {
			mantissa = mantissa *10;
			expTemp++;
		}
	}
	else {
		int expTemp = exponent;
		while (expTemp != 0) {
			mantissa = mantissa/10;
			expTemp--;
		}
	}
	
	if (negative == 1) {
		*floatResult = '-';
		floatResult++;
	}
	
	int y = 0;	
	for (y; y < 7 && mantissa != 0;y++) {
		if (y == 1) {
			*floatResult = '.';
			floatResult++;
		}		
		*floatResult = (int)mantissa%10 + '0';
		mantissa = (mantissa - (*floatResult-'0'))*10;
		floatResult++;
	}
	
	*floatResult = 'e';
	floatResult++;
		
	if (exponent == 0) {
		*floatResult = '0';
		floatResult++;
	}
	
	if (exponent < 0) {
		*floatResult = '-';
		floatResult++;
	}
	
	char* reverseExp = floatResult; 
	for (exponent; exponent != 0; exponent/=10) {
		int b = exponent%10;
		if (b < 0) {
			b = b*-1;
		}
		*floatResult = b + '0';
		floatResult++;
	}
	
	reverseStr(reverseExp);
	
	*floatResult = '\0';
	
	return tempResult;
}

int main(int argc, char** argv) {
	int stop = 0;
	char* result;
	
	if (argc < 3) {
		printf("Not enough arguments!");
		return 0;
	}
	
	if (argc > 3) {
		printf("Too many arguments!");
		return 0;
	}
	
	if (isBinary(argv[1]) == 1) {
		printf("Bit sequence is not 32 bits\n");
		stop = 1;
	}
	else if (isBinary(argv[1]) == 2) {
		printf("Bit sequence contains digits other than 1 and 0\n");
		stop = 1;
	}
	
	if (strcasecmp(argv[2],"int") == 0) {
		result = convertToInt(argv[1]);
	}
	else if (strcasecmp(argv[2],"float") == 0) {
		result = convertToFloat(argv[1]);
	}
	else {
		printf("Output entered is not valid form\n");
		stop = 1;
	}
	
	if (stop == 1) {
		return 0;
	}
		
	printf("RESULT: %s\n",result);
	free(result);
	return 0;
}
