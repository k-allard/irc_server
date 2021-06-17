#include "../includes/Cmds.hpp"


Cmds::Cmds(Server &server): _server(server)
{
	_clients = &_server._clients;
}

Cmds::~Cmds()
{
}

Client *Cmds::findClient(int fd)
{
	std::map<int, Client*>::iterator it;
	it = _clients->find(fd);
	if (it == _clients->end())
		return NULL;
	return it->second;
}

void            Cmds::regClient(int fd)
{
    Client *client = findClient(fd);

    client->registr();
    setReply(fd, RPL_WELCOME, RPL_WELCOME_MSG, "");
    setReply(fd, RPL_YOURHOST, RPL_YOURHOST_MSG, "");
    setReply(fd, RPL_CREATED, RPL_CREATED_MSG, "");
    setReply(fd, RPL_MYINFO, RPL_MYINFO_MSG, "");
}

int		Cmds::writeToBuf(int fd, std::string mess)
{
	Client *client = findClient(fd);
	if (client == NULL)
	{
		perror("client not found");
		return -1;
	}
	mess += "\r\n";
	client->_buf.push(mess);
	return 1;
}

// Формат ответа:
// Префикс с названием хоста + код ошибки в формате трехзначного числа + ник получателя (если нет то *) + аргументы полученой команды (если есть) + сообщение по коду
// Пример: ":irc.example.com 001 borja :Welcome to the Internet Relay Network borja!borja@polaris.cs.uchicago.edu"

int		Cmds::setReply(int fd, int code, std::string mess, std::string args)
{
	std::string res;
	Client *client = findClient(fd);
	if (client == NULL)
	{
		perror("client not found");
		return -1;
	}
	res += ":ircserv.net " + std::to_string(code); // С++11
	if(!client->getNick().empty())
		res += " " + client->getNick();
	else
		res += " *";
	if(!args.empty())
		res += " " + args;
	res += " " + mess;
	writeToBuf(fd, res);
	return 0;
}

int		Cmds::checkNick(std::string nick)
{
	if(nick.size() > 9)
		return 0;
    for(int i = 0; i < nick.size(); i++)
    {
        if(nick[i] < 33 || nick[i] > 126)
            return 0;
    }
	return 1;
}

Client *Cmds::findClientNick(const std::string& nick)
{
	std::map<int,Client*>::iterator en = _clients->end();
	for (std::map<int,Client*>::iterator beg = _clients->begin(); beg != en; ++beg)
	{
		if (beg->second->getNick() == nick)
			return (beg->second);
	}
	return NULL;
}

int		Cmds::NICKCmd(int fd, std::string args)
{
	Client *client = findClient(fd);
	if (client == NULL)
	{
		perror("client not found");
		return -1;
	}
	if(!client->isPass())
		return setReply(fd, ERR_NOTREGISTERED, ERR_NOTREGISTERED_MSG, "");
	if(args.empty())
		return setReply(fd, ERR_NONICKNAMEGIVEN, ERR_NONICKNAMEGIVEN_MSG, "");
	if(checkNick(args) == 0)
		return setReply(fd, ERR_ERRONEUSNICKNAME, ERR_ERRONEUSNICKNAME_MSG, args);
	if(findClientNick(args) != NULL)
        return setReply(fd, ERR_NICKNAMEINUSE, ERR_NICKNAMEINUSE_MSG, args);
	else {
        client->setNick(args);
        if (!client->getUserdata()->empty())
            regClient(fd);
    }
	return 0;
}

int		Cmds::PASSCmd(int fd, Message msg)
{
	Client *client = findClient(fd);
	if(client->isPass())
		return setReply(fd, ERR_ALREADYREGISTRED, ERR_ALREADYREGISTRED_MSG, "");
	if(msg.params->Params.empty())
		return setReply(fd, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG, "PASS");
	if(msg.params->Params[0] == _server.getPass())
	    client->setPass();
	return 0;
}

int		Cmds::USERCmd(int fd, std::string args)
{
	Client *client = findClient(fd);
	if (client == NULL)
	{
		perror("client not found");
		return -1;
	}
	if(!client->isPass())
		return setReply(fd, ERR_NOTREGISTERED, ERR_NOTREGISTERED_MSG, "");
	if(client->isReg())
		return setReply(fd, ERR_ALREADYREGISTRED, ERR_ALREADYREGISTRED_MSG, "");
	if(args.empty())
		return setReply(fd, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG, "USER");

	// TODO Вывести в отдельную функцию
	std::istringstream stream(args);
	std::vector<std::string> data;
	std::string tmp;
	while (std::getline(stream, tmp, ' ')) {
		if(tmp.empty())
			continue;
		data.push_back(tmp);
		if (data.size() == 4)
			break ;
	}
	if (data.size() < 4)
		return setReply(fd, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG, "USER");

	client->setUserdata(data);
	if(!client->getNick().empty())
        regClient(fd);
	return 0;
}

// JOIN #here, #there 123
int		Cmds::JOINCmd(int fd, std::string args)
{
	return 0;
}

int		Cmds::QUITCmd(int fd, std::string args)
{
    writeToBuf(fd, "ERROR Closing Link");
    _server.disconnectClient(fd);
    // TODO отправить команнду QUIT всем каналам в которых был этот юзер с аргументом (если не дан то ник)
	return 0;
}

//PART #here, :#there zzz
int		Cmds::PARTCmd(int fd, std::string args)
{
	return 0;
}

int		Cmds::MOTDCmd(int fd, std::string args)
{
	return 0;
}

int		Cmds::PRIVMSGCmd(int fd, Message msg)
{
    if(msg.params->Params.empty())
        return setReply(fd, ERR_NORECIPIENT, ERR_NORECIPIENT_MSG, "");
    if(msg.params->Params.size() == 1)
        return setReply(fd, ERR_NOTEXTTOSEND, ERR_NOTEXTTOSEND_MSG, "");
    Client *client = findClient(fd);
    std::vector<std::string>::iterator it = msg.params->Params.begin();
    Client *recip =findClientNick(*it);
    //TODO добавить поиск по каналам
    if(recip == NULL)
        return setReply(fd, ERR_NOSUCHNICK, ERR_NOSUCHNICK_MSG, "");
    //TODO отправлять только один аргумент сообщения
    writeToBuf(recip->getFd(), client->getPrefix() + " PRIVMSG " + recip->getNick() + " :" + msg.params->Params[1]);
	return 0;
}

int		Cmds::MODECmd(int fd, std::string args)
{
	return 0;
}

int		Cmds::KICKCmd(int fd, std::string args)
{
	return 0;
}

int		Cmds::LUSERCmd(int fd, std::string args)
{
	return 0;
}

int		Cmds::USERSCmd(int fd, std::string args)
{
	return 0;
}

int		Cmds::PONGCmd(int fd, std::string args)
{
    writeToBuf(fd, "PONG " + args);
    return 0;
}
