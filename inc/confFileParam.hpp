#ifndef CONFFILEPARAMS_HPP
#define CONFFILEPARAMS_HPP

#include "webLib.hpp"

class confFileParam
{
	private:
		int _port;
		int _client_max_body_size;
		std::string _server_name;
		std::map<int,std::string> _error_pages;
		struct sockaddr_in _server_address;
	public:
		confFileParam();
		~confFileParam();

		void setPort(int);
		void setServerName(std::string);
		void setHost(uint32_t);
		void setErrorPages(std::vector<std::string>);
		void setClientMaxBodySize(int);

		int getPort() const;
		uint32_t getHost() const;
		std::string getServerName() const;
		std::map<int,std::string> getErrorPages() const;
		int getClientMaxBodySize() const;
};

std::ostream &operator<<(std::ostream &stream,confFileParam & arg);

#endif //CONFFILEPARAMS_HPP