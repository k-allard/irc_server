//
// Created by Anastasia on 14.06.2021.
//

#include "../includes/MessageCommand.hpp"

MessageCommand::MessageCommand(int numbers)
{
	this->numbers = numbers;
	this->cmdType = MsgCmd__NUMBER;
	this->letters = "";
}

MessageCommand::MessageCommand(std::string string)
{
	this->letters = string;
	this->cmdType = this->str2enum(this->letters);
	this->numbers = 0;
}
MessageCommand::MessageCommand(char *string)
{
	this->letters = std::string (string);
	this->cmdType = this->str2enum(this->letters);
	this->numbers = 0;
}

MessageCommand::MessageCommand(std::string::const_iterator &it, const std::string::const_iterator &end)
{
	this->letters = this->getLetters(it, end);
	if(it < end && *it != ' ')
		this->cmdType = MsgCmd__UNKNOWN;
	else
		this->cmdType = this->str2enum(this->letters);
	this->numbers = 0;
}


MessageCommand::~MessageCommand()
{

}

/**
 * @b Format:
 *
 * @code
 * command  ::= letter { letter } | number number number
 * letter   ::= 'a' ... 'z' | 'A' ... 'Z'
 * number   ::= '0' ... '9'
 * @param it
 * @param end
 * @return
 */
std::string MessageCommand::getLetters(std::string::const_iterator &it, const std::string::const_iterator &end)
{
	std::string str = "";
	if (it < end)
	{
		if(*it >= '0' && *it <= '9') {
			int digitLenght = 0;
			while (digitLenght < 3 && it < end && *it >= '0' && *it <= '9')
			{
				str += *it;
				digitLenght++;
				it++;
			}
		} else {
			while (it < end && ((*it >= 'a' && *it <= 'z')||(*it >= 'A' && *it <= 'Z')))
			{
				str += *it;
				it++;
			}
		}
	}
	return str;
}

std::string str_toupper(std::string s) {
	std::string str("");
	for (std::string::const_iterator i = s.cbegin(); i != s.cend(); ++i)
	{
		unsigned char c = *i;
		str += std::toupper(c);
	}


	return (str);
}

MessageCommandEnum MessageCommand::str2enum(std::string &str)
{
	MessageCommandEnum msgEnum;
	std::string string = str_toupper(str);

	if(string == "PASS")
		msgEnum = MsgCmd_PASS;
	else if(string == "NICK")
		msgEnum = MsgCmd_NICK;
	else if(string == "USER")
		msgEnum = MsgCmd_USER;
	else if(string == "SERVER")
		msgEnum = MsgCmd_SERVER;
	else if(string == "OPER")
		msgEnum = MsgCmd_OPER;
	else if(string == "QUIT")
		msgEnum = MsgCmd_QUIT;
	else if(string == "SQUIT")
		msgEnum = MsgCmd_SQUIT;
	else if(string == "JOIN")
		msgEnum = MsgCmd_JOIN;
	else if(string == "MSG")
		msgEnum = MsgCmd_MSG;
	else if(string == "PRIVMSG")
		msgEnum = MsgCmd_PRIVMSG;
	else if(string == "LIST")
		msgEnum = MsgCmd_LIST;
	else if(string == "USERS")
		msgEnum = MsgCmd_USERS;
	else if(string == "MOTD")
		msgEnum = MsgCmd_MOTD;
	else if(string == "LUSER")
		msgEnum = MsgCmd_LUSER;
	else if(string == "PART")
		msgEnum = MsgCmd_PART;
	else if(string == "PING")
		msgEnum = MsgCmd_PING;
	else if(string == "PONG")
		msgEnum = MsgCmd_PONG;
	else
		msgEnum = MsgCmd__UNKNOWN;
	return  msgEnum;
}
