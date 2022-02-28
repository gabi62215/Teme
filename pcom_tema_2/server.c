#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "helpers.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <netinet/tcp.h>
#include <queue>

#define STDIN 0
using namespace std;

void usage(char *file)
{
	fprintf(stderr, "Usage: %s server_port\n", file);
	exit(0);
}

struct Client
{
	string id_client;
	vector <string> topics; //subscribed topics of a client
	int sock;
	int connected = -1;
	vector <string> sf_topics; //topics with sf=1
	queue <string> stored; //messages that must be sent

	Client(string s,int x)
	{
		id_client = s;
		sock = x;
	}
};

struct Message
{
	char topic[51];
	uint8_t type;
	char m[1501];
};

map<string,Client*> clients; //map of all the clients who ever connected
map<int,Client*> clients_by_sock; //same map as above with sock as key
//each entry has a list of ids the clients subscribed to that topic
map<string,vector <string>> available_topics;

/*
	Function to parse command reveived from client
*/
void parse(char *s,int sock)
{
	char *p;
	char c[51];
	p = strtok(s," ");
	if(strcmp(p,"subscribe") == 0)
	{
		//add topic to map and vector topics of client
		//checks if the topic must be add to sf_topics
		p = strtok(NULL," ");
		available_topics[p].push_back(clients_by_sock[sock]->id_client);
		clients_by_sock[sock]->topics.push_back(p);
		strcpy(c,p);
		p = strtok(NULL," ");
		if(atoi(p) == 1)
			clients_by_sock[sock]->sf_topics.push_back(c);
	}
	else if(strcmp(p,"unsubscribe") == 0)
	{
		//deletes client id from the topic in map and deletes topic from client's topics
		p = strtok(NULL," \n");
		auto it = find(clients_by_sock[sock]->topics.begin(),
			clients_by_sock[sock]->topics.end(),p);
		if(it != clients_by_sock[sock]->topics.end())
			clients_by_sock[sock]->topics.erase(it);
		else
			printf("Client hasn't subscribed to this topic\n");

		auto itr = find(available_topics[p].begin(),available_topics[p].end(),
			clients_by_sock[sock]->id_client);
		if(itr != available_topics[p].end())
			available_topics[p].erase(itr);
		else
			printf("Client hasn't subscribed to this topic\n");
		//deletes topic from sf_topics
		auto aux = find(clients_by_sock[sock]->sf_topics.begin(),
			clients_by_sock[sock]->sf_topics.end(),p);
		if(aux != clients_by_sock[sock]->sf_topics.end())
			clients_by_sock[sock]->sf_topics.erase(aux);
	}
}

/*
	Function that builds the meesage that must be sent in buffer
*/
void getTopic(Message *data,char *buffer,struct sockaddr_in *client_addr)
{
	char port[15];
	memset(buffer,0,1600);
	sprintf(port,"%hu",ntohs(client_addr->sin_port));
	strcpy(buffer,inet_ntoa(client_addr->sin_addr));
	strcat(buffer,":");
	strcat(buffer,port);
	strcat(buffer," - ");
	strcat(buffer,data->topic);
	if(data->type == 0)
	{
		strcat(buffer," - INT - ");
		uint8_t *sign = (uint8_t *)data->m;
		if(*sign == 1)
			strcat(buffer,"-");
		uint32_t *number = (uint32_t *)(sign + 1);
		string num = to_string(ntohl(*number));
		strcat(buffer,num.c_str());
	}
	if(data->type == 1)
	{
		strcat(buffer," - SHORT_REAL - ");
		uint16_t *number = (uint16_t *)data->m;
		char number_s[8];
		char digits[4];
		sprintf(number_s,"%hu",ntohs(*number));
		strcpy(digits,&number_s[strlen(number_s) - 2]);
		number_s[strlen(number_s) - 2] = '.';
		number_s[strlen(number_s) - 1] = '\0';
		strcat(number_s,digits);
		strcat(buffer,number_s);
	}
	if(data->type == 2)
	{
		strcat(buffer," - FLOAT - ");
		uint8_t *sign = (uint8_t *)data->m;
		if(*sign == 1)
			strcat(buffer,"-");
		uint32_t *number = (uint32_t *)(sign + 1);
		uint8_t *power = (uint8_t *)(number + 1);
		double actual_number = ntohl(*number) / (pow(10,*power));

		char number_s[50];
		sprintf(number_s,"%f",actual_number);
		for(int i = strlen(number_s) - 1; i >= 0; i--)
		{
			if(number_s[i] != '0')
			{
				number_s[i + 1] = '\0';
				break;
			}
		}
		strcat(buffer,number_s);
	}
	if(data->type == 3)
	{
		strcat(buffer," - STRING - ");
		strcat(buffer,data->m);
	}
}

