/**
	Hun Jae Lee (hxl224)
	EECS338 HW4
	Due 161003

	Description:
	Shubert function to find the minimum value for -2.0 ≤ x1, x2 ≤ 2.0
	Using socket communication with port 9089
	This is the SERVER file.

	The server opens up a port then waits for the client to send data.
	Server will run @ localhost:9089
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "shubert.c"

#define PORT_NO 9089

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char* argv[]) {
	// environment setup
	int sockfd, newsockfd;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) 
	   error("ERROR opening socket");

	bzero((char *) &serv_addr, sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(PORT_NO);

	if (bind (sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) { 
		error("ERROR on binding");
	}

	listen(sockfd,5);

	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

	if (newsockfd < 0) 
	     error("ERROR on accept");

	// calculate from (x1, x2) where -2.0 ≤ x1 ≤ 2.0 && 0.0 ≤ x2 ≤ 2.0
	double x1, x2, y, min;
	for (x1 = -2; x1 <= 2; x1 += 0.05) {
	  for (x2 = 0; x2 <= 2; x2 += 0.05) {
	    y = shubert(x1, x2);
	    if (y < min)
	      min = y;
	  }
	}
	printf("<SERVER> shubert result is %f.\n", min);
	
	bzero(buffer, 256);

	n = read(newsockfd,buffer,255);
	if (n < 0) {
		error("ERROR reading from socket");
	}

    printf("<SERVER> Global minimum is %s.\n", buffer);


	// send ACK
	n = write(newsockfd, "received", 8);
	if (n < 0) {
		error("ERROR writing to socket");
	}

	close(newsockfd);
	close(sockfd);

	return 0; 
	
}
