#include "webServ.hpp"

int main(void)
{
	webServ server("default.conf");
	server.addServer();
	server.starting();
}