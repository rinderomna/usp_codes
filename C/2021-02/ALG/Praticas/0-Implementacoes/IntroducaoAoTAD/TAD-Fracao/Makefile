somafrac: somafrac.o fracao.o
	gcc -o somafrac somafrac.o fracao.o -g

somafrac.o: somafrac.c
	gcc -c somafrac.c -g

fracao.o: fracao.c fracao.h
	gcc -c fracao.c -g

clean:
	rm *.o somafrac