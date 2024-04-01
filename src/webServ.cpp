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
			confServer conf_file_param_temp;
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
				else if((*it).find("error_page") != std::string::npos)
				{
					std::vector<std::string> error_pages_temp = splitString(*it,' ');
					conf_file_param_temp.setErrorPages(error_pages_temp);
				}
				else if((*it).find("client_max_body_size") != std::string::npos)
				{
					cleanSpaces(*it);
					conf_file_param_temp.setClientMaxBodySize(atoi((*it).substr(20,(*it).length() - 1).c_str()));
				}
				else if((*it).find("root") != std::string::npos)
				{
					cleanSpaces(*it);
					conf_file_param_temp.setRoot((*it).substr(4,(*it).length() - 1));
				}
				else if((*it).find("auto_index") != std::string::npos)
				{
					cleanSpaces(*it);
					conf_file_param_temp.setAutoIndex((*it).substr(10,(*it).length() - 1));
				}
				else if((*it).find("index") != std::string::npos)
				{
					cleanSpaces(*it);
					conf_file_param_temp.setIndex((*it).substr(5,(*it).length() - 1));
				}
				else if((*it).find("location") != std::string::npos)
				{
					std::vector<std::string> location_path_temp = splitString(*it,' ');
					Location location_temp;
					/*
						Ainda nao fiz a verificacao mas quando tiver
						size == 2 e encontrar '{' ele tem que retornar error
					*/
					location_temp.setPath(location_path_temp[1]);
					++it;
					while((*it).find("}") == std::string::npos)
					{
						if((*it).find("root") != std::string::npos)
						{
							cleanSpaces(*it);
							location_temp.setRoot((*it).substr(4,(*it).length() - 1));
						}
						if(it != itn)
							++it;
						if((*it).find("}") != std::string::npos || it == itn)
						{
							conf_file_param_temp.setLocation(location_temp);
							break;
						}
					}
				}
				if(it != itn)
					++it;
				if((*it).find("}") != std::string::npos || it == itn)
				{
					conf_file_param_temp.setSocket();
					this->_conf_server.push_back(conf_file_param_temp);
					break;
				}
			}
		}
		++it;
	}
}

void webServ::printConfFiles()
{
	for(std::vector<confServer>::iterator it = this->_conf_server.begin(); it != this->_conf_server.end();++it)
	{
		std::cout << *it << std::endl;
	}
}

webServ::webServ()
: _servers(), _clients(), _conf_server()
{
	signal(SIGPIPE,SIG_IGN);
	signal(SIGINT, closeServer);
	printAtTerminal("Starting Server...");
}

webServ::~webServ()
{
	printAtTerminal("Closing Server...");
}
