#ifndef UTILS_HPP
#define UTILS_HPP

#include "Server.hpp"

std::string get_header(int length);
std::string get_html(std::string html_arq);
std::string extract_path_from_request(const std::string& request_line);

#endif