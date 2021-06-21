#include "../includes/Cmds.hpp"


Cmds::Cmds(Server &server): _server(server)
{
	_clients = &_server._clients;
	_channels = &_server._channels;
}

Cmds::~Cmds()
{
}

Client *Cmds::findClient(int fd)
{
	std::map<int, Client*>::iterator it;
	it = _clients->find(fd);
	if (it == _clients->end()) {
		std::cerr << "ERROR in management client's socket\nExiting . . ." << std::endl;
		exit(7);
	}
	return it->second;
}

void            Cmds::regClient(int fd)
{
    Client *client = findClient(fd);
    client->registr();
    setReply(fd, RPL_WELCOME, RPL_WELCOME_MSG, client->getPrefix());
    setReply(fd, RPL_YOURHOST, RPL_YOURHOST_MSG, _server.getName());
    setReply(fd, RPL_CREATED, RPL_CREATED_MSG, _server._toc);
    setReply(fd, RPL_MYINFO, RPL_MYINFO_MSG, _server.getName());
    //setReply(fd, "251", ":There are 2 users and 0 services on 0 servers");
    //setReply(fd, "254", "1 :channels formed");
    //setReply(fd, "255", ":I have 2 clients and 0 servers");
    MOTDCmd(fd);
}

int		Cmds::writeToBuf(int fd, std::string mess)
{
	Client *client = findClient(fd);
	mess += "\r\n";
	client->_buf.push(mess);
	return 1;
}

std::string 	Cmds::setMsg(const std::string& prefix, const std::string& cmd, const std::string& arg)
{
    return (":" + prefix + " " + cmd + " " + arg);
}

std::string		Cmds::setMsg(const std::string& prefix, const std::string& cmd, const std::string& arg1, const std::string& arg2)
{
    return (":" + prefix + " " + cmd + " " + arg1 + " :" + arg2);
}

int		Cmds::setReply(int fd, const std::string& code, std::string mess)
{
    std::string res;
    Client *client = findClient(fd);
    res += ":" + _server.getName() + " " + code;
    if(!client->getNick().empty())
        res += " " + client->getNick();
    else
        res += " *";
    res += " " + mess;
    writeToBuf(fd, res);
    return 0;
}

int		Cmds::setReply(int fd, const std::string& code, std::string mess, const std::string& arg1)
{
    std::string res;
    Client *client = findClient(fd);
    res += ":" + _server.getName() + " " + code;
    if(!client->getNick().empty())
        res += " " + client->getNick();
    else
        res += " *";
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
    res += " " + mess;
    writeToBuf(fd, res);
    return 0;
}

int		Cmds::setReply(int fd, const std::string& code, std::string mess, const std::string& arg1, const std::string& arg2)
{
	std::string res;
	Client *client = findClient(fd);
    res += ":" + _server.getName() + " " + code;
	if(!client->getNick().empty())
		res += " " + client->getNick();
	else
		res += " *";
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
	res += " " + mess;
	writeToBuf(fd, res);
	return 0;
}

int		Cmds::setReply(int fd, const std::string& code, std::string mess, const std::string& arg1, const std::string& arg2, const std::string& arg3)
{
    std::string res;
    Client *client = findClient(fd);
    res += ":" + _server.getName() + " " + code;
    if(!client->getNick().empty())
        res += " " + client->getNick();
    else
        res += " *";
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
    if(!arg3.empty()) {
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
        mess.replace(begin_insertion, end_insertion, arg3);
    }
    res += " " + mess;
    writeToBuf(fd, res);
    return 0;
}

