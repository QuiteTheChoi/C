all: nCr.o formula.o
	gcc -m32 nCr.o formula.o -o formula
formula.o: nCr.o nCr.h formula.c formula.h
	gcc -m32 -c formula.c -o formula.o
nCr.o: nCr.s
	gcc -m32 -c nCr.s -o nCr.o
clean:
	rm -rf *.o formula
