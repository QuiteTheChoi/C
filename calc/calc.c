#include <stdio.h>
#include <string.h>

/*struct for creating a number*/
struct number_ {
	char type;
	char *numString;
	int negative;
};

enum states 

typedef struct number_ number;

/* Will take in both numbers to validate that the numbers are entered correctly.
 * Will run the numbers to other functions based on the type specified by user. 
 * Returns a 1 if number entered is found to be an invalid format. */
int validateToken(char* num) {
	char tempType;
	char* tempNum[strlen(num)];
	
	if (num[0] == '-' && strlen(num) <= 2) {         	//to have a negative sign means you must have at least a '-', a type (b,o,x,d) 
		return 1;										// and at least one digit.
	}
	else if (num[0] == '-')
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
		return isBinary(tempNum);
	}
	else if (tempType == 'o')
	{
		return isOctal(tempNum);
	}
	else if (tempType == 'x')
	{
		return isHex(tempNum);
	}
	else if (tempType == 'd')
	{
		return isDecimal(tempNum);
	}

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
	
	if ((strlen(argv[1]) != 1) && (argv[1][0] != '+' || argv[1][0] != '-' || argv[1][0] != '*')) {
		fprintf(stdout,"Invalid operation entered, please try again\n");
		stop = 1;
	}
	
	if (validateToken(argv[2]) == 1 && validateToken(argv[3]) == 1) {
		fprintf(stdout,"First and second number arguments are invald\n");
		stop = 1;
	}
	else if (validateToken(argv[2]) == 1) {
		fprintf(stdout,"First number argument is invald\n");
		stop = 1;
	}
	else if (validateToken(argv[3]) == 1) {
		fprintf(stdout,"Second number argument is invald\n");
		stop = 1;
	}
	
	if (stop == 1) {
		return 0;
	}
	
	number* num1 = numCreate();
	number* num2 = numCreate();
	
	result = solveEqn(argv[1][0],num1,num2);    //temporary 
	
	return 0;
}

