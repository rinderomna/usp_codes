# variavel
objects = main.o pilha.o

# acesso a variavel objects, com conteudo sendo os arquivos main.o e pilha.o
# esses arquivos objeto sao dependencias do executavel teste
# main.o e pilha.o devem ser link editados para formar o executavel teste
# gcc main.o pilha.o -o teste -> explicito

teste: $(objects)
	gcc $(objects) -o teste 

# o Makefile reconhece que eh preciso compilar pilha.c, mesmo sem colocar
# pilha.c -> mesmo nome de pilha.o. pilha.c sera recompilado
pilha.o: pilha.h

# main.c e main.o - mesmo nome, nao precisa explicitar o comando
# depende do TAD aplicado no codigo, houve include
main.o: pilha.h

# possibilitar remover os arquivos .o e o executavel
clean:
	rm *.o teste