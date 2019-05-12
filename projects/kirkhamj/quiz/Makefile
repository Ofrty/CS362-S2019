CFLAGS= -Wall -fpic -coverage -lm -std=c99

default: testme

testme: testme.c
	gcc -o testme testme.c -g $(CFLAGS)

#unittestresults: unittest1.c unittest2.c unittest3.c unittest4.c testingTools.h testingTools.c dominion.o rngs.o
#	gcc -o unittest1 unittest1.c -g  $(CFLAGS)
#	echo "Result for running unit tests:" > unittestresults.out
#	echo "unittest1.c:" >> unittestresults.out
#	./unittest1 >> unittestresults.out
#	gcov unittest1.c >> unittestresults.out

clean:
	rm -f *.o testme testme.exe *.gcov *.gcda *.gcno *.so *.out
