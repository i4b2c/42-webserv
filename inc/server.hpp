#ifndef SERVER_HPP
#define SERVER_HPP

#include "webLib.hpp"

class Server
{
	private:
		struct sockaddr_in address;
		int socket_fd;
		int bind_fd;
	public:
		Server(int domain,int port, u_long interface, int service, int protocol);
		~Server(void);
		static void testConnection(int fd);
		int getSocket(void) const;
		int getBind(void) const;
		struct sockaddr_in getAddress(void) const;
};

#endif