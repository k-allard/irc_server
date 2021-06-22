#pragma once

#include "header.hpp"
#include "Cmds.hpp"

class Parser
{
private:
	Server&					_server;
	Parser();
public:
	Parser(Server &server);
	~Parser();

	std::vector<Message>	do_parsing(char *buf);
};
