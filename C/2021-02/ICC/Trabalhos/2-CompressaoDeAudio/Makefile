objects = *.c

all: $(objects)
	gcc $(objects) -g -o bin -lm
run:
	./bin
clean:
	rm bin *.wav
audios:
	cp ./documents/audios/* .
test1: all audios
	./bin < tests/1.in > results/1.my
test2: all audios
	./bin < tests/2.in > results/2.my
test3: all audios
	./bin < tests/3.in > results/3.my
