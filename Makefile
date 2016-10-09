all: obj/splay.o obj/main.o
	gcc obj/splay.o obj/main.o -Wall -o splay

obj/splay.o: src/splay.c src/splay.h
	gcc -c src/splay.c -o obj/splay.o

obj/main.o: src/main.c
	gcc -c src/main.c -o obj/main.o
