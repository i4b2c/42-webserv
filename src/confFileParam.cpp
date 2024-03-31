#include "webLib.hpp"

confFileParam::confFileParam()
: _port(0),_host(0),_server_name(""),_root(""),_index(""),_auto_index(false),_client_max_body_size(0), _error_pages(),_server_address() {};

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

std::string confFileParam::getRoot() const
{
	return this->_root;
}

std::string confFileParam::getServerName() const
{
	return this->_server_name;
}

std::string confFileParam::getIndex() const
{
	return this->_index;
}

bool confFileParam::getAutoIndex() const
{
	return this->_auto_index;
}

void confFileParam::setHost(uint32_t host)
{
	this->_server_address.sin_addr.s_addr = htonl(host);
	this->_host = htonl(host);
}

void confFileParam::setRoot(std::string root)
{
	this->_root = root;
}

void confFileParam::setIndex(std::string index)
{
	this->_index = index;
}

void confFileParam::setAutoIndex(std::string auto_index)
{
	if(auto_index == "on")
		this->_auto_index = true;
	else
		this->_auto_index = false;
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
	stream << "Index: " << arg.getIndex() << std::endl;
	if(arg.getAutoIndex() == true)
		stream << "Auto Index: on" << std::endl;
	else
		stream << "Auto Index: off" << std::endl;
	stream << "Root: " << arg.getRoot() << std::endl;
	stream << "Client Max Body Size: " << arg.getClientMaxBodySize() << std::endl;
	return stream;
}