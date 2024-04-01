#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "webLib.hpp"

class confFile;
class Server;
class Client;
class confServer;

class webServ
{
	private:
		std::vector<Server> _servers;
		std::vector<Client> _clients;
		std::vector<confServer> _conf_server;
		// std::map<std::string,std::string> params;
	public:
		webServ();
		~webServ();
		// void addServer();
		// void addServer(int domain, int port, u_long interface, int service, int protocol);
		// void addClient(int idx);
		// void starting(void);
		void configServerFile(confFile & arg);
		void printConfFiles();
};

#endif //WEBSERV_HPP