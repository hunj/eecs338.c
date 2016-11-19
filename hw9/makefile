all: build

build:	q1.c q2.c
	gcc -o q1.o q1.c
	g++-6 -o q2.o q2.c -fopenmp
	
q1:	q1.o
	./q1.o 4

q2:	q2.o
	export OMP_NUM_THREADS=8
	./q2.o

clean:
	rm *.o
