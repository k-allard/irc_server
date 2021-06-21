#include "../includes/Parser.hpp"

Parser::Parser(Server &server) : _server(server) { }

Parser::~Parser() { }

std::vector<Message> Parser::do_parsing(int fd, char *buf, int size)
{
	std::vector<Message> result;
	Cmds cmds(this->_server);
	std::string com(buf);
	std::istringstream stream(com);
	std::queue<std::string> data;
	std::string tmp;
	while (std::getline(stream, tmp, '\n')) {
		if (tmp.empty())
			continue;
		if (tmp.at(tmp.size() - 1) == '\r')
			tmp.erase(tmp.size() - 1, 1);
		data.push(tmp);
	}
	while(!data.empty()) {
		Message msg = Message(data.front());
		result.push_back(msg);
		data.pop();
	}
	return (result);
}
