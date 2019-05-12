CFLAGS= -Wall -fpic -coverage -lm -std=c99

default: all 

testme: testme.c
	gcc -o testme -g testme.c $(CFLAGS)

testmecov: testme
	-./testme &> testmeresults.out
	echo "\n\n***Result for testme:" >> testmeresults.out
	echo "\n\n***testme.c:" >> testmeresults.out
	gcov testme.c >> testmeresults.out
	cat testme.c.gcov >> testmeresults.out

all: testme testmecov

clean:
	rm -f *.o testme testme.exe *.gcov *.gcda *.gcno *.so *.out
