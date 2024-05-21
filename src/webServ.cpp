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

/*
	Constructor and Destructor
*/

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

webServ::ErrorException::ErrorException(std::string mensage_temp) throw()
: _mensage(mensage_temp) {};

webServ::ErrorException::~ErrorException() throw() {};

/*
	configServerFile
	used to read the file .conf and put on std::vector<confServer> _conf_server;
*/
void webServ::configServerFile(confFile & conf_file)
{
	std::vector<std::string>::iterator it,itn;
	it = conf_file.begin();
	itn = conf_file.end();
	bool check_open_server = false;
	while(it != itn)
	{
		if((*it).find("server") != std::string::npos)
		{
			if((*it).find("{") != std::string::npos)
				check_open_server = true;
			++it;
			confServer conf_file_param_temp;
			while((*it).find("}") == std::string::npos)
			{
				if((*it).find("{") != std::string::npos && (*it).find("location") == std::string::npos)
					check_open_server = true;
				else if((*it).find("listen") != std::string::npos)
				{
					if(!checkToken(*it))
						throw webServ::ErrorException("Error: Missing ';' on listen");
					cleanSpaces(*it);
					conf_file_param_temp.setPort((atoi((*it).substr(6,(*it).length() - 1).c_str())));
				}
				else if((*it).find("server_name") != std::string::npos)
				{
					if(!checkToken(*it))
						throw webServ::ErrorException("Error: Missing ';' on server_name");
					cleanSpaces(*it);
					conf_file_param_temp.setServerName((*it).substr(11,(*it).length() - 1));
				}
				else if((*it).find("host") != std::string::npos)
				{
					if(!checkToken(*it))
						throw webServ::ErrorException("Error: Missing ';' on host");
					cleanSpaces(*it);
					conf_file_param_temp.setHost(ipToBinary((*it).substr(4,(*it).length() - 1)));
				}
				else if((*it).find("error_page") != std::string::npos)
				{
					if(!checkToken(*it))
						throw webServ::ErrorException("Error: Missing ';' on error_page");
					std::vector<std::string> error_pages_temp = splitString(*it,' ');
					conf_file_param_temp.setErrorPages(error_pages_temp);
				}
				else if((*it).find("client_max_body_size") != std::string::npos)
				{
					if(!checkToken(*it))
						throw webServ::ErrorException("Error: Missing ';' on client_max_body_size");
					cleanSpaces(*it);
					conf_file_param_temp.setClientMaxBodySize(atoi((*it).substr(20,(*it).length() - 1).c_str()));
				}
				else if((*it).find("root") != std::string::npos)
				{
					if(!checkToken(*it))
						throw webServ::ErrorException("Error: Missing ';' on root");
					cleanSpaces(*it);
					conf_file_param_temp.setRoot((*it).substr(4,(*it).length() - 1));
				}
				else if((*it).find("auto_index") != std::string::npos)
				{
					if(!checkToken(*it))
						throw webServ::ErrorException("Error: Missing ';' on auto_index");
					cleanSpaces(*it);
					conf_file_param_temp.setAutoIndex((*it).substr(10,(*it).length() - 1));
				}
				else if((*it).find("index") != std::string::npos)
				{
					if(!checkToken(*it))
						throw webServ::ErrorException("Error: Missing ';' on index");
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
					bool check_open_location = false;
					if((*it).find("{") != std::string::npos)
						check_open_location = true;
					++it;
					while((*it).find("}") == std::string::npos)
					{
						if((*it).find("{") != std::string::npos)
							check_open_location = true;
						if((*it).find("root") != std::string::npos)
						{
							if(!checkToken(*it))
								throw webServ::ErrorException("Error: Missing ';' on root inside the location");
							cleanSpaces(*it);
							location_temp.setRoot((*it).substr(4,(*it).length() - 1));
						}
						else if((*it).find("autoindex") != std::string::npos)
						{
							if(!checkToken(*it))
								throw webServ::ErrorException("Error: Missing ';' on root inside the auto index");
							cleanSpaces(*it);
							if((*it).find("false") != std::string::npos && (*it).size() == 14)
								location_temp.setAutoIndex(false);
							else if((*it).find("true") != std::string::npos && (*it).size() == 13)
								location_temp.setAutoIndex(true);
							else
								throw webServ::ErrorException("Error: Invalid type of auto index");
						}
						if(it != itn)
							++it;
						if((*it).find("}") != std::string::npos || it == itn)
						{
							if(check_open_location == false)
								throw webServ::ErrorException("Unclosed brackets location");
							conf_file_param_temp.setLocation(location_temp);
							check_open_location = false;
							break;
						}
					}
				}
				else if((*it).empty() || checkOnlySpaces((*it))) {}
				else
				{
					throw webServ::ErrorException("Invalid token in conf file" + (*it));
				}
				if(it != itn)
					++it;
				if((*it).find("}") != std::string::npos || it == itn)
				{
					if(check_open_server == false)	
						throw webServ::ErrorException("Unclosed brackets server");
					conf_file_param_temp.setSocket();
					this->_conf_server.push_back(conf_file_param_temp);
					check_open_server = false;
					break;
				}
			}
		}
		++it;
	}
}


/*
	printConfFiles
	used to print the conf files stored in std::vector<confServer> _conf_server;
*/
void webServ::printConfFiles()
{
	for(std::vector<confServer>::iterator it = this->_conf_server.begin(); it != this->_conf_server.end();++it)
	{
		std::cout << *it << std::endl;
	}
}

/*
	ErrorException
*/
const char * webServ::ErrorException::what() const throw()
{
	return this->_mensage.c_str();
}