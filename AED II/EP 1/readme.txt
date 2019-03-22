 _____                _ __  __      
|  __ \              | |  \/  |     
| |__) |___  __ _  __| | \  / | ___ 
|  _  // _ \/ _` |/ _` | |\/| |/ _ \
| | \ \  __/ (_| | (_| | |  | |  __/
|_|  \_\___|\__,_|\__,_|_|  |_|\___|

/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/
@author Daniel Augusto de Melo Moreira - NUSP 8122477

Como Compilar e executar: 

	No Windows: Duplo clique no arquivo "Compilar - Executar.bat".
		obs.: Deve-se editar a linha 8 do arquivo caso queira executar o programa com parametros diferentes de entrada1_dist.txt e saida.txt
			  
	No Linux: Abrir a linha de comando e entrar com os seguintes comandos:
		  1. gcc -o busca_rotas busca_rotas.c geodist.c fila.c grafo_op.c cronometro.c heapB.c -lm
		  2. busca_rotas <arquivo de entrada com extensão> <arquivo de saída com extensão>
		  	Ex.: busca_rotas entrada.txt saida.txt

Algoritmos implementados:
	1. Busca em profundidade
	2. Algoritmo de Dijkstra (com Heap Binário)
	3. Algortimo de Bellman-Ford

Comparação entre Dijkstra e Bellman-Ford:

	  Após a realização de alguns testes em ambos os algoritmos, foi possivel perceber que o algoritmo de Dijkstra é mais eficiente que o algoritmo de Bellman-Ford quando a quantidade de vertices no grafo é muito grande, mesmo quando o algoritmo de Dijkstra não é implementado utilizando uma fila de prioridade eficiente(Ex.: Fila baseada em heap binario).
	Porém o algoritmo de Bellman-Ford possui a vantagem de conseguir calcular a menor distancia em um grafo que possui arestas de peso negativo.

