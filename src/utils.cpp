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

void error(std::string const arg)
{
	std::cerr << "Error: " << arg << std::endl;
	exit(EXIT_FAILURE);
}

void addBinaryNum(uint32_t &binary_num, int num_to_add)
{
	int num_temp = 0;
	for (int i = 0; i < 8; ++i)
	{
		num_temp <<= 1;
		if (num_to_add & 1)
			num_temp |= 1;
		num_to_add >>= 1;
	}
	for(int i = 0; i < 8; ++i)
	{
		binary_num <<= 1;
		if (num_temp & 1)
			binary_num |= 1;
		num_temp >>= 1;
	}
}

uint32_t ipToBinary(std::string const ip_address)
{
	size_t pos = 0;
	size_t old_pos = 0;
	uint32_t binary_num = 0;
	while (pos != std::string::npos)
	{
		pos = ip_address.find(".", old_pos);
		if (pos != std::string::npos)
		{
			addBinaryNum(binary_num,atoi(ip_address.substr(old_pos, pos - old_pos).c_str()));
			old_pos = pos + 1;
		}
		else
			addBinaryNum(binary_num,atoi(ip_address.substr(old_pos, pos - old_pos).c_str()));
	}
	return binary_num;
}