#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "calc.h"

numState curr_State = undetermined;

/*checks the string for anything that isn't a '0' or '1'*/
int isBinary(char* numB) {
	while (*numB != '\0') {
		if (*numB != '0' && *numB != '1') {
			return 1;
		}
		numB++;
	}
	return 0;
}

/*checks the string for anything that isn't (0-7)*/
int isOctal(char* numO) {
	while (*numO != '\0') {
		if (*numO < '0' || *numO > '7') {
			return 1;
		}
		numO++;
	}
	return 0;
}

/*checks the string for anything that isn't (0-9), (a-f), (A-F)*/
int isHex (char* numH) {
	while (*numH != '\0') {
		if ((*numH >= '0' && *numH <= '9')|| (*numH >= 'a' && *numH <= 'f') || (*numH >= 'A' && *numH <= 'F'))  {
		}
		else {
			return 1; 
		}
		numH++;		
	}
	return 0;	
}

/*checks the string for anything that isn't a digit, the first number can only be 1-9*/
int isDecimal(char* numD) {
	while (*numD != '\0') {
		switch(curr_State) {
			case(mightBeDecFirstNum): {
				if (*numD >= '1' && *numD <= '9') {
					curr_State = mightBeDec;
					break;
				}
				else if ((int)strlen(numD) == 1 && isdigit(*numD)) {			//if its any digit including 0 and the length is one, that is ok. 
					return 0;
				}
				else
					return 1;
			}
			case(mightBeDec): {
				if (*numD >= '0' && *numD <= '9') {
					curr_State = mightBeDec;
					break;
				}
				else
					return 1;
			}
		}
		numD++;
	}
	return 0;
}

/* Will take in both numbers to validate that the numbers are entered correctly.
 * Will run the numbers to other functions based on the type specified by user. 
 * Returns a 1 if number entered is found to be an invalid format.*/
int validateToken(char* num) {
	char tempType;
	char* tempNum;
	
	if (num[0] == '-' && strlen(num) <= 2) {         	//to have a negative sign means you must have at least a '-', a type (b,o,x,d) 
		return 1;										// and at least one digit.
	}
	else if (num[0] == '-') {
		tempType = num[1];
		tempNum = strdup(&num[2]);
	}
	else if (strlen(num) <= 1) {						//string must contain a type and at least one digit
		return 1;
	}
	else {
		tempType = num[0];
		tempNum = strdup(&num[1]);
	}

	if (tempType == 'b' || tempType == 'B')								//determination of type and whether number entered is valid. 
	{
		return isBinary(tempNum);
	}
	else if (tempType == 'o'|| tempType == 'O')
	{
		return isOctal(tempNum);
	}
	else if (tempType == 'x' || tempType == 'X')
	{
		return isHex(tempNum);
	}
	else if (tempType == 'd' || tempType == 'D')
	{
		curr_State = mightBeDecFirstNum;
		return isDecimal(tempNum);		
	}
	curr_State = undetermined;
	free(tempNum);
	return 1;
}

/*Converts an octal, decimal or binary string to base 10 quivalent. 
 * Returns 1 if a number longer than 32 bits is detected.*/
int strToInt(number *ptr) {
	int result = 0;
	int j = 0;
	int i = 0;
	
	char* num = ptr -> numString;
		
	if (ptr -> type == 'd' || ptr -> type == 'D') {
		j = 10;
	}
	else if (ptr -> type == 'o' || ptr -> type == 'O') {
		j = 8;
	}
	else if (ptr -> type == 'b' || ptr -> type == 'B') {
		j = 2;
	}
	
	int resultTemp = 0;
	for (num; *num != '\0'; num++) {
		switch(ptr -> negative) {
			case(0): {
				result = result * j + (*num - '0');
				if (resultTemp > result) {
					return 1;
				}
				break;
			}
			case(1): {
				result = result * j + ((*num - '0')*-1);
				if (resultTemp < result) {
					return 1;
				}
				break;
			}
		}
		resultTemp = result;
	}
	
	ptr -> equiv = result;
	return 0;
}

/*Converts a hexadecimal string to base 10 quivalent. 
 * Returns 1 if a number longer than 32 bits is detected.*/
