all: build

build:	q1.c q2.c
	gcc -o q1.o q1.c -lpthread
	gcc -o q2.o q2.c -lpthread
	
q1:	q1.o
	./q1.o

q2:	q2.o
	./q2.o

clean:
	rm *.o
