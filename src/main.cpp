#include "webLib.hpp"

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	confFile confFile("conf/default.conf");
	confFile.init();
	try {
		webServ server;
		server.configServerFile(confFile);
		server.printConfFiles();
	} catch(std::exception & e) {
		std::cout << e.what() << std::endl;
	}
}