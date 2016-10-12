all: build run

build:	hunjmp.c
	gcc -o hunjmp.o hunjmp.c -Wall -pedantic
	
run:	hunjmp.o
	export OMP_NUM_THREADS=#{n}
	./hunjmp.o

clean:
	rm *.o
