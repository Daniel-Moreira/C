 _____                _ __  __      
|  __ \              | |  \/  |     
| |__) |___  __ _  __| | \  / | ___ 
|  _  // _ \/ _` |/ _` | |\/| |/ _ \
| | \ \  __/ (_| | (_| | |  | |  __/
|_|  \_\___|\__,_|\__,_|_|  |_|\___|

/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/
@author Daniel Augusto de Melo Moreira - NUSP 8122477

Como Compilar e executar: 
			  
	Abrir a linha de comando e entrar com os seguintes comandos:
		  1. gcc -o ep2 ep2.c ArquivoReg.c Busca.c cronometro.c GeraIndice.c Ordena.c -lm
		  2. ep2 <arquivo de entrada com extensão>
		  	Ex.: busca_rotas config.txt

Comando adicional:

	1. create <nome do arquivo de saida> <número de blocos> - Cria um arquivo de teste. 

Considerações adicionais:

	As pastas 62500, 125000 e 250000 encontra-se os arquivos resultantes dos testes realizados, com 
arquivos de mesmo tamanho em blocos do nome da pasta. 
	No arquivo Busca.txt encontra-se os valores pesquisados.
	No arquivo Resultado - Seq encontra-se os resultados das pesquisas com o algoritmo de busca sequencial.
	No arquivo Resultado - Bin encontra-se os resultados das pesquisas com o algoritmo de busca binária.
	No arquivo Resultado - Ind encontra-se os resultados das pesquisas com o algoritmo de busca por índice.