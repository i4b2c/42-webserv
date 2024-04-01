#ifndef CONFFILESERVER_HPP
#define CONFFILESERVER_HPP

#include "webLib.hpp"

class Location;

class confServer
{
	private:
		int							_socket_fd;
		int							_port;
		in_addr_t					_host;
		std::string					_server_name;
		std::string					_root;
		std::string					_index;
		bool						_auto_index;
		int							_client_max_body_size;
		std::map<int,std::string>	_error_pages;
		struct sockaddr_in			_server_address;
		std::vector<Location>		_location;
	public:
		/*
			Constructor and Destructor
		*/
		confServer();
		~confServer();

		/*
			Set functions
		*/
		void setPort(int);
		void setServerName(std::string);
		void setHost(uint32_t);
		void setErrorPages(std::vector<std::string>);
		void setClientMaxBodySize(int);
		void setRoot(std::string);
		void setIndex(std::string);
		void setAutoIndex(std::string);
		void setLocation(Location);
		void setSocket();

		/*
			Get funtions
		*/
		int							getPort() const;
		uint32_t					getHost() const;
		std::string					getServerName() const;
		std::map<int,std::string>	getErrorPages() const;
		int							getClientMaxBodySize() const;
		std::string					getRoot() const;
		std::string					getIndex() const;
		bool						getAutoIndex() const;
		std::vector<Location>		getLocation() const;
		int							getSocket() const;
};

/*
	Utils Funcions
*/

std::ostream &operator<<(std::ostream &stream,confServer & arg);

#endif //CONFFILESERVER_HPP