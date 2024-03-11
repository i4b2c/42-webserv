#include "utils.hpp"

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