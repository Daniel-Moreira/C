#include "listas.h"
#include <stdio.h>

// Use main() para testar seu EP, mas lembre-se de que este codigo nao 
// faz parte da entrega do trabalho  

int main() {
           // cria lista vazia
           NO *inicio = criar();
           
           inicio -> chave = 1;
           inicio -> prox = NULL;
           int i;
           NO *aux = inicio;
           for (i = 2; i < 6; i++)
           {
           aux -> prox = criar();
           aux = aux -> prox;
           aux -> chave = i;
           aux -> prox = NULL;
		   }

           int k = 5;
           removerK(&inicio, k); 
           
           aux = inicio;
           while(aux)
           {
           	printf("%d ", aux->chave);
           	aux = aux -> prox;
		   }
           getch();
}
