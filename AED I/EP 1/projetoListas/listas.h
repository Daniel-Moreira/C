#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

// elemento da lista
typedef struct estr {
        int chave;
        estr *prox;
} NO;

// funcoes a implementar em trabalho.cpp
char *aluno1();
char *nrousp1();
char *aluno2();
char *nrousp2();
char *turma();

void removerK(NO **inicio, int k);

// NAO ALTERE ESTAS FUNCOES
NO *criar();
void destruir(NO *p);
