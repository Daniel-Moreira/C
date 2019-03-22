:op1
@echo on
cls
gcc -o busca_rotas busca_rotas.c geodist.c fila.c grafo_op.c cronometro.c heapB.c -lm
@echo off
pause
cls
busca_rotas entrada4_escala.txt saida.txt
pause
cls
Echo [1] Deseja executar novamente?
Echo [2] Deseja sair do programa?
Set /p choice=Digite o numero correspodente a sua opçao:
if '%choice%'=='2' goto op2
if '%choice%'=='1' goto op1
:op2