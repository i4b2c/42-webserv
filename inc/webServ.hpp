#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "webLib.hpp"

class confFile;
class Server;
class Client;
class confFileParam;

class webServ
{
	private:
		std::vector<Server> servers;
		std::vector<Client> clients;
		std::vector<confFileParam> confFileParams;
		// std::map<std::string,std::string> params;
	public:
		webServ();
		~webServ();
		// void addServer();
		// void addServer(int domain, int port, u_long interface, int service, int protocol);
		// void addClient(int idx);
		// void starting(void);
		void configServerFile(confFile);
		void printConfFiles();
};

#endif //WEBSERV_HPP