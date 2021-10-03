# Makefile

# variavel
objects = main.o fila.o

# acesso a variavel objects, com conteudo sendo os arquivos main.o e fila.o
# esses arquivos objeto sao dependencias do executavel main
# main.o e fila.o devem ser link editados para formar o executavel main
# gcc main.o fila.o -o main -> explicito

main: $(objects)
	gcc $(objects) -o main 

# o Makefile reconhece que eh preciso compilar fila.c, mesmo sem colocar
# fila.c -> mesmo nome de fila.o. fila.c sera recompilado
fila.o: fila.h

# main.c e main.o - mesmo nome, nao precisa explicitar o comando
# depende do TAD aplicado no codigo, houve include
main.o: fila.h

# possibilitar remover os arquivos .o e o executavel
clean:
	rm *.o main