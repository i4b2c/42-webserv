#include "confFile.hpp"
#include "utils.hpp"

confFile::confFile(std::string const conf_file)
: _port(0), _server_name("")
{
	this->init(conf_file);
}

confFile::~confFile() {};

void confFile::init(std::string const conf_file)
{
	std::ifstream arq(conf_file.c_str());
	if(!arq.is_open())
	{
		std::cerr << "Error" << std::endl;
		return ;
	}
	std::string line_temp;
	std::string conf_file_complete;
	while(std::getline(arq,line_temp))
	{
		cleanSpaces(line_temp);
		if(line_temp.substr(0,6) == "listen")
			this->_port = atoi(line_temp.substr(6,line_temp.length() - 6).c_str());
		else if(line_temp.substr(0,11) == "server_name")
			this->_server_name = line_temp.substr(11,line_temp.length() - 11);
		conf_file_complete += line_temp;
		conf_file_complete += "\n";
	}
}

int confFile::getPort() const
{
	return this->_port;
}

std::string confFile::getServerName() const
{
	return this->_server_name;
}

std::ostream &operator<<(std::ostream & stream, confFile & file)
{
	stream << "port: " << file.getPort() << std::endl;
	stream << "server name: " << file.getServerName(); 
	return stream;
}