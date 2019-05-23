#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define ASCII_MIN 32
#define ASCII_MAX 125
/*
#define ASCII_RNGA_MIN 32
#define ASCII_RNGA_MAX 41
#define ASCII_RNGB_MIN 97
#define ASCII_RNGB_MAX 125
*/
#define LEN_MIN 1 
#define LEN_MAX 5

//global var - char input domain
const char inDom[] = {'(',')','{','}','[',']',' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

/*charInInDom() is a helper function that assesses whether arg1 is in the input domain*/
/*
int charInInDom(char c)
{
	int found = 0;

	//check each value of input domain. if found, set return value to true and break loop
	for (int i = 0; ((i < (sizeof(inDom)/sizeof(char))) && (!found)); i++)
	{
		if(c == inDom[i])
		{
			found = 1;
		}
	}

	return found;
}
*/

char inputChar()
{
	//gen char in inDom
	char c = (char) inDom[(rand() % ((sizeof(inDom))/(sizeof(char))))];

	//int c = -1; //init to something outside of the domain 
	//char c = (char) ((rand() % (ASCII_MAX - ASCII_MIN + 1)) + ASCII_MIN);
	//int c = 64; //init to something outside of the domain 
	//char c = '@'; //init to something outside of the domain 

	/*	
	//(re)gen a char until it's verified as part of the input domain
	while (!charInInDom(c))
	{
		//generate a random value in valid ASCII ranges. handle char casting once, here.
		c = (char) ((rand() % (ASCII_MAX - ASCII_MIN + 1)) + ASCII_MIN);
	}
	*/

	/*
	while ( !((c >= ASCII_RNGA_MIN) && (c <= ASCII_RNGA_MAX)) && !((c >= ASCII_RNGB_MIN) && (c <= ASCII_RNGB_MAX))) //is val within either range
	{
		//random int isn't within ranges, regen
		c = (rand() % (ASCII_RNGB_MAX - ASCII_RNGA_MIN + 1)) + ASCII_RNGA_MIN;
	}
	*/

	/*debug num gen
	for(int i = 0; i < 50; i++)
	{
		//int c = (rand() % (ASCII_MAX - ASCII_MIN + 1)) + ASCII_MIN; //abandoned single-range implementation

		c = 0;
		while ( !((c >= ASCII_RNGA_MIN) && (c <= ASCII_RNGA_MAX)) && !((c >= ASCII_RNGB_MIN) && (c <= ASCII_RNGB_MAX))) //is val within either range
		{
			printf("old c = %d, scrap and regen\n", c);

			//random int isn't within ranges, regen
			c = (rand() % (ASCII_RNGB_MAX - ASCII_RNGA_MIN + 1)) + ASCII_RNGA_MIN;

			printf("new c = %d\n",c);
		}
			
		if((i%10) == 0)
		{
			printf("\n");
		}

		printf("%d\t", c);
	}

	printf("\n");
	*/
 
	//return randomly-generated, validated char
	return c;
}

char *inputString()
{
	//generate a random number between LEN min and max
	int l = (rand() % (LEN_MAX - LEN_MIN + 1)) + LEN_MIN;

	//printf("**inputString() - randomly-gen'd length is %d\n", l);//debug

	//create a string of length l + 1 (for null term \0) and fill with randomly-gen'd chars
	char* s = malloc((sizeof(char) * (l + 1)));
	for (int i = 0; i < l; i++)
	{
		s[i] = inputChar();
		//printf("**inputString() - s[%d] is %c\n", i, s[i]);//debug
	}
	//printf("\n\n"); //debug

	//terminate string
	s[l] = '\0';

	return s;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;

printf("***Running test. Will report every 250k tests for brevity.***\n\n");

  while (1)
  {
	tcCount++;
	c = inputChar();
	s = inputString();
	
	//report test info if divisible by 250k
	if ((tcCount % 250000) == 0)
	{
		printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);
	}

	if (c == '[' && state == 0) state = 1;
	if (c == '(' && state == 1) state = 2;
	if (c == '{' && state == 2) state = 3;
	if (c == ' '&& state == 3) state = 4;
	if (c == 'a' && state == 4) state = 5;
	if (c == 'x' && state == 5) state = 6;
	if (c == '}' && state == 6) state = 7;
	if (c == ')' && state == 7) state = 8;
	if (c == ']' && state == 8) state = 9;
	if (s[0] == 'r' && s[1] == 'e'
	   && s[2] == 's' && s[3] == 'e'
	   && s[4] == 't' && s[5] == '\0'
	   && state == 9)
	{
		printf("\n\nFINAL Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);
		printf("error ");
		
		//dealloc str	
		free(s);
		s = NULL;

		exit(200);
	}
  }
}


int main(int argc, char *argv[])
{
	srand(time(NULL));
	testme();
	return 0;

	/*func testing/debugging
	srand(time(NULL));

	printf("%c\n", inputChar()); //debug inputChar


	//debug inputString
	char* s = inputString();
	char c;
	c = s[0];
	int i = 0;
	while(c != '\0')
	{
		c = s[i];
		printf("%c - (%d)\n", c, (int) c);
		i++;
	}

	printf("\n\n");
	free(s);
	s = NULL;

	return 0;
	*/
}
