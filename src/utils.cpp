#include "utils.hpp"

void printAtTerminal(std::string const arg)
{
	std::cout << arg << std::endl;
}

void cleanSpaces(std::string &arg)
{
	std::string result;
	for (size_t i = 0; i < arg.length(); ++i)
	{
		if (arg[i] != ' ' && arg[i] != '\t' && arg[i] != ';')
		{
			result += arg[i];
		}
	}
	arg = result;
}