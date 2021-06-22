#pragma once

#include "header.hpp"
#include "Codes.hpp"
#include "Message.hpp"

class Cmds
{
private:
	std::map<int, Client*>*				_clients;
    std::map<std::string, Channel*>*	_channels;
	Server&								_server;

	Client          *findClientNick(const std::string& nick);
    Channel         *findChannel(const std::string& name);
    Client          *findCheckClient(int fd);
	static int		checkNick(std::string nick);
    static int		isChannelNameCorrect(std::string name);
	void            regClient(int fd);
    Client          *findClient(int fd);
	Cmds();

public:
	Cmds(Server &server);
	~Cmds();

    int		setReply(int fd, const std::string& code, std::string mess);
    int		setReply(int fd, const std::string& code, std::string mess, const std::string& arg1);
    int		setReply(int fd, const std::string& code, std::string mess, const std::string& arg1, const std::string& arg2);
	int		setReply(int fd, const std::string& code, std::string mess, const std::string& arg1, const std::string& arg2, const std::string& arg3); // создает сообщение по коду ошибки и отправляет его в writeToBuf
    std::string		setMsg(const std::string& prefix, const std::string& cmd, const std::string& arg);
    std::string		setMsg(const std::string& prefix, const std::string& cmd, const std::string& arg1, const std::string& arg2);
    int		writeToBuf(int fd, std::string mess);

    int		NICKCmd(int fd, const Message& msg);
	int		PASSCmd(int fd, const Message& msg);
	int		JOINCmd(int fd, const Message& msg);
    int		QUITCmd(int fd, const Message& msg);
	int		TOPICCmd(int fd, const Message& msg);
	int		QUITCmd(int fd);
	int		PARTCmd(int fd, const Message& msg);
	int		MOTDCmd(int fd);
	int		PRIVMSGCmd(int fd, const Message& msg);
    int		NOTICECmd(int fd, const Message& msg);
	int		MODECmd(int fd, const Message& msg);
    int		WHOCmd(int fd, const Message& msg);
    int		WHOISCmd(int fd, const Message& msg);
	int		KICKCmd(int fd, const Message& msg);
	int		NAMESCmd(int fd, const Message& msg);
    int		NAMESCmd(int fd, const std::string& channelName);
	int		LUSERSCmd(int fd, const Message& msg);
	int		USERCmd(int fd, const Message& msg);
    int		PINGCmd(int fd, const Message& msg);
    int		LISTCmd(int fd, const Message& msg);
};
