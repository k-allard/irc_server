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
    setReply(fd, RPL_WELCOME, RPL_WELCOME_MSG, "", "");
    setReply(fd, RPL_YOURHOST, RPL_YOURHOST_MSG, "", "");
    setReply(fd, RPL_CREATED, RPL_CREATED_MSG, "", "");
    setReply(fd, RPL_MYINFO, RPL_MYINFO_MSG, "", "");
}

int		Cmds::writeToBuf(int fd, std::string mess)
{
	Client *client = findClient(fd);
	mess += "\r\n";
	client->_buf.push(mess);
	return 1;
}

// Формат ответа:
// Префикс с названием хоста + код ошибки в формате трехзначного числа + ник получателя (если нет то *) + аргументы полученой команды (если есть) + сообщение по коду
// Пример: ":irc.example.com 001 borja :Welcome to the Internet Relay Network borja!borja@polaris.cs.uchicago.edu"

//int		Cmds::setReply(int fd, int code, std::string mess, std::string args)
//{
//	std::string res;
//	Client *client = findClient(fd);
//	if (client == NULL)
//	{
//		perror("client not found");
//		return -1;
//	}
//    std::ostringstream ss;
//    ss << code;
//    res += ":ircserv.net " + ss.str(); // С++98
//	if(!client->getNick().empty())
//		res += " " + client->getNick();
//	else
//		res += " *";
//	if(!args.empty())
//		res += " " + args;
//	res += " " + mess;
//	writeToBuf(fd, res);
//	return 0;
//}

