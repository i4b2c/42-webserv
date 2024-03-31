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

std::string binaryToIp(uint32_t binary_num)
{
    std::string ip_address;
    std::stringstream ss;
    for (int i = 3; i >= 0; --i)
	{
        uint32_t octet = (binary_num >> (8 * (3 - i))) & 255;
        ss << octet;
        if (i > 0) ss << ".";
    }
    ip_address = ss.str();
    return ip_address;
}

std::vector<std::string> splitString(const std::string& input, char delimiter) {
    std::vector<std::string> tokens;
    size_t startPos = 0;
    
    // Enquanto houver delimitadores na string
    while (startPos != std::string::npos) {
        // Encontrar a posição do próximo delimitador a partir da posição inicial
        size_t endPos = input.find(delimiter, startPos);

        // Se não encontrarmos outro delimitador, pegamos o restante da string
        if (endPos == std::string::npos) {
            endPos = input.size();
        }
        
        // Adicionamos a substring delimitada ao vetor de tokens
        tokens.push_back(input.substr(startPos, endPos - startPos));
        
        // Atualizamos a posição inicial para o próximo caractere após o delimitador
        startPos = input.find_first_not_of(delimiter, endPos);

        // Se não houver mais caracteres após o último delimitador, saímos do loop
        if (startPos == std::string::npos) {
            break;
        }
    }

    return tokens;
}