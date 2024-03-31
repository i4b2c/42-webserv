#ifndef CONFFILEPARAMS_HPP
#define CONFFILEPARAMS_HPP

#include "webLib.hpp"

class confFileParam
{
	private:
		int _port;
		std::string _server_name;
	public:
		confFileParam();
		~confFileParam();
		void setPort(int);
		void setServerName(std::string);
		int getPort() const;
		std::string getServerName() const;
};

std::ostream &operator<<(std::ostream &stream,confFileParam & arg);

#endif //CONFFILEPARAMS_HPP