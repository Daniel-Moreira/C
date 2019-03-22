/* @JUDGE_ID:	Daniel.Moreira	100	C	"The 3n + 1 Problem"	*/
/* @BEGIN_OF_SOURCE_CODE */

#include <stdio.h>

int main ()
{
    int n1;
    int n2;
    while(!feof(stdin))
    {
		scanf("%d %d", &n1, &n2);
		printf("%d %d ", n1 , n2);
		int i;
		int count = 0;
		if (n1 > n2)
		{
			int aux = n1;
			n1 = n2;
			n2 = aux;
		}
		for(i = n1; i <= n2; i++)
		{
			int j = i;
            int entrada = 1;
            while (j != 1)
            {
                if(j%2 == 0)
                {
					j = j/2;
                }
                else
                {
                    j = (j*3)+1;
                }
                entrada++;
            }     
			if (entrada > count) count = entrada;   
		}
		printf("%d\n", count);
    }
	return 0;
}

/* @END_OF_SOURCE_CODE */
