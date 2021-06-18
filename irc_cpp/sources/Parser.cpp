#include "../includes/Parser.hpp"


Parser::Parser(Server &server) : _server(server)
{
}

Parser::~Parser()
{
}


std::vector<Message> Parser::do_parsing(int fd, char *buf, int size)
{
	std::vector<Message> result;
	Cmds cmds(this->_server);
	std::string com(buf);
	std::istringstream stream(com);
	std::queue<std::string> data;
	std::string tmp;
	while (std::getline(stream, tmp, '\n')) {
		if(tmp.empty())
			continue;
		if (tmp.at(tmp.size() - 1) == '\r')
			tmp.erase(tmp.size() - 1, 1);
		std::cerr << "[" << tmp << "]" << std::endl;
		data.push(tmp);
	}
	while(!data.empty()) {
		Message msg = Message(data.front());
		result.push_back(msg);

		// for DEBUG
		if(msg.command->cmdType == MsgCmd__UNKNOWN)
		{
			std::cerr << "Parser: Unknown command from client #" << fd << ". Client input :" << std::endl;
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
			std::cout << "        Command.Params: " << msg.params->toString() << std::endl;
			int i = 1;
            for (std::vector<std::string>::const_iterator strIt = msg.params->Params.begin(); strIt != msg.params->Params.end(); ++strIt, ++i)
            {
                std::cout << "        Command.Params [#" << i << "]: " << *strIt << std::endl;
            }
		}

		data.pop();
	}
	return (result);
}
