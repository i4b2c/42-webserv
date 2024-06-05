#include "webLib.hpp"

/*
 * Function used to cut the word out of the conf file
 * more easy to read and work on.
 */
void cutWord(std::string & str,std::string const str_to_cut) throw ()
{
	size_t temp_lenght = str.find(str_to_cut);
	if(temp_lenght != std::string::npos)
		str.erase(temp_lenght,str_to_cut.size());
}

bool tryFind(std::string & str,std::string const str_to_find) throw()
{
	size_t init = str.find_first_not_of("\t ");
	size_t try_to_find = str.find(str_to_find);
	if(try_to_find == std::string::npos || try_to_find != init)
		return false;
	return true;
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	std::string temp = "server_name temp temp.com www.temp.com";
	tryFind(temp,"server_name") ? std::cout << "ok\n" : std::cout << "ko\n";
	std::cout << "Frase antes: " << temp << std::endl;
	cutWord(temp,"server_name");
	std::cout << "Frase depois: " << temp << std::endl;
	/*
	confFile confFile("conf/default.conf");
	confFile.init();
	try {
		webServ server;
		server.configServerFile(confFile);
		server.printConfFiles();
	} catch(std::exception & e) {
		std::cout << e.what() << std::endl;
	}
	*/
}