int		Cmds::checkNick(std::string nick)
{
    if(isChannelNameCorrect(nick))
        return 0;
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

Channel *Cmds::findChannel(const std::string& name)
{
    std::map<std::string, Channel*>::iterator it;
    it = _channels->find(name);
    if (it == _channels->end())
        return NULL;
    return it->second;
}

int		Cmds::NICKCmd(int fd, const Message& msg)
{
	Client *client = findClient(fd);
	if(!client->isPass())
		return setReply(fd, ERR_NOTREGISTERED, ERR_NOTREGISTERED_MSG);
	if(msg.params->Params.empty())
		return setReply(fd, ERR_NONICKNAMEGIVEN, ERR_NONICKNAMEGIVEN_MSG);
	if(checkNick(msg.params->Params[0]) == 0)
		return setReply(fd, ERR_ERRONEUSNICKNAME, ERR_ERRONEUSNICKNAME_MSG, msg.params->Params[0]);
	if(findClientNick(msg.params->Params[0]) != NULL)
        return setReply(fd, ERR_NICKNAMEINUSE, ERR_NICKNAMEINUSE_MSG, msg.params->Params[0]);
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
		return setReply(fd, ERR_ALREADYREGISTRED, ERR_ALREADYREGISTRED_MSG);
	if(msg.params->Params.empty())
		return setReply(fd, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG, "PASS");
	if(msg.params->Params[0] == _server.getPass())
	    client->setPass();
	return 0;
}

int		Cmds::USERCmd(int fd, const Message& msg)
{
	Client *client = findClient(fd);
	if (client == NULL)
		return -1;
	if(!client->isPass())
		return setReply(fd, ERR_NOTREGISTERED, ERR_NOTREGISTERED_MSG);
	if(client->isReg())
		return setReply(fd, ERR_ALREADYREGISTRED, ERR_ALREADYREGISTRED_MSG);
	if(msg.params->Params.empty() || msg.params->Params.size() < 4)
		return setReply(fd, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG, "USER");
	client->setUserdata(msg.params->Params);
	if(!client->getNick().empty())
        regClient(fd);
	return 0;
}

int		Cmds::JOINCmd(int fd, const Message& msg)
{
	if(msg.params->Params.empty())
		return setReply(fd, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG);
	std::string channelName = msg.params->Params[0];
	Client *client = findClient(fd);
    Channel *ch = findChannel(channelName);
	if (ch != NULL)
	{
		if (ch->ifExist(fd))
			return setReply(fd, ERR_USERONCHANNEL, ERR_USERONCHANNEL_MSG, client->getNick(), channelName);
		ch->addParticipant(fd);
        ch->sendMessToAll(0, setMsg(client->getPrefix(), "JOIN", channelName));
		if (!ch->getTopic().empty())
			setReply(fd, RPL_TOPIC, RPL_TOPIC_MSG, channelName, _server._channels[channelName]->getTopic());
        NAMESCmd(fd, channelName);
	}
	else
	{
		if (!isChannelNameCorrect(channelName))
            return setReply(fd, ERR_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL_MSG, channelName);
		Channel *newChannel = new Channel(fd, _server);
		_server._channels.insert( std::pair<std::string, Channel*>(channelName,newChannel));
        writeToBuf(fd, setMsg(client->getPrefix(), "JOIN", channelName));
        NAMESCmd(fd, channelName);
	}
	return 0;
}

int Cmds::isChannelNameCorrect(std::string name) {
	if ((name.at(0) != '#') || (name.find(' ') != std::string::npos) || (name.length() > 50))
		return 0;
	for (int i = 1; i < name.length(); i++) {
		char ch = name.at(i);
		if (ch < 48 || (ch > 57 && ch < 65) || (ch > 90 && ch < 97) || ch > 122)
			return 0;
	}
	return 1;
}

int		Cmds::TOPICCmd(int fd, const Message& msg) {
	if(msg.params->Params.empty())
		return setReply(fd, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG);
	std::string channelName = msg.params->Params[0];
	std::map<std::string, Channel *>::iterator it = _server._channels.find(channelName);
	if (it == _server._channels.end())
		return -1;
	Channel *channel = it->second;
	if (!channel->ifExist(fd)) {
		return setReply(fd, ERR_NOTONCHANNEL, ERR_NOTONCHANNEL_MSG, channelName);
	}
	if(msg.params->Params.size() == 2) {
		if (channel->getOperatorFd() != fd)
			return setReply(fd, ERR_CHANOPRIVSNEEDED, ERR_CHANOPRIVSNEEDED_MSG, channelName);
		channel->setTopic(msg.params->Params[1]);
		return 0;
	}
	if (channel->getTopic().empty())
		return setReply(fd, RPL_NOTOPIC, RPL_NOTOPIC_MSG, channelName);
	return setReply(fd, RPL_TOPIC, RPL_TOPIC_MSG, channelName, channel->getTopic());

}

int		Cmds::QUITCmd(int fd, const Message& msg)
{
    writeToBuf(fd, "ERROR Closing Link");
    Client *client = findClient(fd);
    std::string mess = client->getNick();
    if(!msg.params->Params.empty())
        mess = msg.params->Params[0];
    for(std::map<std::string, Channel*>::iterator it = _channels->begin(); it != _channels->end(); ++it)
    {
        if(it->second->ifExist(fd))
        {
            it->second->delParticipantIfExist(fd);
            it->second->sendMessToAll(fd, setMsg(client->getPrefix(), "QUIT", mess));
        }
    }
    _server.disconnectClient(fd);
    return 0;
}

int		Cmds::QUITCmd(int fd)
{
    Client *client = findClient(fd);
    for(std::map<std::string, Channel*>::iterator it = _channels->begin(); it != _channels->end(); ++it)
    {
        if(it->second->ifExist(fd))
        {
            it->second->delParticipantIfExist(fd);
            it->second->sendMessToAll(fd, setMsg(client->getPrefix(), "QUIT", client->getNick()));
        }
    }
    _server.disconnectClient(fd);
	return 0;
}

//PART #here
int		Cmds::PARTCmd(int fd, const Message& msg)
{
	Client *client = findClient(fd);
	if(msg.params->Params.empty())
		return setReply(fd, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG);

	std::string ch_name = msg.params->Params[0];
    Channel *ch = findChannel(ch_name);
    if (ch == NULL)
        return setReply(fd, ERR_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL_MSG, ch_name);

    std::string mess = client->getNick();
    if(msg.params->Params.size() == 2)
        mess = msg.params->Params[1];

	if (!ch->ifExist(fd))
		return setReply(fd, ERR_NOTONCHANNEL, ERR_NOTONCHANNEL_MSG, ch_name);

    ch->sendMessToAll(0, setMsg(client->getPrefix(), "PART", ch_name, mess));
    ch->delParticipantIfExist(fd);
    if (ch->getParticipantsFds()->empty())
        _channels->erase(ch_name);
	return 0;
}

int		Cmds::MOTDCmd(int fd)
{
    setReply(fd, RPL_MOTDSTART, RPL_MOTDSTART_MSG, _server.getName());
    setReply(fd, RPL_MOTD, RPL_MOTD_MSG, "Hi! Welcome to our humble IRC server!");
    setReply(fd, RPL_ENDOFMOTD, RPL_ENDOFMOTD_MSG);
	return 0;
}

int		Cmds::PRIVMSGCmd(int fd, const Message& msg)
{
    if(msg.params->Params.empty())
        return setReply(fd, ERR_NORECIPIENT, ERR_NORECIPIENT_MSG, "PRIVMSG");
    if(msg.params->Params.size() == 1)
        return setReply(fd, ERR_NOTEXTTOSEND, ERR_NOTEXTTOSEND_MSG);
    Client *client = findClient(fd);
    std::vector<std::string>::iterator it = msg.params->Params.begin();
    if(isChannelNameCorrect(*it))
    {
        Channel *recip = findChannel(*it);
        if(recip == NULL)
            return setReply(fd, ERR_NOSUCHNICK, ERR_NOSUCHNICK_MSG, *it);
        if(!recip->ifExist(fd))
            return setReply(fd, ERR_CANNOTSENDTOCHAN, ERR_CANNOTSENDTOCHAN_MSG, *it);
        recip->sendMessToAll(fd, setMsg(client->getPrefix(), "PRIVMSG", *it, msg.params->Params[1]));
    }
    else
    {
        Client *recip = findClientNick(*it);
        if(recip == NULL)
            return setReply(fd, ERR_NOSUCHNICK, ERR_NOSUCHNICK_MSG, *it);
        writeToBuf(recip->getFd(), setMsg(client->getPrefix(), "PRIVMSG", recip->getNick(), msg.params->Params[1]));
    }
	return 0;
}

int		Cmds::MODECmd(int fd, const Message& msg)
{
	return 0;
}

int		Cmds::WHOCmd(int fd, const Message& msg)
{
    return 0;
}

int		Cmds::WHOISCmd(int fd, const Message& msg)
{
    return 0;
}

int		Cmds::KICKCmd(int fd, const Message& msg)
{
	if(msg.params->Params.size() < 2)
        return setReply(fd, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG);
    std::string ch_name = msg.params->Params[0];
    Channel *ch = findChannel(ch_name);
    if (ch == NULL)
        return setReply(fd, ERR_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL_MSG, ch_name);
    Client *kick = findClientNick(msg.params->Params[1]);
    if(kick == NULL || !ch->ifExist(kick->getFd()))
        setReply(fd, ERR_USERNOTINCHANNEL, ERR_USERNOTINCHANNEL_MSG, msg.params->Params[1], ch_name);

    std::string mess = kick->getNick();
    if(msg.params->Params.size() == 3)
        mess = msg.params->Params[2];

	if (ch->getOperatorFd() != fd)
		return setReply(fd, ERR_CHANOPRIVSNEEDED, ERR_CHANOPRIVSNEEDED_MSG, ch_name);

	ch->sendMessToAll(0, setMsg(findClient(fd)->getPrefix(), "KICK", ch_name + " " + kick->getNick(), mess));
	ch->delParticipantIfExist(kick->getFd());
    if (ch->getParticipantsFds()->empty())
        _channels->erase(ch_name);
	return 0;
}

int		Cmds::NAMESCmd(int fd, const std::string& channelName)
{
    Channel *ch = findChannel(channelName);
    if(ch != NULL)
        setReply(fd, RPL_NAMREPLY, RPL_NAMREPLY_MSG, channelName, ch->getParticipantsNames());
    return setReply(fd, RPL_ENDOFNAMES, RPL_ENDOFNAMES_MSG);
}

int		Cmds::NAMESCmd(int fd, const Message& msg)
{
	if(msg.params->Params.empty()) {
		for (std::map<std::string, Channel *>::iterator it=_server._channels.begin(); it!=_server._channels.end(); ++it)
    		setReply(fd, RPL_NAMREPLY, RPL_NAMREPLY_MSG, it->first, it->second->getParticipantsNames());
		std::string notInChannels = _server.getNamesNotInChannels();
		if (!notInChannels.empty())
			setReply(fd, RPL_NAMREPLY, RPL_NAMREPLY_MSG, "*", notInChannels);
	}
	else {
		// отправили ему список участников одного канала + конечное сообщение
		std::string channelName = msg.params->Params[0];
		Channel *ch = findChannel(channelName);
		if(ch != NULL)
		    setReply(fd, RPL_NAMREPLY, RPL_NAMREPLY_MSG, channelName, _server._channels[channelName]->getParticipantsNames());
	}
	return setReply(fd, RPL_ENDOFNAMES, RPL_ENDOFNAMES_MSG);
}

int		Cmds::LUSERSCmd(int fd, const Message& msg)
{
	const int i = _server.getNumOfUsers();
	std::ostringstream s;
	s << i;
	std::string numOfUsers(s.str());
	setReply(fd, RPL_LUSERCLIENT, RPL_LUSERCLIENT_MSG, numOfUsers, "0", "1"); 	//кол-во всех учатсников в сети

	if (!_channels->empty()) {
		std::ostringstream f;
		f << _channels->size();
		std::string numOfChannels(f.str());
		setReply(fd, RPL_LUSERCHANNELS, RPL_LUSERCHANNELS_MSG, numOfChannels);                    //колво каналов, если они есть
	}

	return setReply(fd, RPL_LUSERME, RPL_LUSERME_MSG, numOfUsers, "1");						 //кол-во всех участников в сети
}

int		Cmds::PONGCmd(int fd, const Message& msg)
{
    Client *client = findClient(fd);
    writeToBuf(fd, setMsg(_server.getName(), "PONG", client->getNick(), msg.params->Params[0]));
    return 0;
}

int		Cmds::LISTCmd(int fd, const Message& msg)
{
    if(msg.params->Params.empty())
    {
        setReply(fd, RPL_LISTSTART, RPL_LISTSTART_MSG);
        for (std::map<std::string, Channel*>::iterator it = _channels->begin(); it != _channels->end(); ++it)
            setReply(fd, RPL_LIST, RPL_LIST_MSG, it->first, it->second->getNumClients(), it->second->getTopic());
        setReply(fd, RPL_LISTEND, RPL_LISTEND_MSG);
    }
    else
    {
        Channel *ch = findChannel(msg.params->Params[0]);
        if(ch != NULL) {
            setReply(fd, RPL_LISTSTART, RPL_LISTSTART_MSG);
            setReply(fd, RPL_LIST, RPL_LIST_MSG, msg.params->Params[0], ch->getNumClients(), ch->getTopic());
            setReply(fd, RPL_LISTEND, RPL_LISTEND_MSG);
        }
    }
    return 0;
}
