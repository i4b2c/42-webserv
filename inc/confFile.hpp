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
		std::string _server_name;
	public:
		void init(std::string const arg);

		int getPort() const;
		std::string getServerName() const;
		
		confFile(std::string const arg);
		~confFile();
};

std::ostream &operator<<(std::ostream & stream, confFile & file);

#endif