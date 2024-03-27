#include "server.hpp"
#include <iostream>

Server::Server(int domain, int port, u_long interface, int service, int protocol)
: address(), socket_fd()
{
	this->address.sin_family = domain;
	this->address.sin_port = htons(port);
	this->address.sin_addr.s_addr = htonl(interface);

	this->socket_fd = socket(domain,service,protocol);
	Server::testConnection(this->socket_fd);

	int reuse = -1;
	if (setsockopt(this->socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}

	this->bind_fd = bind(this->socket_fd,(struct sockaddr *)&this->address,sizeof(this->address));
	Server::testConnection(this->bind_fd);

	if(listen(this->socket_fd,10) < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

Server::~Server(void) {};

void Server::testConnection(int fd)
{
	if(fd < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

int Server::getBind(void) const
{
	return this->bind_fd;
}

int Server::getSocket(void) const
{
	return this->socket_fd;
}

struct sockaddr_in Server::getAddress(void) const
{
	return this->address;
}