int hexToInt(number* ptr) {
	
	char* numX = ptr -> numString;
	int result = 0;
	int resultTemp = 0;
	int i = 0;
	int y = 0;
	int hexNum = 0;
	for (numX; *numX!= '\0'; numX++) {
		i++;
	}
	
	numX--;
	for (y; y < i; y++) {
		if (isdigit(*numX)) {
			hexNum = *numX - '0';
		}
		else if (*numX == 'a' || *numX == 'A') {
			hexNum = 10;
		}
		else if (*numX == 'b' || *numX == 'B') {
			hexNum = 11;
		}	
		else if (*numX == 'c' || *numX == 'C') {
			hexNum = 12;
		}
		else if (*numX == 'd' || *numX == 'D') {
			hexNum = 13;
		}
		else if (*numX == 'e' || *numX == 'E') {
			hexNum = 14;
		}
		else if (*numX == 'f' || *numX == 'F') {
			hexNum = 15;
		}
		switch(ptr -> negative) {
			case(0): {
				result = result + hexNum*(int)pow(16,y);
				if (resultTemp > result) {
					return 1;
				}
				break;
			}
			case(1): {
				result = result + (hexNum*(int)pow(16,y)*-1);
				if (resultTemp < result) {
					return 1;
				}
				break;
			}
		}
		resultTemp = result;
		numX--;
	}
	
	ptr -> equiv = result;
	
	return 0;
}

/*converts user input string into a base 10 number, will 
 * return 1 if number conversion leads to somethign bigger
 * than 32 bit. Calls on seperate functions based on the type
 * of input*/
int convertToInt(number* ptr) {
		if (ptr -> type == 'd' || ptr -> type == 'D' || ptr -> type == 'o' || ptr -> type == 'O' || ptr -> type == 'b' || ptr -> type == 'B') {
			if (strToInt(ptr) == 1) {
				return 1;
			}
			else {
				return 0;
			}
		}
		else if (ptr -> type == 'x' || ptr -> type == 'X') {
			if (hexToInt(ptr) == 1) {
				return 1;
			}
			else {
				return 0;
			}
		}
	return 0;
}

/* creates token number struct which holds information 
 * about the one of numbers that the user inputted will return NULL 
 * if number is greater than 32 bits. Holds negative indicator, base 10 
 * equivalent, type of input and the number string itself*/
number* numCreate (char* str) {
	number *ptr = (number*) malloc (sizeof(number));
	ptr -> equiv = 0;	
	
	if (str[0] == '-') {
		ptr -> negative = 1;
		ptr -> type = str[1];
		ptr -> numString = strdup(&str[2]);
	}
	else {
		ptr -> negative = 0;
		ptr -> type = str[0];
		ptr -> numString = strdup(&str[1]);
	}
	
	if (convertToInt(ptr) == 1)
		return NULL;
	
	return ptr;
}

//Reversese a string. 
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

/*Converts answer to binary, octal or decimal string with type and negative*/
char* toStr(char type, int ans) {
	char* result = (char*) malloc(sizeof(char)*33);
	int i = 0;
	int num = 0;
	int mem = ans;
	
	if (type == 'd' || type == 'D') {
		num = 10;
	}
	else if (type == 'o' || type == 'O') {
		num = 8;
	}
	else if (type == 'b' || type == 'B') {
		num = 2;
	}
	
	if (ans == 0) {
		result[0] = type;
		result[1] = '0';
		result[2] = '\0';
		return result;
	}
	
	while (ans != 0) {
		int b = ans%num;
		if (b < 0)
			b = b*-1;
		result[i] = b + '0';
		i++;
		ans = ans/num;		
	}
	
	result[i] = type;
	i++;
	
	if (mem < 0) {
		result[i] = '-';
		i++;
	}
	
	result[i] = '\0';
	
	reverseStr(result);
	
	return result;
}

/*Converts answer to hexadecimal string with the type and negative. */
char* toHex(int ans) {
	char* result = (char*) malloc(sizeof(char)*33);
	int i = 0;
	int mem = ans;
	
	if (ans == 0) {
		result[0] = '0';
		result[1] = '\0';
		return result;
	}
	
	if (ans < 0)
		ans = ans*-1;
	
	while (ans != 0) {
		int b = ans%16;
		if (b < 0)
			b = b*-1;
		if (b == 10) {
			result[i] = 'a';
		}
		else if (b == 11) {
			result[i] = 'b';
		}
		else if (b == 12) {
			result[i] = 'c';
		}
		else if (b == 13) {
			result[i] = 'd';
		}
		else if (b == 14) {
			result[i] = 'e';
		}
		else if (b == 15) {
			result[i] = 'f';
		}
		else {
			result[i] = b + '0';
		}
		i++;
		ans = ans/16;		
	}
	
	result[i] = 'x';
	i++;
	
	if (mem < 0) {
		result[i] = '-';
		i++;
	}
		
	result[i] = '\0';
	reverseStr(result);
	
	return result;
}

/*Calls different function based on what type output is needed*/
char* convertAns (char type, int ans) {
	if (type == 'b' || type == 'B' || type == 'o' || type == 'O' || type == 'd' || type == 'D')
		return toStr(type, ans);
	else 
		return toHex(ans);
}

