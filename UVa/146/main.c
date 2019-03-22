/* @JUDGE_ID:	Daniel.Moreira	146		C	"ID Codes"	*/
/* @BEGIN_OF_SOURCE_CODE */

#include <stdio.h>
#include <string.h>

int compare(const void* a, const void* b)
{
  return ( *(char*)a - *(char*)b );
}

void troca(char* string, int i, int j, int tamanho)
{
	char aux = string[i];
	string[i] = string[j];
	string[j] = aux;
	
	qsort(&string[j+1], tamanho-(j+1), sizeof(char), compare);
}

int main()
{
	char leitura[55];
	
	while(scanf("%s", leitura) != EOF && strcmp(leitura, "#") != 0)
	{
		int tamanho = strlen(leitura), i, j;
		int mudou = 0;
		for(i = tamanho-1; i > 0 && mudou == 0; i--)
		{
			for(j = i-1; j >= 0 && mudou == 0; j--)
			{
				if(leitura[j] < leitura[i])
				{
					troca(leitura, i, j, tamanho);
					mudou = 1;
				}
			}
		}
		
		if(mudou == 1) printf("%s\n", leitura);
		else printf("No Successor\n");
	}
	
	return 0;
}

/* @END_OF_SOURCE_CODE */