int		Cmds::setReply(int fd, int code, std::string mess, std::string arg1, std::string arg2)
{
	std::string res;
	Client *client = findClient(fd);
	if (client == NULL)
	{
		perror("client not found");
		return -1;
	}
	std::ostringstream ss;
	ss << code;
	res += ":ircserv.net " + ss.str(); // С++98
	if(!client->getNick().empty())
		res += " " + client->getNick();
	else
		res += " *";

	std::cout << "Initial mess: [" << mess << "]" << std::endl;
	if(!arg1.empty()) {
		std::string::iterator begin_insertion;
		std::string::iterator end_insertion;
		for ( std::string::iterator it=mess.begin(); it!=mess.end(); ++it) {
			if (*it == '<')
				begin_insertion = it;
			if (*it == '>') {
				end_insertion = it;
				end_insertion++;
				break ;
			}
		}
		mess.replace(begin_insertion, end_insertion, arg1);
	}
	std::cout << "After 1st replace: [" << mess << "]" << std::endl;

	if(!arg2.empty()) {
		std::string::iterator begin_insertion;
		std::string::iterator end_insertion;
		for ( std::string::iterator it=mess.begin(); it!=mess.end(); ++it) {
			if (*it == '<')
				begin_insertion = it;
			if (*it == '>') {
				end_insertion = it;
				end_insertion++;
				break ;
			}
		}
		mess.replace(begin_insertion, end_insertion, arg2);
	}
	std::cout << "After 2nd replace: [" << mess << "]" << std::endl;


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

int		Cmds::NICKCmd(int fd, const Message& msg)
{
	Client *client = findClient(fd);
	if(!client->isPass())
		return setReply(fd, ERR_NOTREGISTERED, ERR_NOTREGISTERED_MSG, "", "");
	if(msg.params->Params.empty())
		return setReply(fd, ERR_NONICKNAMEGIVEN, ERR_NONICKNAMEGIVEN_MSG, "", "");
	if(checkNick(msg.params->Params[0]) == 0)
		return setReply(fd, ERR_ERRONEUSNICKNAME, ERR_ERRONEUSNICKNAME_MSG, msg.params->Params[0], "");
	if(findClientNick(msg.params->Params[0]) != NULL)
        return setReply(fd, ERR_NICKNAMEINUSE, ERR_NICKNAMEINUSE_MSG, msg.params->Params[0], "");
	else {
        client->setNick(msg.params->Params[0]);
        if (!client->getUserdata()->empty() && !client->isReg())
            regClient(fd);
    }
	return 0;
}

int		Cmds::PASSCmd(int fd, const Message& msg)
{
	Client *client = findClient(fd);
	if(client->isPass())
		return setReply(fd, ERR_ALREADYREGISTRED, ERR_ALREADYREGISTRED_MSG, "", "");
	if(msg.params->Params.empty())
		return setReply(fd, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG, "PASS", "");
	if(msg.params->Params[0] == _server.getPass())
	    client->setPass();
	return 0;
}

int		Cmds::USERCmd(int fd, const Message& msg)
{
	Client *client = findClient(fd);
	if (client == NULL)
	{
		perror("client not found");
		return -1;
	}
	if(!client->isPass())
		return setReply(fd, ERR_NOTREGISTERED, ERR_NOTREGISTERED_MSG, "", "");
	if(client->isReg())
		return setReply(fd, ERR_ALREADYREGISTRED, ERR_ALREADYREGISTRED_MSG, "", "");
	if(msg.params->Params.empty() || msg.params->Params.size() < 4)
		return setReply(fd, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG, "USER", "");
	client->setUserdata(msg.params->Params);
	if(!client->getNick().empty())
        regClient(fd);
	return 0;
}

// JOIN #here, #there 123
int		Cmds::JOINCmd(int fd, const Message& msg)
{

	if(msg.params->Params.empty())
		return setReply(fd, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG, "", "");
	std::string channelName = msg.params->Params[0];

	Client *client = findClient(fd);

	if (_server._channels.find(channelName) != _server._channels.end()) { // 	такой канал у нас есть
		// добвить в учатников канала, если он еще не там
		std::set<int>::iterator it;
		it = _server._channels[channelName]->getParticipantsFds()->find(fd);
		if (it != _server._channels[channelName]->getParticipantsFds()->end()) {
			std::cout << "D E B U G: не добавить в учаcтников канала, он уже там" << std::endl;
			return setReply(fd, ERR_USERONCHANNEL, ERR_USERONCHANNEL_MSG, client->getNick(), channelName);
		}
		std::cout << "D E B U G: добавить в учаcтников канала, он еще не там" << std::endl;
		_server._channels[channelName]->addParticipant(fd);
		// всем в этом канале (кроме его самого) разослать :<client prefix> JOIN <channel name>
		for (std::set<int>::iterator it=_server._channels[channelName]->getParticipantsFds()->begin(); it!=_server._channels[channelName]->getParticipantsFds()->end(); ++it) {
			if (*it != fd)
				writeToBuf(*it, ":" + client->getPrefix() + " JOIN " + channelName);
			else
				writeToBuf(fd, "JOIN " + msg.params->Params[0]);
		}

		// отправили ему топик канала
		if (!_server._channels[channelName]->getTopic().empty())
			setReply(fd, RPL_TOPIC, RPL_TOPIC_MSG, channelName, _server._channels[channelName]->getTopic());

		// отправили ему список участников каналов + конечное сообщение
		setReply(fd, RPL_NAMREPLY, RPL_NAMREPLY_MSG, channelName, _server._channels[channelName]->getParticipantsNames());
		setReply(fd, RPL_ENDOFNAMES, RPL_ENDOFNAMES_MSG, "", "");
	}

	else { //такого канала нет надо создать и его туда добавить
		std::cout << "D E B U G: создать канал и добвить в учаcтников создателя" << std::endl;
		if (!isChannelNameCorrect(channelName)) {
			std::cout << "D E B U G: некорректное имя канала, выходим из джойна" << std::endl;
			return -1;
		}
		std::cout << "D E B U G: корректное имя канала, создаем" << std::endl;

		Channel *newChannel = new Channel(fd, _server);

		std::pair<std::map<std::string, Channel*>::iterator,bool> ret;
		ret = _server._channels.insert( std::pair<std::string, Channel*>(channelName,newChannel) );
		if (ret.second == false) { 	//channel not inserted
			return setReply(fd, ERR_BADCHANNELKEY, ERR_BADCHANNELKEY_MSG, channelName, "");
		}

	}


	return 0;
}

int Cmds::isChannelNameCorrect(std::string name) {
	if ((name.at(0) != '#') || (name.find(' ') != std::string::npos) || (name.length() > 50)) {
		std::cout << "D E B U G: неправильно!" << std::endl;
		return 0;
	}
	for (int i = 1; i < name.length(); i++) {
		char ch = name.at(i);
		if (ch < 48 || (ch > 57 && ch < 65) || (ch > 90 && ch < 97) || ch > 122) {
			std::cout << "D E B U G: символ [" << ch << "] неправильный" << std::endl;
			return 0;
		}
	}
	return 1;
}

int		Cmds::QUITCmd(int fd, const std::string& msg)
{
    writeToBuf(fd, "ERROR Closing Link");
    _server.disconnectClient(fd);
    // TODO отправить команнду QUIT всем каналам в которых был этот юзер с аргументом (если не дан то ник)
	return 0;
}

//PART #here
int		Cmds::PARTCmd(int fd, const Message& msg)
{
	Client *client = findClient(fd);
	if(msg.params->Params.empty())
		return setReply(fd, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG, "", "");
	std::string channelName = msg.params->Params[0];
	if (_server._channels.find(channelName) == _server._channels.end()) {
		// std::cout << "D E B U G: ERR_ NO SUCH CHANNEL" << std::endl;
		return setReply(fd, ERR_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL_MSG, channelName, "");
	}
	if (!_server._channels.find(channelName)->second->ifExist(fd)) {
		// std::cout << "D E B U G: ERR_ NOT ON CHANNEL" << std::endl;
		return setReply(fd, ERR_NOTONCHANNEL, ERR_NOTONCHANNEL_MSG, channelName, "");
	}
	_server._channels.find(channelName)->second->delParticipantIfExist(fd);
	// std::cout << "D E B U G: 	Удалили с канала. " << std::endl;
	std::set<int> *UsersStillOnChannel = _server._channels[channelName]->getParticipantsFds();
	std::set<int>::iterator it;
  	for (it=UsersStillOnChannel->begin(); it!=UsersStillOnChannel->end(); ++it) {
		writeToBuf(*it, ":" + client->getPrefix() + " PART " + channelName);
  }

}

int		Cmds::MOTDCmd(int fd, const Message& msg)
{
	return 0;
}

int		Cmds::PRIVMSGCmd(int fd, const Message& msg)
{
    if(msg.params->Params.empty())
        return setReply(fd, ERR_NORECIPIENT, ERR_NORECIPIENT_MSG, "", "");
    if(msg.params->Params.size() == 1)
        return setReply(fd, ERR_NOTEXTTOSEND, ERR_NOTEXTTOSEND_MSG, "", "");
    Client *client = findClient(fd);
    std::vector<std::string>::iterator it = msg.params->Params.begin();
    Client *recip =findClientNick(*it);
    //TODO добавить поиск по каналам
    if(recip == NULL)
        return setReply(fd, ERR_NOSUCHNICK, ERR_NOSUCHNICK_MSG, "", "");
    writeToBuf(recip->getFd(), client->getPrefix() + " PRIVMSG " + recip->getNick() + " :" + msg.params->Params[1]);
	return 0;
}

int		Cmds::MODECmd(int fd, const Message& msg)
{
	return 0;
}

int		Cmds::KICKCmd(int fd, const Message& msg)
{
	return 0;
}

int		Cmds::LUSERCmd(int fd, const Message& msg)
{
	return 0;
}

int		Cmds::USERSCmd(int fd, const Message& msg)
{
	return 0;
}

int		Cmds::PONGCmd(int fd, const Message& msg)
{
    writeToBuf(fd, "PONG " + msg.params->Params[0]);
    return 0;
}
