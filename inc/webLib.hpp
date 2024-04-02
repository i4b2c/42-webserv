#ifndef WEBLIB_HPP
#define WEBLIB_HPP

/*
	c++98 headers
*/
#include <string>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <exception>

/*
	c headers
*/
#include <sys/socket.h>
#include <sys/poll.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

/*
	my own headers
*/
#include "webServ.hpp"
#include "server.hpp"
#include "client.hpp"
#include "confFile.hpp"
#include "confServer.hpp"
#include "utils.hpp"
#include "location.hpp"

#endif //WEBLIB_HPP