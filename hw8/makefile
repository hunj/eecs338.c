all: build

build:	q1a.c q1b.c 
	g++-6 -o q1a.o q1a.c -lpthread
	g++-6 -o q1b.o q1b.c -lpthread
	gcc -o q2.o q2.c -lpthread
	
q1a:	q1a.o
	./q1a.o

q1b:	q1b.o
	./q1b.o

q2:	q2.o
	./q2.o

clean:
	rm *.o
