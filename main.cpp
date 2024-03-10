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

/*
Apenas para estudo:
IP - Internet Protocol
TCP - Transmission Control Protocol
HTTP - Hypertext Transfer Protocol
*/


// Uma funcao simples para copiar o conteudo do arquivo html
std::string get_html(std::string html_arq)
{
	std::ifstream arquivo(html_arq.c_str());
	std::string conteudo_html;
	std::string linha;

	if (arquivo.is_open())
	{
		while (std::getline(arquivo, linha))
			conteudo_html += linha;
		arquivo.close();
	}
	else
	{
		// Se não foi possível abrir o arquivo, exibir uma mensagem de erro
		std::cerr << "Erro ao abrir o arquivo HTML: " << html_arq << std::endl;
		conteudo_html = "<!DOCTYPE html><html><body><h1>Error 500!</h1></body></html>";
	}

	return conteudo_html; // Retornando o conteúdo do arquivo HTML em uma string
}

int main(void)
{
	/*
	Criar um socket, o que eh?
	eh basicamente um ponto de comunicacao e retorna um
	descritor para um arquivo

	Parametros->
	-------
	1) AF_INET diz que vamos usar IPv4
	tambem podemos usar o AF_INET6 para IPv6
	------
	2) SOCK_STREAM diz que vamos utilizar o metodo TCP
	eh o mais usado
	-----
	3) Usamos 0 como ultimo parametro para que o programa
	escolha o protocolo apropriado para o tipo de socket 
	selecionado
	*/
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock == -1)
	{
		perror("Error ao criar o socket");
		return EXIT_FAILURE;
	}
	/*
	Manipular o socket
	Podemos usar para conectar a um servidor
	Aceitar conexoes de clientes ou enviar/receber dados

	setsockopt() - usado para reutilizar o IP , no caso usamos 0.0.0.0
	por conta do INADDR_ANY

	- Flag SO_REUSEADDR para permitir que o endereco seja reutilizado mesmo que
	ainda esteja em uso

	bind() - usado para associar um socket a uma porta e endereco IP local

	listen() - usado para aguardar conexoes

	accept() - usado para aceitar uma conexao de cliente pendente
	*/

	int reuse = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
	{
		perror("Erro ao definir a opção SO_REUSEADDR");
		return EXIT_FAILURE;
	}

	/*
		Criamos uma struct para configurar o
		endereco do servidor ou client
		no caso vamos usar sockaddr_in para representar
		enderecos IP e portas
	*/

	sockaddr_in server_address = {};
	server_address.sin_family = AF_INET; // vamos usar IPv4
	server_address.sin_port = htons(8080); // vamos usar porta 8080, usamos a funcao htons para converter o 8080 para uma porta correta
	server_address.sin_addr.s_addr = htonl(INADDR_ANY); // vai ser usado qualquer IP disponivel na maquina local

	/*
		a funcao bind() vai ser usado para associar um endereco IP , o tipo de IP e a porta a um socket
	*/

	if(bind(sock,(struct sockaddr *)&server_address,sizeof(server_address)) < 0)
	{
		perror("Error ao fazer bind do socket");
		return EXIT_FAILURE;
	}

	/*
		a funcao listen() eh usado para colocar um maximo de conexoes a um socket
		a funcao retorna -1 caso passe o maximo de conexoes
	*/

	if(listen(sock,2) < 0)//numero maximo de conexoes eh 2 neste caso
	{
		perror("Error ao conectar");
		return EXIT_FAILURE;
	}

	// Criamos um sockaddr_in para armazenar os dados do cliente 

	int client;
	sockaddr_in client_adderss;
	socklen_t client_size = sizeof(client_adderss);
	ssize_t x;
	char buff[129] = {0};
	while(1)
	{
		//leitura dos dados
		client = accept(sock,(struct sockaddr *)&client_adderss,&client_size);
		x = recv(client,buff,sizeof(buff),0);
		std::string response = get_html("filesHtml/teste.html");
		if(x == -1)
		{
			std::cout << "Nao ha dados";
			close(client);
			return EXIT_FAILURE;
		}

		// manda dados para o cliente
		/*
			Usamos o stringstream para passar de int para string
			e fazer 
		*/
		std::stringstream ss;
		ss << response.length();
		std::string str = ss.str();

		/*
			Temos que criar um header para dizer para o client o que ele vai receber
			no caso vai ser uma conexao HTTP/1.1 
			200 quer dizer que deu para conectar

			Tipo de texto vai ser html
			e depois o tamanho do texto

			depois de mandar o header mandamos o html para o cliente
		*/

		std::string header = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " + str + "\n\n";
		send(client,header.c_str(),header.length(),0);
		send(client,response.c_str(),response.length(),0);
		// send(client,"<!DOCTYPE html><html><body><h1>Servidor HTTP em C++</h1></body></html>",71,0);
		// send(client,buff,x,0);

		//imprime no terminal os dados que recebeu do cliente
		// Vai ser impreso no servidor para debuff
		std::cout << "Client: " << buff;

		if(close(client) == -1)
		{
			perror("Error ao fechar o socket do client");
			return EXIT_FAILURE;
		}
	}

	/*
	Por fim igual a um open que abre arquivos temos 
	que fechar o socket usando o close() function
	*/
	if(close(sock) == -1)
	{
		perror("Error ao fechar o socket do servidor");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
