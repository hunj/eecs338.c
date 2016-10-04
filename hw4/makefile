all: build

build:	fork_pipe.c server.c client.c threads.c shubert.c
	gcc -o pipe.o fork_pipe.c -Wall -pedantic
	gcc -o server.o server.c -Wall -pedantic
	gcc -o client.o client.c -Wall -pedantic
	gcc -o threads.o threads.c -lpthread -Wall -pedantic
	
pipe:	pipe.o
	echo "Shubert Function with fork() and pipe comms:"
	./pipe.o

socket: 	server.o client.o
	echo "Shubert Function with server/client and socket comms:"
	./server.o & ./client.o

threads: 	threads.o
	echo "Shubert Function with multithreading:"
	./threads.o

clean:
	rm *.o
