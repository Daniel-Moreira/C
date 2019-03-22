/* @JUDGE_ID:	Daniel.Moreira	156	C	"Ananagrams"	*/
/* @BEGIN_OF_SOURCE_CODE */

#include <stdio.h>

typedef struct
{
	char word[81];
	int quantidade[27];
	int anagram; 
}palavra;

void inicializar(palavra *p)
{
	scanf("%s", p -> word);
	int i;
	for (i = 0; i < 27; i++)
	{
		p -> quantidade[i] = 0;
	}
	p -> anagram = 0;
}

int main()
{
	palavra p[1001];
	int n = 0;
	int i;
	int j;
	inicializar(&p[n]);
    while(p[n].word[0] != '#')
    {
		for (i = 0; i < 81; i++)
		{
			int dWord = (int)p[n].word[i];
			//Lower Case
			if (dWord >= 65 && dWord <= 90)dWord += 32;
			//Fora do alfabeto
			if (dWord > 122 || dWord < 97)break;
			p[n].quantidade[dWord % 97]++;
		}
		n++;	
		inicializar(&p[n]);
    }
	for(i = n-1; i >= 0; i--)
    {
		for(j = i-1; j >= 0; j--)
		{
			int k;
			for (k = 0; k < 27; k++)
			{
				if (p[i].quantidade[k] != p[j].quantidade[k])break;
			}
			if (k == 27)
			{
				p[i].anagram = 1;
				p[j].anagram = 1;
				break;
			}
		}
	}
	int ordW[1001];
	j = 0;
	for(i = n-1; i >= 0; i--)
	{
		if (p[i].anagram != 1)
		{
			ordW[j] = i;
			j++;
		}
	}
	for(i = 0; i < j; i++)
	{
		int k;
		for(k = i+1; k < j; k++)
		{
			int ind;
			for(ind = 0; ind < 81; ind++)
			{
				if((int)p[ordW[i]].word[ind] > (int)p[ordW[k]].word[ind])
				{
					int aux = ordW[k];
					ordW[k] = ordW[i];
					ordW[i] = aux;
					break;
				}
				if((int)p[ordW[i]].word[ind] < (int)p[ordW[k]].word[ind])break;
			}
		}
	}
	for(i = 0; i < j; i++)
	{
		printf("%s\n", p[ordW[i]].word);
	}
	//scanf("%d", &i);
	return 0;
}

/* @END_OF_SOURCE_CODE */
