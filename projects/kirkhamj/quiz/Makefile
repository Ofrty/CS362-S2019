CFLAGS= -Wall -fpic -coverage -lm -std=c99

default: testme

testme: testme.c
	gcc -o testme testme.c -g $(CFLAGS)
	./testme
	echo "Result for testme:" > testmeresults.out
	echo "testme.c:" >> testmeresults.out
	gcov testme.c >> testmeresults.out
	cat testme.c.gcov >> testmeresults.out

clean:
	rm -f *.o testme testme.exe *.gcov *.gcda *.gcno *.so *.out
