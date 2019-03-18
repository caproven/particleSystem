CC = gcc
CFLAGS = -Wall -std=c99 -g
LDLIBS = -lcsfml-graphics

main: main.o particle.o

main.o: particle.h

clean:
	rm -f *.o
	rm -f main
