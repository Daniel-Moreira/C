/* @JUDGE_ID:	Daniel.Moreira	462 	C	"Bridge Hand Evaluator"	*/
/* @BEGIN_OF_SOURCE_CODE */

#include <stdio.h>
#include <string.h>

#define S 0
#define H 1
#define D 2
#define C 3

int getIndex(char value)
{
	if(value == 'A' || value == 'S') return 0;
	else if(value == 'K' || value == 'H') return 1;
	else if(value == 'Q' || value == 'D') return 2;
	else if(value == 'J' || value == 'C') return 3;
	else return 4;
}

void imprime(int value)
{
	if(value == 0) printf("BID S\n");
	else if(value == 1) printf("BID H\n");
	else if(value == 2) printf("BID D\n");
	else printf("BID C\n");
}

int main()
{
	char leitura[3];
	int i, j, n, running = 1;
	
	while(running)
	{
		int points = 0, suits[4], suitStop[4], valuableCards[5][5];
		
		/* S = 0, H = 1, D = 2, C = 3 */
		for(i = 0; i < 4; i++) suits[i] = 0;
		for(i = 0; i < 4; i++) suitStop[i] = 0;
		for(i = 0; i < 4; i++) for(j = 0; j < 4; j++) valuableCards[i][j] = 0;
	
		for(n = 0; n < 13; n++)
		{
			if(scanf("%s", &leitura) == EOF) return 0;
			/* Rule 1 */
			if(leitura[0] == 'A') points += 4;
			else if(leitura[0] == 'K') points += 3;
			else if(leitura[0] == 'Q') points += 2;
			else if(leitura[0] == 'J') points++;
				
			/* Counting cards */
			if(leitura[1] == 'S') suits[S]++;
			else if(leitura[1] == 'H') suits[H]++;
			else if(leitura[1] == 'D') suits[D]++;
			else if(leitura[1] == 'C') suits[C]++;
			
			valuableCards[getIndex(leitura[0])][getIndex(leitura[1])] = 1;
		}
		
		/* Rule j+1 (2 to 4)*/
		for(j = 1; j < 4; j++)
		{
			for(i = 0; i < 4; i++)
			{
				if(valuableCards[j][i] == 1)
				{
					if(suits[i] <= j) points--;
					else if(j != 3) suitStop[i] = 1;
				}
			}
		}
		
		/* Maior grupo de cartas */
		int suitMax = suits[S], biggerSuit = S;
		for(i = 1; i < 4; i++)
		{
			if(suitMax < suits[i])
			{
				suitMax = suits[i];
				biggerSuit = i;
			}
		}
		
		if(points >= 16)
		{
			int teste = 1;
			for(i = 0; i < 4 && teste; i++) if(suitStop[i] == 0 && valuableCards[0][i] == 0) teste = 0;
			
			if(teste) printf("BID NO-TRUMP\n");
			else imprime(biggerSuit);
		}
		else
		{
			for(i = 0; i < 4; i++)
			{
				/* Rule 5, 6, 7 */
				if(suits[i] == 2) points++;
				else if(suits[i] == 1) points += 2;
				else if(suits[i] == 0) points += 2;
			}
			
			if(points >= 14) imprime(biggerSuit);
			else printf("PASS\n");
		}
	}
	
	return 0;
}

/* @END_OF_SOURCE_CODE */