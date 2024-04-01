#include "webLib.hpp"

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
	std::cout << "Nova Conexao: " << this->idx << std::endl;
	std::cout << buffer << std::endl;

	// Apenas para mostrar alguma coisa no client
	// write(this->client,"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 1234\n\n",63);
	// write(this->client,"<!DOCTYPE html><html><head><meta charset='UTF-8'/><title>Document</title></head><body><!-- Conteúdo --></body></html>\n",120);
	close(this->client);
}