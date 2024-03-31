#include "webLib.hpp"

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	confFile confFile("conf/default.conf");
	confFile.init();
	webServ server;
	server.configServerFile(confFile);
	server.printConfFiles();
}