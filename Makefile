CC = gcc
CFLAGS = -Wall -std=c99 -g
LDLIBS = -lm -lcsfml-graphics

main: main.o particle.o particleSystem.o

main.o: particleSystem.h

particleSystem.o: particle.h

clean:
	rm -f *.o
	rm -f main
