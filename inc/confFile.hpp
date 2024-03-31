#ifndef CONFFILE_HPP
#define CONFFILE_HPP

#include "webLib.hpp"

class confFile
{
	private:
		std::vector<std::string> _content;
		std::string 			_path;
		size_t 					_size;
	public:
		void init();
		std::string getServerName() const;
		std::vector<std::string>::iterator begin();
		std::vector<std::string>::iterator end();

		confFile(std::string const arg);
		~confFile();
};

#endif