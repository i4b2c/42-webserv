#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "webLib.hpp"

class Client
{
	private:
		struct sockaddr_in address;
		int client;
		int idx;
		socklen_t client_size;
		ssize_t buffer_size;
	public:
		Client(int idx);
		~Client();
		void connect(int socket);

};

#endif