/*
	Functions which sends interested clients the messages and stores the messages for 
	the offline interested clients	
*/
void sendTopic(char *buffer,char *topic)
{
	int n;
	for(unsigned int i = 0; i < available_topics[topic].size(); i++)
	{
		if(clients[available_topics[topic][i]]->connected == 1)
		{
			n = send(clients[available_topics[topic][i]]->sock,buffer,1600,0);
			if(n < 0)
				printf("Failed to send\n");
		}
		else
		{
			if(find(clients_by_sock[clients[available_topics[topic][i]]->sock]
				->sf_topics.begin(),clients_by_sock[clients[available_topics[topic][i]]->sock]
				->sf_topics.end(),topic) != 
				clients_by_sock[clients[available_topics[topic][i]]->sock]->sf_topics.end())
			clients_by_sock[clients[available_topics[topic][i]]->sock]->stored.push(buffer);
		}
	}
}

/*
	Function which sends stored missed messages to the newly connected client
*/
void sendStoredTopics(int old_sock,int new_sock)
{
	int n;
	char aux[1600];
	while(!clients_by_sock[old_sock]->stored.empty())
	{
		strcpy(aux,clients_by_sock[old_sock]->stored.front().c_str());
		n = send(new_sock,aux,1600,0);
		if(n < 0)
			printf("Failed to send1\n");
		clients_by_sock[old_sock]->stored.pop();
	}
}

