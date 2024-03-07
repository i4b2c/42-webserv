#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <stdio.h>
#include <arpa/inet.h>

/*
Apenas para estudo:
IP - Internet Protocol
TCP - Transmission Control Protocol
HTTP - Hypertext Transfer Protocol
*/

/*
Criamos uma struct para configurar o
endereco do servidor ou client
no caso vamos usar sockaddr_in para representar
enderecos IP e portas
*/

struct sockaddr_in client_adderss;
// struct sockaddr_in server_address = {
// 	server_address.sin_family = AF_INET, // vamos usar IPv4
// 	server_address.sin_port = htons(8080), // vamos usar porta 8080, usamos a funcao
// 	// htons para converter o 8080 para uma porta correta
// 	server_address.sin_addr.s_addr = htonl(INADDR_ANY) // vai ser usado qualquer
// 	// IP disponivel na maquina local
// };

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
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
		perror("Erro ao definir a opção SO_REUSEADDR");
		return EXIT_FAILURE;
	}

	sockaddr_in server_address = {};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080); // Exemplo de porta
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(sock,(struct sockaddr *)&server_address,sizeof(server_address)) < 0)
	{
		perror("Error ao fazer bind do socket");
		return EXIT_FAILURE;
	}
	if(listen(sock,2) < 0)//numero maximo de conexoes eh 2 neste caso
	{
		perror("Error ao conectar");
		return EXIT_FAILURE;
	}
	int client;
	socklen_t client_size = sizeof(client_adderss);
	ssize_t x;
	char buff[129] = {0};
	while(1)
	{
		//leitura dos dados
		client = accept(sock,(struct sockaddr *)&client_adderss,&client_size);
		x = recv(client,buff,sizeof(buff),0);
		if(x == -1)
		{
			std::cout << "Nao ha dados";
			close(client);
			return EXIT_FAILURE;
		}

		// manda dados para o cliente
		send(client,"Server: ",9,0);
		send(client,buff,x,0);

		//imprime no terminal os dados que recebeu do cliente
		std::cout << "Client: " <<buff;
		close(client);
	}

	// socklen_t client_address_length = sizeof(client_adderss);
	// int client_socket = accept(sock,(struct sockaddr *)&client_adderss,&client_address_length);
	// if(client_socket < 0)
	// {
	// 	perror("Error ao aceitar conexao");
	// 	return EXIT_FAILURE;
	// }
	// char buffer[1024] = {0};
	// int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
	// if (bytes_received < 0) {
	// 	perror("Erro ao receber dados do cliente");
	// 	return EXIT_FAILURE;
	// }
	// std::cout << "Mensagem recebida do cliente: " << buffer << std::endl;

	// const char *mensagem = "Olá do servidor!\n";
	// int bytes_enviados = send(client_socket, mensagem, strlen(mensagem), 0);
	// if (bytes_enviados < 0) {
	// 	perror("Erro ao enviar dados para o cliente");
	// 	return EXIT_FAILURE;
	// }


	/*
	Por fim igual a um open que abre arquivos temos 
	que fechar o socket usando o close() function
	*/
	if(close(sock) == -1)
	{
		perror("Error ao fechar o socket");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
