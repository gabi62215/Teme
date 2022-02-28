#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/tcp.h>
#include "helpers.h"

#define STDIN 0

/*
	Function to parse command received from STDIN
*/
void parse(char *s,int sock)
{
	char c[70];
	strcpy(c,s);
	int n;
	
	char *p;
	p = strtok(s," ");

	if(strcmp(p,"subscribe") == 0)
	{
		p = strtok(NULL," ");
		printf("Subscribed to topic.\n");
		//send
		n = send(sock,c,70,0);
	}
	else if(strcmp(p,"unsubscribe") == 0)
	{
		printf("Unsubscribed from topic.\n");
		n = send(sock,c,70,0);
	}

	DIE(n < 0, "send");
}

int main(int argc,char *argv[])
{
	int sockfd,n,ret,fdmax;
	struct sockaddr_in serv_addr;
	char buffer[1600];
	fd_set read_fds,tmp_fds;

	setvbuf(stdout, NULL, _IONBF, BUFSIZ);

	if(argc < 3)
	{
		printf("Wrong number of arguments\n");
		return 0;
	}

	//get sock for tcp
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	DIE(sockfd < 0, "socket");

	int flag = 1;
	ret = setsockopt(sockfd,IPPROTO_TCP,TCP_NODELAY,(char *)&flag,sizeof(int));
	if(ret < 0)
		printf("Coulnd't turn off Nagle's algorithm\n");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[3]));
	ret = inet_aton(argv[2], &serv_addr.sin_addr);
	DIE(ret == 0, "inet_aton");

	//connect to the server
	ret = connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
	DIE(ret < 0, "connect");

	n = send(sockfd,argv[1],strlen(argv[1]),0);
	DIE(sockfd < 0, "send");

	//add sock and STDIN to set
	FD_ZERO(&read_fds);
	FD_ZERO(&tmp_fds);
	FD_SET(STDIN, &read_fds);
	FD_SET(sockfd, &read_fds);

	fdmax = sockfd + 1;

	while(1)
	{
		tmp_fds = read_fds;

		ret = select(fdmax,&tmp_fds,NULL,NULL,NULL);
		DIE(ret < 0, "select");

		memset(buffer,0,1600);
		if(FD_ISSET(sockfd,&tmp_fds))
		{
			//receive subscribed data
			memset(buffer,0,1600);
			n = recv(sockfd,buffer,sizeof(buffer),0);
			if(n <= 0)
			{
				close(sockfd);
				break;
			}
			puts(buffer);
		}
		else if(FD_ISSET(STDIN,&tmp_fds))
		{
			//read from STDIN and send to server
			memset(buffer,0,1600);
			read(STDIN,buffer,1599);
			if(strcmp(buffer,"exit\n") == 0)
			{
				close(sockfd);
				return 0;
			}
			else
				parse(buffer,sockfd);
		}
	}
}