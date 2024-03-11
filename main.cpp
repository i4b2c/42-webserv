#include "Server.hpp"
#include "utils.hpp"
#include "Client.hpp"

int main(int ac, char **av)
{
	(void)av;
	if(ac > 2)
	{
		std::cout << "Error: invalid arguments" << std::endl;
		return EXIT_FAILURE;
	}
	Server server;
	// Client client;
	// falta organizar isso e adicionar uma nova classe chamada 
	// webserver que vai ter um vector server e um vector client
	int client;
	sockaddr_in client_adderss;
	socklen_t client_size = sizeof(client_adderss);
	ssize_t x;
	char buff[1024] = {0};
	while(1)
	{
		client = accept(server.getSock(),(struct sockaddr *)&client_adderss,&client_size);
		x = recv(client,buff,sizeof(buff),0);
		std::string get_temp = extract_path_from_request(buff);
		std::string response = get_html(get_temp);
		if(x == -1)
		{
			std::cout << "Nao ha dados";
			close(client);
			return EXIT_FAILURE;
		}
		std::string header = get_header(response.length());
		send(client,header.c_str(),header.length(),0);
		send(client,response.c_str(),response.length(),0);
		std::cout << buff;
		if(close(client) == -1)
		{
			perror("Error ao fechar o socket do client");
			return EXIT_FAILURE;
		}
	}
	// if(close(sock) == -1)
	// {
	// 	perror("Error ao fechar o socket do servidor");
	// 	return EXIT_FAILURE;
	// }
	return EXIT_SUCCESS;
}
