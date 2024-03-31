#include "webLib.hpp"

confFileParam::confFileParam()
: _port(0), _server_name("") {};

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

std::string confFileParam::getServerName() const
{
	return this->_server_name;
}

void confFileParam::setHost(uint32_t host)
{
	this->_server_address.sin_addr.s_addr = htonl(host);
}

std::ostream &operator<<(std::ostream &stream,confFileParam & arg)
{
	stream << "Port: " << arg.getPort() << std::endl;
	stream << "Server Name: " << arg.getServerName();
	return stream;
}