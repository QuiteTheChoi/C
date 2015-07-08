#include <stdio.h>
#include <string.h>

/*struct for creating a number*/
struct number_ {
	char type;
	char *numString;
	int negative;
};

typedef struct number_ number;

enum states {
	undetermined;
	mightBeDecFirstNum;
	mightBeDec;
	mightBeBin;
	mightBeOct;
	mightBeHexFirstChar;
	mightBeHexSecChar;
	mightBeHexThirdChar;
	mightBeHex;	
} curr_State;

int isBinary(char* numB) {
	while (*numB != '\0') {
		if (*numB != '0' || *numB != '1') {
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
			case(mightBeHexFirstChar): {
				if (*numH == '0') {
					curr_State = mightBeHexSecChar;
					break;
				}
				else
					return 1;
			}
			case(mightBeHexSecChar): {
				if (*numH == 'x' || *numH == 'X') {
					curr_State = mightBeHexThirdChar;
					break;
				}
				else
					return 1;
			}
			case(mightBeHexThirdChar): {
				if (*numH >= '0' && *numH <= '9') {
					curr_State = mightBeHex;
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
	char* tempNum[strlen(num)];
	
	if (num[0] == '-' && strlen(num) <= 2) {         	//to have a negative sign means you must have at least a '-', a type (b,o,x,d) 
		return 1;										// and at least one digit.
	}
	else if (num[0] == '-') {
		tempType = num[1];
		strncpy(tempNum,&num[2],strlen(num)-2);
	}
	else if (strlen(num) == 1) {						//string must contain a type and at least one digit
		return 1;
	}
	else {
		tempType = num[0];
		strncpy(tempNum,&num[1],strlen(num)-1);
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
		curr_State = mightBeHexFirstChar;
		return isHex(tempNum);
	}
	else if (tempType == 'd')
	{
		curr_State = mightBeDecFirstNum;
		return isDecimal(tempNum);		
	}
	curr_State = undetermined;
	return 1;
}
/*main will take in five arguments to perform a calculation called by user. They will be able to input numbers 
 * in octal, hexadecimal, decimal and binary. They will also be able to output answers in one of those four types. 
 * negative numbers maybe used.  */
int main (int argc, char** argv) {
	int result;
	int stop = 0;
	
	if (argc < 5) {
		fprintf(stdout,"Not enough arguments!\n");
		stop = 1;
	}
	else if (argc > 5) {
		fprintf(stdout,"Too many arguments!\n");
		stop = 1;
	}
	
	if ((strlen(argv[1]) != 1) || (argv[1][0] != '+' || argv[1][0] != '-' || argv[1][0] != '*')) {
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
	
	if ((strlen(argv[4]) != 1) || (argv[4][0] != 'b' || argv[4][0] != 'o' || argv[4][0] != 'x'|| argv[4][0] != 'd')) {
		fprintf(stdout,"Invalid output conversion entered, please try again\n");
		stop = 1;
	}
	
	if (stop == 1) {
		return 0;
	}
	
	//number* num1 = numCreate();
	//number* num2 = numCreate();
	
	//result = solveEqn(argv[1][0],num1,num2);    //temporary 
	
	return 0;
}

