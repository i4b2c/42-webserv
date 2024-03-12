#include "client.hpp"
#include <sys/poll.h>

Client::Client(int idx)
: address(),client(0),idx(idx),client_size(sizeof(this->address)),buffer_size(1024)
{
}

Client::~Client(void) {};

void Client::connect(int socket)
{
	char buffer[this->buffer_size];
	this->client = accept(socket,(struct sockaddr *)&this->address,&client_size);
	int read_bytes = recv(this->client,buffer,this->buffer_size,0);
	if(read_bytes < 0)
	{
		std::cerr << "Error ao ler os dados" << std::endl;
		close(this->client);
	}
	std::cout << buffer << std::endl;
	close(this->client);
}