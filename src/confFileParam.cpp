#include "webLib.hpp"

confFileParam::confFileParam()
: _port(0), _server_name(""), _server_address() {};

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

std::ostream &operator<<(std::ostream &stream,confFileParam & arg)
{
	stream << "Server" << std::endl;
	stream << "Port: " << arg.getPort() << std::endl;
	stream << "Server Name: " << arg.getServerName() << std::endl;
	stream << "Host: " << binaryToIp(arg.getHost()) << std::endl;
	return stream;
}