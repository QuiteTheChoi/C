/*
 * tokenizer.c
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

enum states {				
	undetermined,			//The begining of a token
	malformed,				
	int_float,				//final state (Integer) if no malformed char or '.' or 'e' is found. 
	oct_hex_float_zero,
	mightBeOct,				//Is the final state if no malformed character is found.
	mightBeHex, 			//Is the final state if no malformed character is found.
	mightBeFloat,			//Is the final state if no malformed character is found, state can change if an 'e' is found
	mightBeFloat_onlyints_neg_pos, 
	mightBeFloat_onlyints,   //Is the final state if no malformed character is found after a negative or positive is found
} curr_State;

char err;

struct TokenizerT_ {
	int i;   			//Index number used later for creating tokens
	int stringSize;		//Stri	ng size for getnexttoken function	
	char *myString;		//input string
};

typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 * 
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( char * ts ) {
	char copy[strlen(ts)]; 					//copy of string ts
	strcpy(copy,ts);  
	
	TokenizerT *ptr = (TokenizerT*) malloc (sizeof(struct TokenizerT_));   //Allocation of size for TokenizerT_
	ptr -> i = 0;		
	ptr -> stringSize = strlen(copy);	
	ptr -> myString = strdup(copy);
	
	return ptr;           /*returning the pointer*/
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {
	free (tk);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken( TokenizerT * tk ) {	
	int start = tk -> i;
	int arrBound = (tk -> stringSize) - 1;
	int end;
	char *ptr = tk -> myString;
	
	if (start > arrBound) { 			/*reached the end of char[] or out of bounds*/ 
	return 0;										
	}
	
	while (isspace(ptr[start]) && start < arrBound) {			/*clear out white spaces first or reached end of array before nul*/
		start++;
	}
	
	if (start == arrBound && isspace(ptr[start]))
		return 0;				/*reached last char and found only spaces*/
	
	end = start+1; /*start at first char of new token*/
	
	while (!isspace(ptr[end]) && end <= arrBound) {  /*find current full token (until next white space is found or end of char array is reached)*/
		end++;
	}
	
	int tokenSize = end - start;
	tk -> i = end + 1;
		
	char *token = (char*) malloc ((tokenSize+2)*sizeof(char));   
	
	int i;
	for (i = 0; i < tokenSize; i++) {
	token[i] = ptr[i+start];
	}
	token[i] = '\0';
	
	return token;
		
}

//beginning of all states and function calls for states

/*set the global char to the malform char of token*/
int malChar(char ptr) {
	err = ptr;
	return 0;
}

/* this will check whether or not the first character of token is a valid char of 
 * (1-9), '-' (this will be int or float), '0' (which will be float, hex, oct or zero state) or a malformed character. */
int isZeroOrNot(char x) {
	if (x == '0') {
		curr_State = oct_hex_float_zero;
	}
	else if ((x > '0' && x <= '9')||(x=='-')) {
		curr_State = int_float;
	}
	else if (x == '.') {
		curr_State = mightBeFloat;
	}
	else {
		curr_State = malformed;
		malChar(x);
	}
	
	return 0;
}

/* if isZeroOrNot determines that it could be a hex, float, oct or zero, 
 * this will determine if the next char is a 'x' or 'X' for hex, (0-7) for oct
 * or '.' for float and malform for all other characters. 'e' will not make it a 
 * float as the previous state was determined from * a '0', "0e" should not be valid. */
int isOctHexOrFloat(char x) {
	if (x >= '0' && x <= '7') {
		curr_State = mightBeOct;
	}
	else if (x == 'x' || x == 'X') { 
		curr_State = mightBeHex;
	}
	else if (x == '.') {
		curr_State = mightBeFloat;
	}
	else {
		curr_State = malformed;
		malChar(x);
	}
	
	return 0;
}

/*This will change the state from mightBeOct to malform
 * if anything besides (0-7) is found*/
int isOctal(char x) {				
	if (x >= '0' && x <= '7') {
	}
	else {
		curr_State = malformed;
		malChar(x);
	}
	return 0;
}

/*This will change the state from mightBeHex to malform
 * if anything besides (0-9), (a-f) or (A-F) is found is found*/
int isHex(char x) {
	if ((x >= '0' && x <= '9') || (x >= 'a' && x <= 'f') || (x >= 'A' && x <= 'F')) {
		}
	else {
		curr_State = malformed;
		malChar(x);
	}
	return 0;
}

/*This is for a float that consists of an 'e' and '+' or '-', the only thing left that 
 * should be found is integers, if not, malform state*/
int isDigit(char x) {
	if (x >= '0' && x <= '9') {
	}
	else {
		curr_State = malformed;
		malChar(x);
	}
	return 0;
}

/*This will determine if a token is an integer or float, the 
 * possible values for integer are (0-9), '.', 'e', 'E' will change the 
 * state appropriately */
int isDigitDotOrE (char x) {
	if (x == '.') {
		curr_State = mightBeFloat;
	}
	else if (x == 'e' || x == 'E') {
		curr_State = mightBeFloat_onlyints_neg_pos;
	}
	else if (x >= '0' && x <= '9') {
	}
	else {
		curr_State = malformed;
		malChar(x);
	}
	return 0;
}

/* This is called after a token is determined to be a float 
 * because a '.' has been found, only digits and 'e' can be found after the first '.' */
int isDigitOrE(char x) {
	if (x >= '0' && x <= '9') {
		curr_State = mightBeFloat;
	}
	else if (x == 'e' || x == 'E'){
		curr_State = mightBeFloat_onlyints_neg_pos;
	}
	else {
		curr_State = malformed;
		malChar(x);

	}
	return 0;
}

/* This is called after a possible float token has an 'e'
 * the only possible char after this e is digits or a negative or positive sign */
int isDigitOrSign(char x) {
	if ((x >= '0' && x <= '9') || (x == '-' || x == '+')) {
		curr_State	=  mightBeFloat_onlyints;
	}
	else {
		curr_State = malformed;
		malChar(x);
	}
	return 0;
}

int IdentifyToken (char *ptr) {
	while (*ptr != '\0') {
		switch(curr_State) {
			case (malformed): {     /*temporary*/
				return 0;
			}
			case(undetermined): {
				isZeroOrNot(*ptr);
				break;
			}
			case (oct_hex_float_zero): {
				isOctHexOrFloat(*ptr);
				break;
			}
			case (mightBeOct): {
				isOctal(*ptr);
				break;
			}
			case (mightBeHex): {
				isHex(*ptr);
				break;
			}
			case (mightBeFloat): {
				isDigitOrE(*ptr);
				break;
			}
			case (mightBeFloat_onlyints_neg_pos): {
				isDigitOrSign(*ptr);
				break;
			}
			case (mightBeFloat_onlyints): {
				isDigit(*ptr);
				break;
			}
			case (int_float): {
				isDigitDotOrE(*ptr);
				break;
			}
			default:
			break;
		}
	ptr++;
	}

	return 0;
}

char* TKGetState() {
	switch (curr_State) {
		case(malformed): {
			return "ERROR";
			break;
		}
		case (oct_hex_float_zero): {
			return "ZERO";
			break;
		}
		case (mightBeOct): {
			return "OCTAL";
			break;
		}
		case (mightBeHex): {
			return "HEXADECIMAL";
			break;
		}
		case (mightBeFloat): {
			return "FLOAT";
			break;
		}
		case (mightBeFloat_onlyints_neg_pos): {
			return "FLOAT";
			break;
		}
		case (mightBeFloat_onlyints): {
			return "FLOAT";
			break;
		}
		case (int_float): {
			return "INTEGER";
			break;
		}
		
		default:
		break;
	}
}
/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {
	if (argc == 1 || argv[1][0] == '\0') {									//in case no arguments are given
		return 0;
	}
		
	TokenizerT *tokenizer = TKCreate (argv[1]);        //creation of tokenizerT
	
	curr_State = undetermined;
	char *token =TKGetNextToken(tokenizer);
	char *status;
	
	while (token != 0) { 
		IdentifyToken(token);
		status = TKGetState();
		fprintf(stdout,"%s: %s ",status,token);
		if (curr_State == malformed) {
			fprintf(stdout,"Error caused by: [0x%x]\n",err);
		}
		else
			fprintf(stdout,"\n");
		curr_State = undetermined;
		token = TKGetNextToken(tokenizer);
	}
	
	free (token);
	TKDestroy(tokenizer);
				
	return 0;
}
