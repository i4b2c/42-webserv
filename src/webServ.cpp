#include "webLib.hpp"

#define DOMAIN_DEFAULT AF_INET
#define TYPE_DEFAULT SOCK_STREAM
#define PROTOCOL_DEFAULT 0

bool g_closeServer = false;

static void closeServer(int signum)
{
	(void)signum;
	std::cout << "\n";
	g_closeServer = true;
	exit(EXIT_SUCCESS);
}

void webServ::configServerFile(confFile & conf_file)
{
	std::vector<std::string>::iterator it,itn;
	it = conf_file.begin();
	itn = conf_file.end();
	while(it != itn)
	{
		if((*it).find("server") != std::string::npos)
		{
			++it;
			if((*it).empty())
				error("Invalid config file");
			confFileParam conf_file_param_temp;
			while((*it).find("}") == std::string::npos)
			{
				if((*it).find("listen") != std::string::npos)
				{
					cleanSpaces(*it);
					conf_file_param_temp.setPort((atoi((*it).substr(6,(*it).length() - 1).c_str())));
				}
				else if((*it).find("server_name") != std::string::npos)
				{
					cleanSpaces(*it);
					conf_file_param_temp.setServerName((*it).substr(11,(*it).length() - 1));
				}
				else if((*it).find("host") != std::string::npos)
				{
					cleanSpaces(*it);
					conf_file_param_temp.setHost(ipToBinary((*it).substr(4,(*it).length() - 1)));
				}
				if((*it).find("}") != std::string::npos)
				{
					this->confFileParams.push_back(conf_file_param_temp);
					break;
				}
				++it;
			}
		}
		++it;
	}
}

void webServ::printConfFiles()
{
	for(std::vector<confFileParam>::iterator it = this->confFileParams.begin(); it != this->confFileParams.end();++it)
	{
		std::cout << *it << std::endl;
	}
}

webServ::webServ()
: servers(),clients(), confFileParams()
{
	signal(SIGPIPE,SIG_IGN);
	signal(SIGINT, closeServer);
	printAtTerminal("Starting Server...");
}


// webServ::webServ()
// : server(),client(),confFile(),params()
// {
// 	this->getConfFile("conf/default.conf");
// }

webServ::~webServ()
{
	printAtTerminal("Closing Server...");
}

// void webServ::addServer()
// {
// 	static int idx = 0;
// 	Server serverTemp(AF_INET,atoi(this->params["listen"].c_str()),INADDR_ANY,SOCK_STREAM,0);
// 	this->server.push_back(serverTemp);
// 	this->id = idx;
// 	idx++;
// }

// void webServ::addServer(int domain, int port, u_long interface, int service, int protocol)
// {
// 	Server serverTemp(domain,port,interface,service,protocol);
// 	this->server.push_back(serverTemp);
// }

// void webServ::addClient(int idx)
// {
// 	Client clientTemp(idx);
// 	this->client.push_back(clientTemp);
// }

// void webServ::starting(void)
// {
// 	struct pollfd pfd;
// 	pfd.fd = this->server.at(this->id).getSocket();
// 	pfd.events = POLLIN;

// 	int idx = 0;
// 	while (!g_closeServer)
// 	{
// 		int poll_ret = poll(&pfd, 1, -1);
// 		if (poll_ret < 0)
// 		{
// 			return;
// 		}
// 		else if (poll_ret == 0)
// 		{
// 			continue;
// 		}
// 		else if (pfd.revents & POLLIN)
// 		{
// 			this->addClient(idx);
// 			this->client.at(this->client.size() - 1).connect(this->server.at(this->id).getSocket());
// 			idx++;
// 		}
// 		else
// 		{
// 		}
// 	}
// }