all: build run

build:	q1.c q2.c q3.c
	gcc -o q1.o q1.c
	gcc -o q2.o q2.c
	gcc -o q3.o q3.c

run:	q1.o q2.o q3.o
	echo "Question 1:"
	./q1.o
	echo "Question 2:"
	./q2.o
	echo "Question 3:"
	./q3.o

clean:	
	rm *.o
