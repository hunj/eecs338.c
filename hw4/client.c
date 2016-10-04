/**
	Hun Jae Lee (hxl224)
	EECS338 HW4
	Due 161003

	Description:
	Shubert function to find the minimum value for -2.0 ≤ x1, x2 ≤ 2.0
	Using socket communication
	This is the CLIENT file.

	The client connects to server using the preset port number (9089).
	Client will connect to localhost:9089
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "shubert.c"

#define PORT_NO 9089

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname("localhost");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(PORT_NO);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        error("ERROR connecting");
    }

    // calculate from (x1, x2) where -2.0 ≤ x1 ≤ 2.0 && -2.0 ≤ x2 ≤ 0.0
    double x1, x2, y, min;
    for (x1 = -2; x1 <= 2; x1 += 0.05) {
      for (x2 = -2; x2 <= 0; x2 += 0.05) {
        y = shubert(x1, x2);
        if (y < min)
          min = y;
      }
    }
    printf("<CLIENT> shubert result is %f\n", min);

    // convert result to string so we can send
    
    sprintf(buffer, "%.6f", min);

    n = write(sockfd, buffer, strlen(buffer));

    if (n < 0) {
    	error("ERROR writing to socket");
    }
    bzero(buffer,256);

    // this is ACKing the ACK
    n = read(sockfd,buffer,255);
    if (n < 0) {
    	error("ERROR reading from socket");
    }


    close(sockfd);
    return 0;
}
