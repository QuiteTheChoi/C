#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/*struct for creating a number*/
struct number_ {
	char type;
	char *numString;
	int negative;
	int equiv; 
};

typedef struct number_ number;

enum states {
	undetermined,
	mightBeDecFirstNum,
	mightBeDec,
	mightBeBin,
	mightBeOct,
	mightBeHexFirstChar,
	mightBeHexSecChar,
	mightBeHexThirdChar,
	mightBeHex,
} curr_State;

int isBinary(char* numB) {
	while (*numB != '\0') {
		if (*numB != '0' && *numB != '1') {
			return 1;
		}
		numB++;
	}
	return 0;
}

int isOctal(char* numO) {
	while (*numO != '\0') {
		if (*numO < '0' || *numO > '7') {
			return 1;
		}
		numO++;
	}
	return 0;
}

int isHex (char* numH) {
	while (*numH != '\0') {
		switch(curr_State) {
			case(mightBeHex): {
				if ((*numH >= '0' && *numH <= '9')|| (*numH >= 'a' && *numH <= 'f') || (*numH >= 'A' && *numH <= 'F'))  {
					break;
				}
				else
				return 1;
			}
		}
		numH++;
	}
	if (curr_State == mightBeHexFirstChar || curr_State == mightBeHexSecChar || curr_State == mightBeHexThirdChar)
		return 1;
	
	return 0;
}

