# cs335 lab1
# to compile your project, type make and press enter

all: hw1

hw1: hw1.cpp movement.cpp
	g++ hw1.cpp movement.cpp libggfonts.a -Wall -ohw1 -lX11 -lGL -lGLU -lm

clean:
	rm -f hw1
	rm -f *.o

