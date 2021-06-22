#include "../includes/MessageCommand.hpp"

MessageCommand::MessageCommand(std::string::iterator &it, const std::string::iterator &end)
{
	this->numbers = -1;
	this->letters = this->getLettersOrSetNumbers(it, end);
	if (it < end && *it != ' ')
		this->cmdType = MsgCmd__UNKNOWN;
	else
	    if (this->cmdType != MsgCmd__NUMBER)
		    this->cmdType = this->str2enum(this->letters);
}

MessageCommand::~MessageCommand() { }

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
std::string MessageCommand::getLettersOrSetNumbers(std::string::iterator &it, const std::string::iterator &end)
{
    this->cmdType = MsgCmd__UNKNOWN;
	std::string str = "";
	if (it < end)
	{
		if (*it >= '0' && *it <= '9') {
		    this->numbers = 0;
			int digitLenght = 0;
			while (digitLenght < 3 && it < end && *it >= '0' && *it <= '9')
			{
				this->numbers = 10 * this->numbers + (*it - '0');
				str += *it;
				digitLenght++;
				it++;
			}
			if (digitLenght < 3)
                this->numbers = -1;
			else
                this->cmdType = MsgCmd__NUMBER;
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
	for (std::string::iterator i = s.begin(); i != s.end(); ++i)
	{
		unsigned char c = *i;
		str += std::toupper(c);
	}
	return (str);
}

MessageCommandEnum MessageCommand::str2enum(std::string &str)
{
	MessageCommandEnum		msgEnum;
	std::string string =	str_toupper(str);

	// Connection/Registration
	if (string == "PASS")			msgEnum = MsgCmd_PASS;
	else if (string == "NICK")		msgEnum = MsgCmd_NICK;
	else if (string == "USER")		msgEnum = MsgCmd_USER;
	else if (string == "SERVER")	msgEnum = MsgCmd_SERVER;
	else if (string == "OPER")		msgEnum = MsgCmd_OPER;
	else if (string == "QUIT")		msgEnum = MsgCmd_QUIT;
	else if (string == "SQUIT")		msgEnum = MsgCmd_SQUIT;

	// Channel Operations
	else if (string == "JOIN")		msgEnum = MsgCmd_JOIN;
    else if (string == "PART")		msgEnum = MsgCmd_PART;
    else if (string == "MODE")		msgEnum = MsgCmd_MODE;
    else if (string == "MODE")		msgEnum = MsgCmd_MODE;
    else if (string == "TOPIC")		msgEnum = MsgCmd_TOPIC;
    else if (string == "NAMES")		msgEnum = MsgCmd_NAMES;
    else if (string == "LIST")		msgEnum = MsgCmd_LIST;
    else if (string == "INVITE")	msgEnum = MsgCmd_INVITE;
    else if (string == "KICK")		msgEnum = MsgCmd_KICK;

    // Server queries and commands
    else if (string == "VERSION")	msgEnum = MsgCmd_VERSION;
    else if (string == "STATS")		msgEnum = MsgCmd_STATS;
    else if (string == "LINKS")		msgEnum = MsgCmd_LINKS;
    else if (string == "TIME")		msgEnum = MsgCmd_TIME;
    else if (string == "CONNECT")	msgEnum = MsgCmd_CONNECT;
    else if (string == "TRACE")		msgEnum = MsgCmd_TRACE;
    else if (string == "ADMIN")		msgEnum = MsgCmd_ADMIN;
    else if (string == "INFO")		msgEnum = MsgCmd_INFO;

    // Sending messages
    else if (string == "PRIVMSG")	msgEnum = MsgCmd_PRIVMSG;
    else if (string == "NOTICE")	msgEnum = MsgCmd_NOTICE;

    // User based queries
    else if (string == "WHO")		msgEnum = MsgCmd_WHO;
    else if (string == "WHOIS")		msgEnum = MsgCmd_WHOIS;
    else if (string == "WHOWAS")	msgEnum = MsgCmd_WHOWAS;

    // Miscellaneous messages
    else if (string == "KILL")		msgEnum = MsgCmd_KILL;
    else if (string == "PING")		msgEnum = MsgCmd_PING;
    else if (string == "PONG")		msgEnum = MsgCmd_PONG;
    else if (string == "ERROR")		msgEnum = MsgCmd_ERROR;

    // OPTIONALS
    else if (string == "AWAY")		msgEnum = MsgCmd_AWAY;
    else if (string == "REHASH")	msgEnum = MsgCmd_REHASH;
    else if (string == "RESTART")	msgEnum = MsgCmd_RESTART;
    else if (string == "SUMMON")	msgEnum = MsgCmd_SUMMON;
    else if (string == "USERS")		msgEnum = MsgCmd_USERS;
    else if (string == "WALLOPS")	msgEnum = MsgCmd_WALLOPS;
    else if (string == "USERHOST")	msgEnum = MsgCmd_USERHOST;
    else if (string == "ISON")		msgEnum = MsgCmd_ISON;

    // OTHER
    else if (string == "MSG")		msgEnum = MsgCmd_MSG;
    else if (string == "MOTD")		msgEnum = MsgCmd_MOTD;
    else if (string == "LUSERS")	msgEnum = MsgCmd_LUSERS;
    else if (string == "")			msgEnum = MsgCmd__EMPTY;
    else
        msgEnum = MsgCmd__UNKNOWN;
    return  msgEnum;
}
