#ifndef SERVER_HPP
#define SERVER_HPP

#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <stdio.h>
#include <arpa/inet.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

class Server
{
	private:
		struct sockaddr_in address;
		int sock;
	public:
		Server();
		~Server();
		int getSock() const;
		struct sockaddr_in getAddress() const;
};

#endif