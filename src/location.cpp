#include "webLib.hpp"

/*
	+----------------------------+
	| Constructor and Destructor |
	+----------------------------+
*/

Location::Location()
: _path(""), _root(""), _auto_index(false) {};

Location::~Location() {};

/*
	+---------------+
	| Set Functions |
	+---------------+
*/

void Location::setPath(std::string const path_temp)
{
	this->_path = path_temp;
}

void Location::setRoot(std::string const root_temp)
{
	this->_root = root_temp;
}

void Location::setAutoIndex(bool const auto_index_temp)
{
	this->_auto_index = auto_index_temp;
}

/*
	+---------------+
	| Get Functions |
	+---------------+
*/

std::string Location::getPath() const
{
	return this->_path;
}

std::string Location::getRoot() const
{
	return this->_root;
}

std::string Location::getAutoIndex() const
{
	if(this->_auto_index == false)
		return "false";
	return "true";
}

// EXTRA

std::ostream &operator<<(std::ostream &stream, Location & arg)
{
	stream << "Location " << arg.getPath() << std::endl;
	stream << "Root: " << arg.getRoot() << std::endl;
	stream << "Auto Index: " << arg.getAutoIndex() << std::endl;
	stream << std::endl;
	return stream;
}
