#include "webServ.hpp"
#include "utils.hpp"
#include <csignal>
#include <cstdlib>
#include <sys/poll.h>

#define DOMAIN_DEFAULT AF_INET
#define TYPE_DEFAULT SOCK_STREAM
#define PROTOCOL_DEFAULT 0

bool g_closeServer = false;

static void closeServer(int signum)
{
	(void)signum;
	std::cout << "\n";
	g_closeServer = true;
	exit(EXIT_SUCCESS);
}

webServ::webServ()
: server()
{
	signal(SIGPIPE,SIG_IGN);
	signal(SIGINT, closeServer);
	printAtTerminal("Starting Server...");
}

webServ::~webServ()
{
	printAtTerminal("Closing Server...");
}

void webServ::addServer()
{
	static int idx = 0;
	Server serverTemp(AF_INET,8085,INADDR_ANY,SOCK_STREAM,0);
	this->server.push_back(serverTemp);
	this->id = idx;
	idx++;
}

void webServ::addServer(int domain, int port, u_long interface, int service, int protocol)
{
	Server serverTemp(domain,port,interface,service,protocol);
	this->server.push_back(serverTemp);
}

void webServ::addClient(int idx)
{
	Client clientTemp(idx);
	this->client.push_back(clientTemp);
}

void webServ::starting(void)
{
	struct pollfd pfd;
	pfd.fd = this->server.at(this->id).getSocket();
	pfd.events = POLLIN;

	int idx = 0;
	while (!g_closeServer)
	{
		int poll_ret = poll(&pfd, 1, -1);
		if (poll_ret < 0)
		{
			return;
		}
		else if (poll_ret == 0)
		{
			continue;
		}
		else if (pfd.revents & POLLIN)
		{
			std::cout << "nova conexao " << idx << std::endl;
			this->addClient(idx);
			this->client.at(this->client.size() - 1).connect(this->server.at(this->id).getSocket());
			idx++;
		}
		else
		{
		}
	}
}