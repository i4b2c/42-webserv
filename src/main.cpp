#include "webServ.hpp"
#include "confFile.hpp"
#include <cstdlib>

void error(std::string const arg)
{
	std::cerr << "Error: " << arg << std::endl;
	exit(EXIT_FAILURE);
}

int main(int ac, char **av)
{
	if(ac > 2)
		error("Invalid number of arguments.");
	else if(ac == 1)
	{
		confFile conf_file("conf/default.conf");
		std::cout << conf_file << std::endl;
	}
	else
	{
		confFile conf_file(av[1]);
		std::cout << conf_file << std::endl;
	}
	return EXIT_SUCCESS;
	/*
		Primeira coisa que vai fazer eh ler o conf file
	*/
	// webServ server("default.conf");
	// server.addServer();
	// server.starting();
}