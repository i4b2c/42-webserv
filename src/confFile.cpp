#include "confFile.hpp"
#include "utils.hpp"

confFile::confFile(std::string const conf_file)
: _port(0)
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
			this->_port = atoi(line_temp.substr(6,line_temp.length()).c_str());
		conf_file_complete += line_temp;
		conf_file_complete += "\n";
	}
}

int confFile::getPort() const
{
	return this->_port;
}


std::ostream &operator<<(std::ostream & stream, confFile & file)
{
	stream << file.getPort();
	return stream;
}