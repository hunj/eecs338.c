all: build

build:	q1.c q2.c
	gcc -o q1.o q1.c
	gcc -o q2.o q2.c

q1:	q1.o 
	echo "Question 1:"
	./q1.o

q2: q2.o
	echo "Question 2:"
	./q2.o

q3: q3.o
	echo "Question 3:"
	./q3.o

clean:	
	rm *.o
