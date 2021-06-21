#pragma once
#include "header.hpp"
/*
PASS 123
NICK petya
USER petr petr petr petr

PASS 123
NICK natasha
USER natali natali natali natali
*/
#include "Codes.hpp"
#include "Message.hpp"


class Cmds
{
private:
	std::map<int, Client*>	*_clients;
    std::map<std::string, Channel*> *_channels;
	Server &_server;

	Client          *findClientNick(const std::string& nick); // Ишет инстанс клиента по нику
    Channel         *findChannel(const std::string& name);
	// int          checkClient(int fd); // TODO проверяет существует и зарегестрирован ли клиент (для вызова перед каждой коммандой кроме PASS NICK USER)
	static int		checkNick(std::string nick); // проверка валидности ника max_len = 9, ascii 33-125 dec
    static int		isChannelNameCorrect(std::string name);
	void            regClient(int fd);
    Client          *findClient(int fd); // Ишет инстанс клиента по fd

public:
	Cmds(Server &server);
	~Cmds();

    int		setReply(int fd, const std::string& code, std::string mess);
    int		setReply(int fd, const std::string& code, std::string mess, const std::string& arg1);
    int		setReply(int fd, const std::string& code, std::string mess, const std::string& arg1, const std::string& arg2);
	int		setReply(int fd, const std::string& code, std::string mess, const std::string& arg1, const std::string& arg2, const std::string& arg3); // создает сообщение по коду ошибки и отправляет его в writeToBuf
	int		writeToBuf(int fd, std::string mess); //Записать сообщение в буфер клиента для отправки
	int		NICKCmd(int fd, const Message& msg);
	int		PASSCmd(int fd, const Message& msg);
	int		JOINCmd(int fd, const Message& msg);
    int		QUITCmd(int fd, const Message& msg);
	int		TOPICCmd(int fd, const Message& msg);
	int		QUITCmd(int fd);
	int		PARTCmd(int fd, const Message& msg);
	int		MOTDCmd(int fd, const Message& msg);
	int		PRIVMSGCmd(int fd, const Message& msg);
	int		MODECmd(int fd, const Message& msg);
	int		KICKCmd(int fd, const Message& msg);
	int		NAMESCmd(int fd, const Message& msg);
	int		LUSERCmd(int fd, const Message& msg);
	int		USERCmd(int fd, const Message& msg);
	int		USERSCmd(int fd, const Message& msg);
    int		PONGCmd(int fd, const Message& msg);
    int		LISTCmd(int fd, const Message& msg);
};
