/* @JUDGE_ID:	Daniel.Moreira	401  	C	"Palindromes"	*/
/* @BEGIN_OF_SOURCE_CODE */

#include <stdio.h>
#include <string.h>

char table[] = {'A', ' ', ' ', ' ', '3', ' ', ' ', 'H', 'I', 'L', ' ', 'J', 'M', ' ', 'O', ' ', ' ', ' ', '2', 'T', 'U', 'V', 'W', 'X', 'Y', '5'};
char tableN[] = {'1', 'S', 'E', ' ', 'Z', ' ', ' ', '8', ' '};

int isPalindrome(char* leitura)
{
	int i, j = strlen(leitura)-1;
	for(i = 0; i <= j; i++, j--) if(leitura[i] != leitura[j]) return 0;
	
	return 1;
}

int isMirrored(char* leitura)
{
	int i, j = strlen(leitura)-1;
	for(i = 0; i <= j; i++, j--)
	{
		if(leitura[i] >= '1' && leitura[i] <= '9')
		{
			if(tableN[leitura[i]%'1'] != leitura[j]) return 0;
		}
		else if(table[leitura[i]%'A'] != leitura[j]) return 0;
	}
	
	return 1;
}

int main()
{
	char leitura[50];
	
	while(scanf("%s", leitura) != EOF)
	{
		int palindrome = isPalindrome(leitura);
		int mirrored = isMirrored(leitura);
		
		if(palindrome && mirrored) printf("%s -- is a mirrored palindrome.\n\n", leitura);
		else if(palindrome) printf("%s -- is a regular palindrome.\n\n", leitura);
		else if(mirrored) printf("%s -- is a mirrored string.\n\n", leitura);
		else printf("%s -- is not a palindrome.\n\n", leitura);
	}
	
	return 0;
}

/* @END_OF_SOURCE_CODE */