#include "webLib.hpp"

confFileParam::confFileParam()
: _port(0), _client_max_body_size(0),_server_name(""), _error_pages(),_server_address() {};

confFileParam::~confFileParam() {};

void confFileParam::setPort(int port_temp)
{
	this->_port = port_temp;
}

void confFileParam::setServerName(std::string server_name_temp)
{
	this->_server_name = server_name_temp;
}

int confFileParam::getPort() const
{
	return this->_port;
}

uint32_t confFileParam::getHost() const
{
	return this->_server_address.sin_addr.s_addr;
}

std::string confFileParam::getServerName() const
{
	return this->_server_name;
}

void confFileParam::setHost(uint32_t host)
{
	this->_server_address.sin_addr.s_addr = htonl(host);
}

void confFileParam::setErrorPages(std::vector<std::string> error_pages_temp)
{
    std::vector<std::string>::iterator it = error_pages_temp.begin();
    ++it;
	std::vector<std::string>::iterator next_it = it;
	++next_it;
	std::string temp = *next_it;
	this->_error_pages[atoi((*it).c_str())] = (*next_it).substr(0,(*next_it).length() - 1);
}

void confFileParam::setClientMaxBodySize(int num)
{
	this->_client_max_body_size = num;
}

std::map<int,std::string> confFileParam::getErrorPages() const
{
	return this->_error_pages;
}

int confFileParam::getClientMaxBodySize() const
{
	return this->_client_max_body_size;
}

std::ostream &operator<<(std::ostream &stream,confFileParam & arg)
{
	stream << "Server" << std::endl;
	stream << "Port: " << arg.getPort() << std::endl;
	stream << "Server Name: " << arg.getServerName() << std::endl;
	stream << "Host: " << binaryToIp(arg.getHost()) << std::endl;
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
	stream << "Client Max Body Size: " << arg.getClientMaxBodySize() << std::endl;
	return stream;
}