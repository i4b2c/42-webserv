#ifndef CONFFILEPARAMS_HPP
#define CONFFILEPARAMS_HPP

#include "webLib.hpp"

class confFileParam
{
	private:
		int _port;
		std::string _server_name;
		struct sockaddr_in _server_address;
	public:
		confFileParam();
		~confFileParam();
		void setPort(int);
		void setServerName(std::string);
		void setHost(uint32_t);
		int getPort() const;
		uint32_t getHost() const;
		std::string getServerName() const;
};

std::ostream &operator<<(std::ostream &stream,confFileParam & arg);

#endif //CONFFILEPARAMS_HPP