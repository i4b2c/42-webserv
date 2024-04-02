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
		
		/*
			Exception function
		*/
		class ErrorException: public std::exception
		{
			private:
				std::string _mensage;
			public:
				ErrorException(std::string) throw();
				virtual ~ErrorException() throw();
				const char * what() const throw();
		};


};

#endif //WEBSERV_HPP