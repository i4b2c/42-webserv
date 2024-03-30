#ifndef CONFFILE_HPP
#define CONFFILE_HPP

#include <string>
#include <iostream>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/poll.h>

class confFile
{
	private:
		int _port;
	public:
		void init(std::string const arg);
		int getPort() const;
		confFile(std::string const arg);
		~confFile();
};

std::ostream &operator<<(std::ostream & stream, confFile & file);

#endif