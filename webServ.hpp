#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <iostream> //in and out stream
#include <sys/socket.h> //usar sockets
#include <vector>
#include "server.hpp"
#include "client.hpp"

class webServ
{
	private:
		std::vector<Server> server;
		std::vector<Client> client;
		int id;
	public:
		webServ();
		~webServ();
		void addServer();
		void addServer(int domain, int port, u_long interface, int service, int protocol);
		void addClient(int idx);
		void starting(void);
};

#endif //WEBSERV_HPP