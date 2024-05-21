#include "webLib.hpp"

/*
	+----------------------------+
	| Constructor and Destructor |
	+----------------------------+
*/

Location::Location()
: _path("") {};

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

// EXTRA

std::ostream &operator<<(std::ostream &stream, Location & arg)
{
	stream << "Location " << arg.getPath() << std::endl;
	stream << "Root: " << arg.getRoot() << std::endl;
	stream << std::endl;
	return stream;
}
