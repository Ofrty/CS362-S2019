CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to enter: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)


#########

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

radv: randomtestadventurer.c testingTools.h testingTools.c dominion.o rngs.o
	gcc -o randomtestadventurer randomtestadventurer.c -g $(CFLAGS)

r1: randomtestcard1.c testingTools.h testingTools.c dominion.o rngs.o
	gcc -o randomtestcard1 randomtestcard1.c -g $(CFLAGS)

r2: randomtestcard2.c testingTools.h testingTools.c dominion.o rngs.o
	gcc -o randomtestcard2 randomtestcard2.c -g $(CFLAGS)

#random testing for assignment 4
randomtestresults: randomtestadventurer.c testingTools.h testingTools.c dominion.o rngs.o 
	gcc -o randomtestadventurer randomtestadventurer.c -g  $(CFLAGS)
	gcc -o randomtestcard1 randomtestcard1.c -g  $(CFLAGS)
	gcc -o randomtestcard2 randomtestcard2.c -g  $(CFLAGS)
	echo "Result for running random tests:" > randomtestresults.out
	echo "randomtestadventurer.c:" >> randomtestresults.out
	./randomtestadventurer >> randomtestresults.out
	gcov randomtestadventurer.c >> randomtestresults.out
	echo "randomtestcard1.c:" >> randomtestresults.out
	./randomtestcard1 >> randomtestresults.out
	gcov randomtestcard1.c >> randomtestresults.out
	echo "randomtestcard2.c:" >> randomtestresults.out
	./randomtestcard2 >> randomtestresults.out
	gcov randomtestcard2.c >> randomtestresults.out

all: playdom player 

clean:
	rm -f *.o randomtestadventurer.exe randomtestadventurer randomtestcard1.exe randomtestcard1 randomtestcard2.exe randomtestcard2 playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
