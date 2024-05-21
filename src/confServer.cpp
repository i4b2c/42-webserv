#include "webLib.hpp"

/*
	+----------------------------+
	| Constructor and Destructor |
	+----------------------------+
*/

confServer::confServer()
: _socket_fd(0),_port(0),_host(0),_server_name(""),_root(""),_index(""),_auto_index(false),_client_max_body_size(0), _error_pages(),_server_address(),_location() {};

confServer::~confServer()
{
	if(!this->_socket_fd)
		close(this->_socket_fd);
}

confServer::ErrorException::ErrorException(std::string mensage_temp) throw()
: _mensage(mensage_temp)
{}

confServer::ErrorException::~ErrorException() throw() {};

/*
	+---------------+
	| Set Functions |
	+---------------+
*/

void confServer::setPort(int port_temp)
{
	this->_port = port_temp;
}

void confServer::setServerName(std::string server_name_temp)
{
	this->_server_name = server_name_temp;
}

void confServer::setHost(uint32_t host)
{
	this->_host = htonl(host);
}

void confServer::setRoot(std::string root)
{
	this->_root = root;
}

void confServer::setIndex(std::string index)
{
	this->_index = index;
}

void confServer::setAutoIndex(std::string auto_index)
{
	if(auto_index == "on")
		this->_auto_index = true;
	else
		this->_auto_index = false;
}

void confServer::setErrorPages(std::vector<std::string> error_pages_temp)
{
    std::vector<std::string>::iterator it = error_pages_temp.begin();
    ++it;
	std::vector<std::string>::iterator next_it = it;
	++next_it;
	std::string temp = *next_it;
	this->_error_pages[atoi((*it).c_str())] = (*next_it).substr(0,(*next_it).length() - 1);
}

void confServer::setClientMaxBodySize(int num)
{
	this->_client_max_body_size = num;
}

void confServer::setLocation(Location location_temp)
{
	this->_location.push_back(location_temp);
}

void confServer::setSocket()
{
    // _server_address = new struct sockaddr_in;
    if((_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        throw confServer::ErrorException("Error: cannot create socket");

    int option_value = 1; // Ajuste o valor para 1 para reutilizar o endereço
    if(setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR, &option_value, sizeof(option_value)) == -1)
        throw confServer::ErrorException("Error: setsockopt failed");

    memset(&this->_server_address, 0, sizeof(struct sockaddr_in));
    this->_server_address.sin_family = AF_INET;
    this->_server_address.sin_port = htons(_port);
    this->_server_address.sin_addr.s_addr = this->_host; // Supondo que _host é uma string

    if(bind(_socket_fd, (struct sockaddr *)&this->_server_address, sizeof(struct sockaddr_in)) == -1)
        throw confServer::ErrorException("Error: cannot bind socket");
}


/*
	+---------------+
	| Get Functions |
	+---------------+
*/

int confServer::getPort() const
{
	return this->_port;
}

uint32_t confServer::getHost() const
{
	return this->_server_address.sin_addr.s_addr;
}

std::string confServer::getRoot() const
{
	return this->_root;
}

std::string confServer::getServerName() const
{
	return this->_server_name;
}

std::string confServer::getIndex() const
{
	return this->_index;
}

bool confServer::getAutoIndex() const
{
	return this->_auto_index;
}

std::map<int,std::string> confServer::getErrorPages() const
{
	return this->_error_pages;
}

int confServer::getClientMaxBodySize() const
{
	return this->_client_max_body_size;
}

std::vector<Location> confServer::getLocation() const
{
	return this->_location;
}

int confServer::getSocket() const
{
	return this->_socket_fd;
}

struct sockaddr_in confServer::getAddress() 
{
	return this->_server_address;
}
/*
	+-----------------+
	| Utils Functions |	
	+-----------------+
*/



std::ostream &operator<<(std::ostream &stream,confServer & arg)
{
	stream << "Server" << std::endl;
	stream << "Port: " << arg.getPort() << std::endl;
	stream << "Server Name: " << arg.getServerName() << std::endl;
	stream << "Host: " << binaryToIp(arg.getHost()) << std::endl;
	stream << "Socket fd: " << arg.getSocket() << std::endl;
	if(arg.getErrorPages().size() == 0)
		stream << "Error Pages: None" << std::endl;
	else
	{
		std::map<int,std::string>::iterator it;
		std::map<int,std::string> temp = arg.getErrorPages();
		it = temp.begin();
		while(it != temp.end())
		{
			stream << "Error Pages " << it->first << " : " << it->second << std::endl;
			++it;
		}
	}
	stream << "Index: " << arg.getIndex() << std::endl;
	if(arg.getAutoIndex() == true)
		stream << "Auto Index: on" << std::endl;
	else
		stream << "Auto Index: off" << std::endl;
	stream << "Root: " << arg.getRoot() << std::endl;
	stream << "Client Max Body Size: " << arg.getClientMaxBodySize() << std::endl;
	if(arg.getLocation().size() == 0)
		stream << "Location: None" << std::endl;
	else
	{
		std::vector<Location>::iterator it,itn;
		std::vector<Location> temp = arg.getLocation();
		it = temp.begin();
		itn = temp.end();
		while(it != itn)
		{
			stream << *it << std::endl;
			++it;
		}
	}
	return stream;
}

/*
	Error Exception
*/

const char * confServer::ErrorException::what() const throw()
{
	return this->_mensage.c_str();
}