/*Checks the answer to make sure the answer is not longer than
 * 32 bits. For addition, if both numbers are positive, the result should be 
 * greater than either number and vice versa for two negative numbers. A positive
 * number and a negative number would not have errors by this stage. 
 * 
 * If the operation is subtraction, we need to test only when there 
 * is a negative and a positive number. If the first number is negative, 
 * the answer should be less than that first number. If the first number
 * is positive, the answer should greated than the first number. 
 * 
 * For multiplication, division of the answerby one 
 * number (zero has been taken care of) should equal the other 
 * number*/
int checkResult(char type, int ans, number* num1, number* num2) {
	int ansTemp = 0;
			
	if (type == '+') {
		if ((num1 -> negative == 1)&&(num2 -> negative == 1)) {
			if ((ans > num1 -> equiv)||(ans > num2 -> equiv))
				return 1;
		}
		else if ((num1 -> negative == 0)&&(num2 -> negative == 0)) {
			if ((ans < num1 -> equiv)||(ans < num2 -> equiv))
				return 1;
		}
	}
	if (type == '-'){
		if ((num1 -> negative == 0)&&(num2 -> negative == 1)) {
			if (ans < num1 -> equiv)
				return 1;
			}
		else if ((num1 -> negative == 1) && (num2 -> negative == 0)) {
			if (ans > num1 -> equiv)
				return 1;		
		}		
	}
	if (type == '*') {
		ansTemp =  ans/(num1 -> equiv);
		if (ansTemp != num2-> equiv)
		return 1;
	}
	return 0;
}

//Solves eqn in base 10 math
int solveEqn(char op, number* num1, number* num2) {
	int ansTemp;
	int x = num1 -> equiv;
	int y = num2 -> equiv;
		
	if (op == '+') {
		ansTemp = x + y;
	}
	if (op == '-') {
		ansTemp = x - y;
	}
	if (op == '*') {
		ansTemp = x * y;
	}
	
	return ansTemp;	
}

//deletes the number structs and string
void delete (number* num1, number* num2, char* str) {
	free(num1);
	free(num2);
	free(str);
}
/*main will take in five arguments to perform a calculation called by user. They will be able to input numbers 
 * in octal, hexadecimal, decimal and binary. They will also be able to output answers in one of those four types. 
 * negative numbers maybe used.  */
int main (int argc, char** argv) {
	int result;
	char* resultStr;
	int stop = 0;
	
	if (argc < 5) {
		fprintf(stdout,"Not enough arguments!\n");
		return 0;
	}
	else if (argc > 5) {
		fprintf(stdout,"Too many arguments!\n");
		return 0;
	}
	
	if (((int)strlen(argv[1]) != 1) || (argv[1][0] != '+' && argv[1][0] != '-' && argv[1][0] != '*')) {
		fprintf(stdout,"Invalid operation entered, please try again\n");
		stop = 1;
	}
		
	if (validateToken(argv[2]) == 1 && validateToken(argv[3]) == 1) {
		fprintf(stdout,"First and second number arguments are invalid\n");
		stop = 1;
	}
	else if (validateToken(argv[2]) == 1) {
		fprintf(stdout,"First number argument is invalid\n");
		stop = 1;
	}
	else if (validateToken(argv[3]) == 1) {
		fprintf(stdout,"Second number argument is invalid\n");
		stop = 1;
	}
	
	if ((strlen(argv[4]) != 1) || (argv[4][0] != 'b' && argv[4][0] != 'o' && argv[4][0] != 'x'&& argv[4][0] != 'd' &&argv[4][0] != 'B' && argv[4][0] != 'O' && argv[4][0] != 'X' && argv[4][0] != 'D')) {
		fprintf(stdout,"Invalid output conversion entered, please try again\n");
		stop = 1;
	}
	
	if (stop == 1) {
		return 0;
	}
	
	number* num1 = numCreate(argv[2]);
	number* num2 = numCreate(argv[3]);
	
	if (num1 == NULL && num2 == NULL) {
		printf("First and second value is greater than 32bits\n");
		return 0;
	}
	else if (num1 == NULL) {
		printf("First value is greater than 32bits\n");
		return 0;
	}
	else if (num2 == NULL) {
		printf("Second value is greater than 32bits\n");
		return 0;
	}
	
	if ((num1 -> equiv == 0 || num2 -> equiv == 0) && argv[1][0] == '*') {
		printf("RESULT: %c0\n",argv[4][0]);
		return 0;
	} 
	
	result = solveEqn(argv[1][0],num1,num2); 
	
	if (checkResult(argv[1][0],result,num1,num2)==1) {
		printf("The answer is longer than 32 bits\n");
		return 0; 
	}
	
	resultStr = convertAns(argv[4][0],result);
	printf("%s\n",resultStr);				
	delete(num1,num2,resultStr);
	
	return 0;
}
