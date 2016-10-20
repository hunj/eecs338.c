all: build

build:	q1.c q2.c q3.c q4.c
	gcc -fopenmp -o q1.o q1.c -lm
	gcc -fopenmp -o q2.o q2.c -lm
	gcc -o q3.o q3.c -lpthread
	gcc -o q4.o q4.c -lrt
	
q1:	q1.o
	export OMP_NUM_THREADS=4
	./q1.o

q2: q2.o
	export OMP_NUM_THREADS=4
	./q2.o

q3: q3.o
	./q3.o

q4: q4.o
	./q4.o

clean:
	rm *.o
