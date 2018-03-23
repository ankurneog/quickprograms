//============================================================================
// Name        : TcpServer.cpp
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

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 8 /*maximum number of client connections*/
using namespace std;

int main() {

    int listenfd, connfd,n;
    pid_t childpid;
    char buf[MAXLINE];
    struct sockaddr_in clientAddr, serverAddr;
    socklen_t clilen;
	cout << "TCP SERVER" << endl; // prints TCP SERVER

	listenfd = socket(AF_INET,SOCK_STREAM,0);
	if(listenfd<0)
	{
	    perror("Error Creating Socket ");
	    exit(1);
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(SERV_PORT);

	bind(listenfd,(struct sockaddr *)&serverAddr,sizeof(serverAddr));

	listen(listenfd,LISTENQ);

	cout<<"Server Running...."<<endl;

	while(1){
	    clilen = sizeof(clientAddr);

	    connfd = accept(listenfd,(struct sockaddr *)&clientAddr,&clilen);

	    if((childpid=fork())==0) // This is child
	    {
	        cout<<"Created Child for handling Incoming request ..."<<endl;
	        close(listenfd);
	        while((n=recv(connfd,buf,MAXLINE,0))>0)
	        {
	            cout<<" Recived String From Client ::: "<<endl;
	            puts(buf);
	            send(connfd,buf,n,0);
	        }
	        if(n<0)
	        {
	            perror("read error");
	            exit(0);
	        }
	    }
	    close(connfd); //close connfd in parent;

	}
	return 0;
}
