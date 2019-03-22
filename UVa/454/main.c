/* @JUDGE_ID:	Daniel.Moreira	454  	C	"Angrams"	*/
/* @BEGIN_OF_SOURCE_CODE */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b)
{
	return strcmp((char*)a, (char*)b);
}

int main()
{
	char leitura[105][1000];
	int i, j, k, n, len, letras[105][200], max;
	
	scanf("%d\n", &n);
	while(n--)
	{
		/* leitura */
		for(i = 0; gets(leitura[i]) != NULL && strcmp(leitura[i], "") != 0 && strcmp(leitura[i], " ") != 0; i++) for(j = 0; j < 200; j++) letras[i][j] = 0;
		
		max = i;
		qsort(leitura, max, sizeof(char)*1000, compare);
		
		for(i = 0; i < max; i++)
		{
			len = strlen(leitura[i]);
			/* Conta a qtd de letras */
			for(j = 0; j < len; j++) if(leitura[i][j] != ' ') letras[i][leitura[i][j]]++;	
		}
		
		for(i = 0; i < max; i++)
		{
			for(j = i+1; j < max; j++)
			{
				/* Se eh um anagrama imprime */
				for(k = 0; k < 200 && letras[i][k] == letras[j][k]; k++);
				if(k == 200) printf("%s = %s\n", leitura[i], leitura[j]);
			}
		}
		
		if(n > 0) printf("\n");
	}
	
	return 0;
}

/* @END_OF_SOURCE_CODE */