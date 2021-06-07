#pragma once
#include "header.hpp"

std::string G_CMDS[12] = {"NICK", "PASS", "JOIN", "QUIT", "PART", "MOTD", "PRIVMSG", "MODE", "KICK", "LUSER", "USER", "USERS" };

class Parser
{
private:
	/* data */
public:
	Parser(/* args */);
	~Parser();
};
