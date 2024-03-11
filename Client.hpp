#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Server.hpp"

class Client
{
	private:
		struct sockaddr_in address;
		socklen_t client_size;
		int sock;
		char buffer[1024];
	public:
		Client();
		~Client();
};

Client::Client(void)
{

}

#endif