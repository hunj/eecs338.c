all: build

build:	q1a.c q1b.c 
	gcc-6 -o q1a.o q1a.c -fopenmp -lpthread
	gcc-6 -o q1b.o q1b.c -fopenmp -lpthread
	gcc-6 -o q2.o q2.c -lpthread
	
q1a:	q1a.o
	export OMP_NUM_THREADS=4
	./q1a.o

q1b:	q1b.o
	export OMP_NUM_THREADS=4
	./q1b.o

q2:	q2.o
	./q2.o

clean:
	rm *.o
