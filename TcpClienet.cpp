//============================================================================
// Name        : TcpClienet.cpp
// Author      : (c) Ankur Neog
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>


#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 8 /*maximum number of client connections */

using namespace std;

int main(int argc, char **argv) {
	cout << "TCP CLIENT" << endl; // prints TCP CLIENT
	int sockfd;
	struct sockaddr_in serverAddr;
	char sendline[MAXLINE];
	char recvline[MAXLINE];
	if(argc!=2)
	{
	    perror("Usage :: tcpclient <ip address Of the Server");
	    exit(1);
	}
	//Create Socket For the Client
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))<0){
	    perror("Problem Creating Socket .... ");
	    exit(2);
	}
	memset(&serverAddr,0,sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
	serverAddr.sin_port = htons(SERV_PORT);

	//Connect client to the server

	if(connect(sockfd,(struct sockaddr *)&serverAddr,sizeof(serverAddr))<0)
	{
	    perror("Problem in Connecting to Server");
	    exit(3);
	}

	while(fgets(sendline,MAXLINE,stdin)!=NULL)
	{
	    send(sockfd,sendline,strlen(sendline),0);
	    if(recv(sockfd,recvline,MAXLINE,0)==0){
	        perror("The Server Terminated Prematurely ");
	        exit(4);
	    }
	    printf("%s\n","String recieved from SERVER...");
	    fputs(recvline,stdout);
	}

	return 0;
}