int isDecimal(char* numD) {
	while (*numD != '\0') {
		switch(curr_State) {
			case(mightBeDecFirstNum): {
				if (*numD >= '1' && *numD <= '9') {
					curr_State = mightBeDec;
					break;
				}
				else if ((int)strlen(numD) == 1 && isdigit(*numD)) {
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
 * Returns a 1 if number entered is found to be an invalid format. */
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
	else if (strlen(num) == 1) {						//string must contain a type and at least one digit
		return 1;
	}
	else {
		tempType = num[0];
		tempNum = strdup(&num[1]);
	}

	if (tempType == 'b')
	{
		curr_State = mightBeBin;
		return isBinary(tempNum);
	}
	else if (tempType == 'o')
	{
		curr_State = mightBeOct;
		return isOctal(tempNum);
	}
	else if (tempType == 'x')
	{
		curr_State = mightBeHex;
		return isHex(tempNum);
	}
	else if (tempType == 'd')
	{
		curr_State = mightBeDecFirstNum;
		return isDecimal(tempNum);		
	}
	curr_State = undetermined;
	free(tempNum);
	return 1;
}

int strToInt(number *ptr) {
	int result = 0;
	int resultTemp = 0;
	char* num = ptr -> numString;
	int len = (int)strlen(ptr -> numString);
	
	/*for (num; *num != '\0'; num++) {
		result = result * 10 + (*num - '0');
		if (resultTemp > result) {
			return 1;
		}
		resultTemp = result;
	}*/
	
	for (num; *num != '\0'; num++) {
		switch(ptr -> negative) {
			case(0): {
				result = result * 10 + (*num - '0');
				if (resultTemp > result) {
					return 1;
				}
				break;
			}
			case(1): {
				result = result * 10 + ((*num - '0')*-1);
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

//return 1 for error;
int binToInt(number* ptr) {
	char* numB = ptr -> numString;
	int result = 0;
	int resultTemp = 0;
	for (numB; *numB != '\0'; numB++) {
		switch(ptr -> negative) {
			case(0): {
				result = result * 2 + (*numB - '0');
				if (resultTemp > result) {
					return 1;
				}
				break;
			}
			case(1): {
				result = result * 2 + ((*numB - '0')*-1);
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

int octToInt(number* ptr) {
	char* numO = ptr -> numString;
	int result = 0;
	int resultTemp = 0;
	for (numO; *numO != '\0'; numO++) {
		switch(ptr -> negative) {
			case(0): {
				result = result * 8 + (*numO - '0');
				if (resultTemp > result) {
					return 1;
				}
				break;
			}
			case(1): {
				result = result * 8 + ((*numO - '0')*-1);
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

int hexToInt(number* ptr) {
	char* numX = ptr -> numString;
	int result = 0;
	int resultTemp = 0;
	int i = 0;
	int y = 0;
	int hexNum;
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

//return 1 for error
int convertToInt(number* ptr) {
	switch(ptr -> type) {
		case('b'): {
			if (binToInt(ptr) == 1) 
				return 1; 
			else 
				return 0;
		}
		case('o'): {
			if (octToInt(ptr) == 1) 
				return 1; 
			else 
				return 0;
		}
		case('d'): {
			if (strToInt(ptr)==1)
				return 1;
			else
				return 0;
		}
		case('x'): {
			if (hexToInt(ptr) == 1)
				return 1;
			else
				return 0;
		}
	}
	return 0;
}

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

char* toBinary(int ans) {
	char* result = (char*) malloc(sizeof(char)*33);
	int i = 0;
	int mem = ans;
	
	if (ans == 0) {
		result[0] = '0';
		result[1] = '\0';
		return result;
	}
	
	while (ans != 0) {
		int b = ans%2;
		if (b < 0)
			b = b*-1;
		printf("b is: %d\n",b);
		result[i] = b + '0';
		i++;
		ans = ans/2;		
	}
	
	if (mem < 0) {
		result[i] = '-';
		i++;
	}
	
	result[i] = '\0';
	
	reverseStr(result);
	
	return result;
}

char* toDec(int ans) {
	char* result = (char*) malloc(sizeof(char)*33);
	int i = 0;
	int mem = ans;
	
	if (ans == 0) {
		result[0] = '0';
		result[1] = '\0';
		return result;
	}
	
	while (ans != 0) {
		int b = ans%10;
		if (b < 0)
			b = b*-1;
		result[i] = b + '0';
		i++;
		ans = ans/10;		
	}
	
	if (mem < 0) {
		result[i] = '-';
		i++;
	}
	
	result[i] = '\0';
	
	reverseStr(result);
	
	return result;
}

char* toOctal(int ans) {
	char* result = (char*) malloc(sizeof(char)*33);
	int i = 0;
	int mem = ans;
	
	if (ans == 0) {
		result[0] = '0';
		result[1] = '\0';
		return result;
	}
	
	while (ans != 0) {
		int b = ans%8;
		if (b < 0)
			b = b*-1;
		result[i] = b + '0';
		i++;
		ans = ans/8;		
	}
	
	if (mem < 0) {
		result[i] = '-';
		i++;
	}
	
	result[i] = '\0';
	
	reverseStr(result);
	
	return result;
}

char* toHexa(int ans) {
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
	
	if (mem < 0) {
		result[i] = '-';
		i++;
	}
	
	
	
	result[i] = '\0';
	reverseStr(result);
	
	return result;
}

int solveEqn(char op, char type, number* num1, number* num2) {
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

char* convertAns (char type, int ans) {
	if (type == 'b' || type == 'B')
		return toBinary(ans);
	if (type == 'x' || type == 'X')
		return toHexa(ans);
	if (type == 'o' || type == 'O')
		return toOctal(ans);
	if (type == 'd' || type == 'D')
		return toDec(ans);
}

int checkResult(char type, int ans, number* num1, number* num2) {
	int ansTemp = 0;
			
	if (type == '+') {
		printf("1");
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
		printf("%d\n",argc);
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
	
	printf("Value stored in num1: %d\n",num1 -> equiv);
	printf("Value stored in num2: %d\n",num2 -> equiv);
	
	if ((num1 -> equiv == 0 || num2 -> equiv) && argv[1][0] == '*') {
		printf("RESULT: %c0",argv[4][0]);
		return 0;
	} 
	
	result = solveEqn(argv[1][0],argv[4][0],num1,num2); 
	
	if (checkResult(argv[1][0],result,num1,num2)==1) {
		printf("The answer is longer than 32 bits\n");
		return 0; 
	}
	
	printf("Decimal answer is: %d\n",result);
	
	resultStr = convertAns(argv[4][0],result);
				
	//delete(num1,num2,resultStr);
	
	return 0;
}

