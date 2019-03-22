/* @JUDGE_ID:	Daniel.Moreira	403  	C	"Postscript"	*/
/* @BEGIN_OF_SOURCE_CODE */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char sheet[60][61];
char C5[][5][7] = {
	{".***..", "*...*.", "*****.", "*...*.", "*...*."},
	{"****..", "*...*.", "****..", "*...*.", "****.."},
	{".****.", "*...*.", "*.....", "*.....", ".****."},
	{"****..", "*...*.", "*...*.", "*...*.", "****.."},
	{"*****.", "*.....", "***...", "*.....", "*****."},
	{"*****.", "*.....", "***...", "*.....", "*....."},
	{".****.", "*.....", "*..**.", "*...*.", ".***.."},
	{"*...*.", "*...*.", "*****.", "*...*.", "*...*."},
	{"*****.", "..*...", "..*...", "..*...", "*****."},
	{"..***.", "...*..", "...*..", "*..*..", ".**..."},
	{"*...*.", "*..*..", "***...", "*..*..", "*...*."},
	{"*.....", "*.....", "*.....", "*.....", "*****."},
	{"*...*.", "**.**.", "*.*.*.", "*...*.", "*...*."},
	{"*...*.", "**..*.", "*.*.*.", "*..**.", "*...*."},
	{".***..", "*...*.", "*...*.", "*...*.", ".***.."},
	{"****..", "*...*.", "****..", "*.....", "*....."},
	{".***..", "*...*.", "*...*.", "*..**.", ".****."},
	{"****..", "*...*.", "****..", "*..*..", "*...*."},
	{".****.", "*.....", ".***..", "....*.", "****.."},
	{"*****.", "*.*.*.", "..*...", "..*...", ".***.."},
	{"*...*.", "*...*.", "*...*.", "*...*.", ".***.."},
	{"*...*.", "*...*.", ".*.*..", ".*.*..", "..*..."},
	{"*...*.", "*...*.", "*.*.*.", "**.**.", "*...*."},
	{"*...*.", ".*.*..", "..*...", ".*.*..", "*...*."},
	{"*...*.", ".*.*..", "..*...", "..*...", "..*..."},
	{"*****.", "...*..", "..*...", ".*....", "*****."}};

void init()
{
	int i, j;
	for(i = 0; i < 60; i++) for(j = 0; j < 60; j++) sheet[i][j] = '.';
	for(i = 0; i < 60; i++) sheet[i][60] = '\0';
}

void copyC5(int row, int col, char c)
{
	int i, j;
	if(c == ' ') 
	{
		for(i = row; i < row+5 && i < 60; i++) if(i >= 0) for(j = col; j < col+6 && j < 60; j++) if(j >= 0) sheet[i][j] = '.';
	}
	else for(i = row; i < row+5 && i < 60; i++) if(i >= 0) for(j = col; j < col+6 && j < 60; j++) if(j >= 0) sheet[i][j] = C5[c%'A'][i-row][j-col];
}

void copyC1(int row, int col, char c)
{
	if(c == ' ') return ;
	if(row >= 0 && row < 60 && col >= 0 && col < 60) sheet[row][col] = c;
}

void print()
{
	int i, j;
	for(i = 0; i < 60; i++) printf("%s\n", sheet[i]);
	printf("\n");
	for(i = 0; i < 60; i++) printf("-");
	printf("\n\n");
}

int main()
{
	char command[5], font[5], string[65];
	int i, j, row, col, len;
	
	init();
	while(scanf("%s", command) != EOF)
	{
		if(strcmp(command, ".EOP") == 0)
		{
			print();
			init();
			continue;
		}
		
		scanf("%s %d ", font, &row);	
		
		if(strcmp(command, ".P") == 0) scanf("%d ", &col), i = 0;
		
		scanf("|%[^|]|", string), len = strlen(string);
		
		if(strcmp(command, ".L") == 0) i = 0, col = 1;
		else if(strcmp(command, ".R") == 0) i = len, col = 61;
		else if(strcmp(command, ".C") == 0)
		{
			i = len>>1;
			col = 31;
			if(len%2 != 0 && strcmp(font, "C5") == 0) col = 28;
		}
		
		if(strcmp(font, "C5") == 0)
		{
			int colAux = col-6;
			for(j = i-1; j >= 0; j--) copyC5(row-1, colAux-1, string[j]), colAux-=6;  
			for(j = i; j < len; j++) copyC5(row-1, col-1, string[j]), col+=6;  
		}
		else
		{
			int colAux = col-1;
			for(j = i-1; j >= 0; j--) copyC1(row-1, colAux-1, string[j]), colAux--;  
			for(j = i; j < len; j++) copyC1(row-1, col-1, string[j]), col++; 
		}
	}
	
	return 0;
}

/* @END_OF_SOURCE_CODE */