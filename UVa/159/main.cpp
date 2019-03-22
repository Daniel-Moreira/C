/* @JUDGE_ID:	Daniel.Moreira	159	C	"Word Crosses"	*/
/* @BEGIN_OF_SOURCE_CODE */

#include <stdio.h>
#define TAMANHO 20

int commonWord(char word[], char word2[], int *ind)
{
	int i = 0;
	while(i < TAMANHO)
	{
		if(word[i] == word2[*ind])return i;
		if(*ind < TAMANHO)*ind = *ind + 1;
		if(*ind == TAMANHO || word2[*ind] < 65 || word2[*ind] > 90)
		{
			*ind = 0;
			i++;
		}
		if(word[i] < 65 || word[i] > 90)return -1;
	}
	return -1;
}

int quantidadeLetras(char word[])
{
	int i = 0;
	while(word[i] >= 65 && word[i] <= 90)
	{
		i++;
	}
	return i-1;
}

int main()
{
	char word[4][TAMANHO+1];
	int n = 0;
	scanf("%s", word[0]);
    while(word[0][0] != '#')
    {
		if(n != 0)
		{
			printf("\n");
		}
		scanf("%s", word[1]);
		scanf("%s", word[2]);
		scanf("%s", word[3]);
		int ind = 0;
		int i = commonWord(word[0], word[1], &ind);
		
		if(i == -1)
		{
			printf("Unable to make two crosses\n");
		}
		else
		{
			int ind2 = 0;
			int i2 = commonWord(word[2], word[3], &ind2);
			if(i2 == -1)
			{
				printf("Unable to make two crosses\n");
			}
			else
			{
				int k;
				int k2;
				int espace = quantidadeLetras(word[0]) - i  + 4 + i2;
				for(k = 0; k < ind-ind2; k++)
				{							
					printf("%*c\n", i+1, word[1][k]);					
				}
				for(k2 = 0; k2 < ind2-ind; k2++)
				{							
					printf("%*c\n", espace+i+1, word[3][k2]);					
				}			
				while(k2 < ind2)
				{
					printf("%*c", i+1, word[1][k]);
					printf("%*c\n", espace, word[3][k2]);
					k++;
					k2++;
				}
				printf("%s   %s\n", word[0], word[2]);
				k++;
				k2++;
				int ac = 0;
				int ac2 = 0;			
				while(ac == 0 || ac2 == 0)
				{
					if(word[1][k] >= 65 && word[1][k] <= 90)
					{
						printf("%*c", i+1, word[1][k]);
						k++;
					}
					else
					{
						ac = 1;
					}
					if(word[3][k2] >= 65 && word[3][k2] <= 90)
					{
						if(ac == 1)
						{
							printf("%*c\n", espace+i+1, word[3][k2]);
						}
						else
						{
							printf("%*c\n", espace, word[3][k2]);
						}
						k2++;
					}
					else
					{
						ac2 = 1;
						if (ac == 0)printf("\n");
					}
				}
			} 
		}
		n++;
		scanf("%s", word[0]);
    }
	return 0;
}

/* @END_OF_SOURCE_CODE */
