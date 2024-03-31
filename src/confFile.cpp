#include "webLib.hpp"

confFile::confFile(std::string const conf_file_path)
: _content(),_path(conf_file_path), _size(0) {};

confFile::~confFile() {};

std::vector<std::string>::iterator confFile::begin()
{
	return this->_content.begin();
}

std::vector<std::string>::iterator confFile::end()
{
	return this->_content.end();
}

void confFile::init()
{
	std::ifstream arq(this->_path.c_str());
	if(!arq.is_open())
	{
		std::cerr << "Error" << std::endl;
		return ;
	}
	std::string line_temp;
	while(std::getline(arq,line_temp))
	{
		this->_content.push_back(line_temp);
		this->_size += line_temp.length();
	}
}