int main(int argc, char *argv[])
{
	int sockfd, new_sockfd, portno;
	char buffer[BUFLEN];
	char buffer_2[1600];
	struct sockaddr_in serv_addr, client_addr, serv_addr_udp;
	int n, i, ret;
	socklen_t clilen;

	fd_set read_fds;	// multimea de citire folosita in select()
	fd_set tmp_fds;		// multime folosita temporar
	int fdmax;			// valoare maxima fd din multimea read_fds

	if (argc < 2) 
		usage(argv[0]);
	
	setvbuf(stdout, NULL, _IONBF, BUFSIZ);

	// se goleste multimea de descriptori de citire (read_fds) si multimea temporara (tmp_fds)
	FD_ZERO(&read_fds);
	FD_ZERO(&tmp_fds);

	//initialize socket for listening
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	DIE(sockfd < 0, "socket");

	portno = atoi(argv[1]);
	DIE(portno == 0, "atoi");

	memset((char *) &serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	ret = bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr));
	DIE(ret < 0, "bind");

	int flag = 1;
	ret = setsockopt(sockfd,IPPROTO_TCP,TCP_NODELAY,(char *)&flag,sizeof(int));

	ret = listen(sockfd, MAX_CLIENTS);
	DIE(ret < 0, "listen");

	//initialize udp socket
	int sock_udp = socket(PF_INET, SOCK_DGRAM, 0);
	DIE(sock_udp < 0, "socket");

	memset((char *) &serv_addr_udp, 0, sizeof(serv_addr_udp));
	serv_addr_udp.sin_family = AF_INET;
	serv_addr_udp.sin_port = htons(atoi(argv[1]));
	serv_addr_udp.sin_addr.s_addr = INADDR_ANY;

	int r_udp = bind(sock_udp,(struct sockaddr *)&serv_addr_udp,sizeof(serv_addr_udp));
	DIE(r_udp < 0, "bind");

	//add udp_socket,tcp_socket and STDIN
	FD_SET(sockfd, &read_fds);
	FD_SET(sock_udp, &read_fds);
	FD_SET(STDIN, &read_fds);
	if(sockfd > sock_udp)
		fdmax = sockfd;
	else
		fdmax = sock_udp;

	while (1) {
		tmp_fds = read_fds;
		 
		ret = select(fdmax + 1, &tmp_fds, NULL, NULL, NULL);
		DIE(ret < 0, "select");
		
		for (i = 0; i <= fdmax; i++) {
			if (FD_ISSET(i, &tmp_fds)) 
			{
				if(i == STDIN) 
				{
					memset(buffer, 0, BUFLEN);
					read(STDIN,buffer,BUFLEN - 1);
					if(strcmp(buffer,"exit\n") == 0)
					{
						for(int i = 1; i <= fdmax; i++)
							close(i);
						return 0;
					}
				}
				if (i == sockfd) 
				{
					//new connection on the listening socket,accepts it
					clilen = sizeof(client_addr);
					new_sockfd = accept(sockfd, (struct sockaddr *) &client_addr, &clilen);
					DIE(new_sockfd < 0, "accept");

					ret = setsockopt(new_sockfd,IPPROTO_TCP,TCP_NODELAY,(char *)&flag,sizeof(int));

					memset(buffer,0,BUFLEN);
					int n = recv(new_sockfd,buffer,sizeof(buffer),0);
					DIE(n < 0, "recv");

					//add new received socket from accept to set
					FD_SET(new_sockfd, &read_fds);
					if (new_sockfd > fdmax) { 
						fdmax = new_sockfd;
					}

					//check if the client connected before
					if(clients.find(buffer) == clients.end())
						{
							printf("New client %s connected from %s:%hu.\n",buffer,
								inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

							clients.insert(make_pair(buffer,new Client(buffer,new_sockfd)));
							clients_by_sock.insert(make_pair(new_sockfd,
								new Client(buffer,new_sockfd)));

							clients[buffer]->connected = 1;
							clients_by_sock[new_sockfd]->connected = 1;
						}
						else 
						{
							if(clients[buffer]->connected == 1)
							{
								printf("Client %s already connected.\n",buffer);

								close(new_sockfd);//close new socket
								FD_CLR(new_sockfd,&read_fds);//remove it from set
							}
							else
							{
								printf("New client %s connected from %s:%d.\n",buffer,
								inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

								//send stored data to the client who reconnected
								sendStoredTopics(clients[buffer]->sock,new_sockfd);
								if(new_sockfd != clients[buffer]->sock)
								{
									clients_by_sock.insert(make_pair(new_sockfd,
										new Client(buffer,new_sockfd)));

									copy(clients_by_sock[clients[buffer]->sock]->
										topics.begin(),clients_by_sock[clients[buffer]->sock]->
										topics.end(),back_inserter(clients_by_sock[new_sockfd]->topics));

									Client *aux = clients_by_sock[clients[buffer]->sock];
									clients_by_sock.erase(clients[buffer]->sock);
									delete aux;
								}
								
								clients_by_sock[new_sockfd]->connected = 1;
								clients[buffer]->sock = new_sockfd;
								clients[buffer]->connected = 1;
							}
						}
				} 
				else 
				{
					if(i == sock_udp){
						//receive data from udp client
						memset(buffer_2,0,1600);
						int bytesread = recvfrom(i,buffer_2,1600,0,
							(struct sockaddr *)&client_addr,&clilen);

						DIE(bytesread < 0, "recvfrom");

						Message data;
						memcpy(data.topic,buffer_2,50);
						data.type = *(buffer_2 + 50);
						if(data.type == 0)
							memcpy(data.m,buffer_2 + 51,5);
						if(data.type == 1)
							memcpy(data.m,buffer_2 + 51,2);
						if(data.type == 2)
							memcpy(data.m,buffer_2 + 51,6);
						if(data.type == 3)
							strcpy(data.m,buffer_2 + 51);
							
						//send received data to interested clients
						getTopic(&data,buffer_2,&client_addr);
						sendTopic(buffer_2,data.topic);

					}
					else
					{
						//receive data from tcp client
						memset(buffer, 0, BUFLEN);
						n = recv(i, buffer, sizeof(buffer), 0);
						DIE(n < 0, "recv");

						if (n == 0) 
						{
							cout << "Client " << clients_by_sock[i]->id_client 
								<< " disconnected.\n";

							clients[clients_by_sock[i]->id_client]->connected = -1;
							clients_by_sock[i]->connected = -1;

							close(i);//close socket of disconnected client
							FD_CLR(i,&read_fds);//and delete it from set
						} else 
							parse(buffer,i);//parse command from tcp client
					}
				}
			}
		}
	}

	close(sockfd);

	return 0;
}
