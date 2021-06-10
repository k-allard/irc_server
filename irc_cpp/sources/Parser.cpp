#include "../includes/Parser.hpp"


Parser::Parser(Server &server) : _server(server)
{
}

Parser::~Parser()
{
}

//для дебага
void Parser::do_parsing(int fd, char *buf, int size)
{
	Cmds cmds(_server);
	std::string com(buf);

	com.erase(com.size() - 2, 2); // убирает каретки
	if(com.compare(0, 4, "NICK") == 0)
	{
		std::cout << "NICK cmd" << std::endl;
		std::string nick = com.substr(5, com.npos);
		if (cmds.NICKCmd(fd, com.substr(5, com.npos)) == -1)
			perror("nick err");
		return ;
	}
	if(com.compare(0, 3, "PMN") == 0) // для дебага. нет такой команды)
	{
		Client *client = cmds.findClient(fd);
		std::string nick = client->getNick();
		if (nick == "")
			std::cout << fd << " fd`s nick is not set\n";
		else
			std::cout << fd << " fd`s nick: " << client->getNick() << std::endl;
		return ;
	}
}
