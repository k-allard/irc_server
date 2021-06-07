#pragma once
#include "header.hpp"
#include "Cmds.hpp"


class Parser
{
private:
	Server &_server;
public:
	Parser(Server &server);
	~Parser();
	void do_parsing(int fd, char *buf, int size);
};
