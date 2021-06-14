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
	Cmds cmds(this->_server);
	std::string com(buf);
	std::istringstream stream(com);
	std::queue<std::string> data;
	std::string tmp;
	while (std::getline(stream, tmp, '\n')) {
		if(tmp.empty())
			continue;
		tmp.erase(tmp.size() - 1, 1);
		if (tmp.at(tmp.size() - 1) == '\r')
			tmp.erase(tmp.size() - 1, 1);
		//std::cout << "[" << tmp << "]\n";
		data.push(tmp);
	}
	while(!data.empty()) {
		Message msg = Message(data.front());
		if(msg.command->cmdType == MsgCmd__UNKNOWN)
		{
			std::cerr << "Parser: Unknown client #" << fd << " input :" << std::endl;
			std::cerr << "       \"" << data.front() << "\"" << std::endl;
			std::cout << std::endl;
		}
		else
		{
			std::cout << "Parser: OK (DEBUG): " << std::endl;
			std::cout << "        Prefix.Nick: " << msg.prefix->nick << std::endl;
			std::cout << "        Prefix.User: " << msg.prefix->user << std::endl;
			std::cout << "        Prefix.Host: " << msg.prefix->host << std::endl;
			std::cout << "        Command.Type: " << msg.command->cmdType << std::endl;
			std::cout << "        Command.Letters: " << msg.command->letters << std::endl;
			std::cout << "        Command.Numbers: " << msg.command->numbers << std::endl;
			std::cout << "        Command.Params: " << msg.params << std::endl;			
		}
		
		data.pop();
	}


//	Cmds cmds(_server);
//	std::string com(buf);
//
//	com.erase(com.size() - 2, 2); // убирает каретки
//	if(com.compare(0, 4, "NICK") == 0)
//	{
//		std::cout << "NICK cmd" << std::endl;
//		std::string nick = com.substr(5, com.npos);
//		if (cmds.NICKCmd(fd, com.substr(5, com.npos)) == -1)
//			perror("nick err");
//		return ;
//	}
//	if(com.compare(0, 3, "PMN") == 0) // для дебага. нет такой команды)
//	{
//		Client *client = cmds.findClient(fd);
//		std::string nick = client->getNick();
//		if (nick == "")
//			std::cout << fd << " fd`s nick is not set\n";
//		else
//			std::cout << fd << " fd`s nick: " << client->getNick() << std::endl;
//		return ;
//	}
}
