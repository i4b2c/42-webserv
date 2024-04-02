#ifndef UTILS_HPP
#define UTILS_HPP

#include "webLib.hpp"

void printAtTerminal(std::string const arg);
void cleanSpaces(std::string &arg);
void error(std::string const arg);
uint32_t ipToBinary(std::string const ip_address);
void addBinaryNum(uint32_t &binary_num, int num_to_add);
std::string binaryToIp(uint32_t binary_num);
std::vector<std::string> splitString(const std::string& input, char delimiter);
bool checkOnlySpaces(std::string);
bool checkToken(std::string const);

#endif