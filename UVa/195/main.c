/* @JUDGE_ID:	Daniel.Moreira	195  	C	"Angram"	*/
/* @BEGIN_OF_SOURCE_CODE */
/* http://blog.bjrn.se/2008/04/lexicographic-permutations-using.html */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b)
{
	int result = tolower(*(char*)a) - tolower(*(char*)b);
	if(result == 0) result = (*(char*)a) - (*(char*)b);
	return result;
}

void swap(char* leitura, int i, int j)
{
	leitura[i] ^= leitura[j];
	leitura[j] ^= leitura[i];
	leitura[i] ^= leitura[j];
}

void reverse(char* leitura, int i, int len)
{
	for(; i < len; i++, len--) swap(leitura, i, len);
}

int nextPermutation(char* leitura, int len)
{
	int i, j, iHigh = -1, jHigh = -1;
	/* Separa a string em duas partes */
	for(i = 0; i < len; i++) if(compare(&leitura[i], &leitura[i+1]) < 0) iHigh = i;

	/* Last permutation */
	if(iHigh == -1) return 0;
	for(j = iHigh+1; j <= len; j++) if(compare(&leitura[iHigh], &leitura[j]) < 0) jHigh = j;
	
	swap(leitura, iHigh, jHigh);
	reverse(leitura, iHigh+1, len);
	
	return 1;
}

int main()
{
	char leitura[100];
	int i, n, len;
	
	scanf("%d", &n);
	while(n-- && scanf("%s", leitura) != EOF)
	{
		len = strlen(leitura);
		qsort(leitura, len, sizeof(char), compare);	
		
		do
		{
			printf("%s\n", leitura);
		} while(nextPermutation(leitura, len-1));
	}
	
	return 0;
}

/* @END_OF_SOURCE_CODE */