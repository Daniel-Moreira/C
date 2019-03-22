/* @JUDGE_ID:	Daniel.Moreira	161  	C	"Traffic Lights"	*/
/* @BEGIN_OF_SOURCE_CODE */

#include <stdio.h>

void swap(int* array, int i, int j)
{
	array[i] ^= array[j];
	array[j] ^= array[i];
	array[i] ^= array[j];
}

int main()
{
	int i, len, signals[105], mult[105];
	
	while(scanf("%d %d", &signals[0], &signals[1]) != EOF && signals[0] != 0)
	{
		int answer = 1, min, max;
		
		/* Menor valor na primeira posicao */
		if(signals[0] > signals[1]) swap(signals, 0, 1);
		for(len = 2; scanf("%d", &signals[len]) && signals[len] != 0; len++) if(signals[0] > signals[len]) swap(signals, 0, len);
		
		/* Marca ciclo 0 para todos menos o menor */
		for(i = 1; i < len; i++) mult[i] = 0;
		for(mult[0] = 2; (min=signals[0]*mult[0]) < 18001; mult[0]+=2)
		{
			answer = 1, max = min+signals[0]-5;
			for(i = 1; i < len && answer; i++)
			{
				int minLocal = signals[i]*mult[i];
				int maxLocal = minLocal+signals[i]-5;
				/* Se ha interseccao */
				if((minLocal >= min && minLocal < max) || (maxLocal > min && maxLocal < max) || (minLocal <= min && maxLocal >= max))
				{
					/* Verifica/Atualiza o menor intervalo */
					if(minLocal > min) min = minLocal;
					if(maxLocal < max) max = maxLocal;
				}
				else if(maxLocal < min)	mult[i--]+=2;
				else answer = 0;
			}
			if(answer) break;
		}
		
		if(min >= 18001) printf("Signals fail to synchronise in 5 hours\n");
		else
		{
			int hour = min/3600;
			int minute = (min-(hour*3600))/60;
			int second = min-((hour*3600)+(minute*60));
			printf("%02d:%02d:%02d\n", hour, minute, second);
		}
	}
	
	return 0;
}

/* @END_OF_SOURCE_CODE */