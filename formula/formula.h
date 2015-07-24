#ifndef FORMULA_H_INCLUDED
#define FORMULA_H_INCLUDED

typedef enum state {
	undetermined,
	mightBeDecFirstNum,
	mightBeDec,	
} numState;

int checkInt(char* ptr);

#endif
