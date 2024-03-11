#include "Server.hpp"

Server::Server(void)
{
	sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock == -1)
	{
		perror("Error creating socket");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_port = htons(8080);
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(this->sock,(struct sockaddr *)&address,sizeof(address)) < 0)
	{
		perror("Error ao fazer bind do socket");
		exit(EXIT_FAILURE);
	}
	if(listen(sock,2) < 0)
	{
		perror("Error ao conectar");
		exit(EXIT_FAILURE);
	}
}

Server::~Server(void)
{
	if(close(this->sock) < 0)
	{
		perror("Error closing server socket");
		exit(EXIT_FAILURE);
	}
}

int Server::getSock(void) const
{
	return sock;
}

struct sockaddr_in Server::getAddress(void) const
{
	return address;
}
