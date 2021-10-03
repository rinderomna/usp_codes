objects = *.c

all: $(objects)
	gcc -g $(objects) -o bgen
mode1:
	./bgen mode1 20 20 6
mode2:
	./bgen mode2 30 20 5
mode3:
	./bgen mode3 30 40 4
erase:
	rm *.board
clean:
	rm bgen
clean-all:
	rm bgen *.board
