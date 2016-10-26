all: build

build:	q1.c q2.c q3.c q4.c
	gcc -o q1.o q1.c
	gcc -o q2.o q2.c
	gcc -o q3.o q3.c
	gcc -o q4.o q4.c
	
q1:	q1.o
	./q1.o

q2:	q2.o
	./q2.o

q3: q3.o
	./q3.o

q4: q4.o
	./q4.o

clean:
	rm *.o
