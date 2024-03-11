#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <stdio.h>
#include <arpa/inet.h>
#include <sstream>
#include <fstream>
#include <string>

std::string get_header(int length)
{
	std::stringstream ss;
	ss << length;
	std::string temp = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";
	temp += ss.str();
	temp += "\n\n";
	return temp;
}

std::string get_html(std::string html_arq)
{
	std::string conteudo_html;
	std::string linha;
	std::ifstream arquivo;
	std::cout << "a: " << html_arq;
	if(html_arq.length() == 1)
		arquivo.open("filesHtml/default.html");
	else
		arquivo.open(html_arq.substr(1,html_arq.length() - 1).c_str());
	if (arquivo.is_open())
	{
		while (std::getline(arquivo, linha))
			conteudo_html += linha;
		arquivo.close();
	}
	else
	{
		std::cerr << "Erro ao abrir o arquivo HTML: " << html_arq << std::endl;
		conteudo_html = "<!DOCTYPE html><html><body><h1>Error 500!</h1></body></html>";
	}

	return conteudo_html;
}

std::string extract_path_from_request(const std::string& request_line)
{
    std::string path;
    size_t first_space = request_line.find(' ');
    if (first_space != std::string::npos)
	{
        size_t second_space = request_line.find(' ', first_space + 1);
        if (second_space != std::string::npos)
            path = request_line.substr(first_space + 1, second_space - first_space - 1);
    }
    return path;
}

int main(int ac, char **av)
{
	(void)av;
	if(ac > 2)
	{
		std::cout << "Error: invalid arguments" << std::endl;
		return EXIT_FAILURE;
	}
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock == -1)
	{
		perror("Error ao criar o socket");
		return EXIT_FAILURE;
	}
	int reuse = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
	{
		perror("Erro ao definir a opção SO_REUSEADDR");
		return EXIT_FAILURE;
	}
	sockaddr_in server_address = {};
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8080);
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(sock,(struct sockaddr *)&server_address,sizeof(server_address)) < 0)
	{
		perror("Error ao fazer bind do socket");
		return EXIT_FAILURE;
	}
	if(listen(sock,2) < 0)
	{
		perror("Error ao conectar");
		return EXIT_FAILURE;
	}
	int client;
	sockaddr_in client_adderss;
	socklen_t client_size = sizeof(client_adderss);
	ssize_t x;
	char buff[1024] = {0};
	while(1)
	{
		client = accept(sock,(struct sockaddr *)&client_adderss,&client_size);
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
	if(close(sock) == -1)
	{
		perror("Error ao fechar o socket do servidor");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
