/* @JUDGE_ID:	Daniel.Moreira	299		C	"Train Swapping"	*/
/* @BEGIN_OF_SOURCE_CODE */

#include <stdio.h>
#include <string.h>

int bubbleSort(int* train, int length)
{
	int i, j, resp = 0;
	for(i = 0; i < length; i++)
	{
		for(j = i+1; j < length; j++)
		{
			if(train[i] > train[j])
			{
				int aux = train[i];
				train[i] = train[j];
				train[j] = aux;
				resp++;
			}
		}
	}

	return resp;
}

int main()
{
	int n;
	scanf("%d", &n);
	
	while(n > 0)
	{
		int l;
		scanf("%d", &l);
		
		int train[l], i;
		for(i = 0; i < l; i++) scanf("%d", &train[i]);
		
		int answ = bubbleSort(train, l);
		
		printf("Optimal train swapping takes %d swaps.\n", answ);
		
		n--;
	}
	
	return 0;
}

/* @END_OF_SOURCE_CODE */