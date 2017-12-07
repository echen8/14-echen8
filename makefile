all: main.c
	gcc -o semaphore main.c
run: all
	./semaphore
clear:
	rm *~