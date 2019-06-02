CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

#To run playdom you need to enter: ./playdom <any integer number> like ./playdom 10*/
playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g dominion.o rngs.o interface.o $(CFLAGS)

#########
#testing for assignment 5
nradv: nonrandomtestadventurer.c testingTools.h testingTools.c dominion.o rngs.o
	gcc -o nonrandomtestadventurer nonrandomtestadventurer.c -g $(CFLAGS)

nrsmithy: nonrandomtestsmithy.c testingTools.h testingTools.c dominion.o rngs.o
	gcc -o nonrandomtestsmithy nonrandomtestsmithy.c -g $(CFLAGS)

radv: randomtestadventurer.c testingTools.h testingTools.c dominion.o rngs.o
	gcc -o randomtestadventurer randomtestadventurer.c -g $(CFLAGS)

rsmithy: randomtestsmithy.c testingTools.h testingTools.c dominion.o rngs.o
	gcc -o randomtestsmithy randomtestsmithy.c -g $(CFLAGS)

#random testing for assignment 3
nonrandomtestresults: nonrandomtestadventurer.c nonrandomtestsmithy.c testingTools.h testingTools.c dominion.o rngs.o
	gcc -o nonrandomtestadventurer nonrandomtestadventurer.c -g  $(CFLAGS)
	gcc -o nonrandomtestsmithy nonrandomtestsmithy.c -g  $(CFLAGS)
	echo "Result for running non-random unit tests:" > nonrandomtestresults.out
	echo "nonrandomtestadventurer.c:" >> nonrandomtestresults.out
	./nonrandomtestadventurer >> nonrandomtestresults.out
	gcov nonrandomtestadventurer.c >> nonrandomtestresults.out
	echo "nonrandomtestsmithy.c:" >> nonrandomtestresults.out
	./nonrandomtestsmithy >> nonrandomtestresults.out
	gcov nonrandomtestsmithy.c >> nonrandomtestresults.out

#random testing for assignment 4
randomtestresults: randomtestadventurer.c randomtestsmithy.c testingTools.h testingTools.c dominion.o rngs.o 
	gcc -o randomtestadventurer randomtestadventurer.c -g  $(CFLAGS)
	gcc -o randomtestsmithy randomtestsmithy.c -g  $(CFLAGS)
	echo "Result for running random tests:" > randomtestresults.out
	echo "randomtestadventurer.c:" >> randomtestresults.out
	./randomtestadventurer >> randomtestresults.out
	gcov randomtestadventurer.c >> randomtestresults.out
	echo "randomtestsmithy.c:" >> randomtestresults.out
	./randomtestsmithy >> randomtestresults.out
	gcov randomtestsmithy.c >> randomtestresults.out

assignment5: nonrandomtestresults randomtestresults

all: playdom player 

clean:
	rm -f *.o nonranomtestadventurer.exe nonrandomtestadventurer nonrandomtestsmithy.exe nonrandomtestsmithy randomtestadventurer.exe randomtestadventurer randomtestsmithy.exe randomtestsmithy playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
