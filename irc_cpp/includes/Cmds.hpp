#pragma once
#include "header.hpp"
#include "Client.hpp"
#include "Codes.hpp"
#include "Message.hpp"

class Cmds
{
private:
	std::map<int, Client*>	*_clients;
	Server &_server;

	Client          *findClientNick(const std::string& nick); // Ишет инстанс клиента по нику
	// int          checkClient(int fd); // TODO проверяет существует и зарегестрирован ли клиент (для вызова перед каждой коммандой кроме PASS NICK USER)
	int		        writeToBuf(int fd, std::string mess); //Записать сообщение в буфер клиента для отправки
	static int		checkNick(std::string nick); // проверка валидности ника max_len = 9, ascii 33-125 dec
	void            regClient(int fd);
    Client          *findClient(int fd); // Ишет инстанс клиента по fd

public:
	Cmds(Server &server);
	~Cmds();

	int		setReply(int fd, int code, std::string mess, std::string args); // создает сообщение по коду ошибки и отправляет его в writeToBuf

	int		NICKCmd(int fd, const Message& msg);
	int		PASSCmd(int fd, const Message& msg);
	int		JOINCmd(int fd, const Message& msg);
	int		QUITCmd(int fd, const std::string& msg);
	int		PARTCmd(int fd, const Message& msg);
	int		MOTDCmd(int fd, const Message& msg);
	int		PRIVMSGCmd(int fd, const Message& msg);
	int		MODECmd(int fd, const Message& msg);
	int		KICKCmd(int fd, const Message& msg);
	int		LUSERCmd(int fd, const Message& msg);
	int		USERCmd(int fd, const Message& msg);
	int		USERSCmd(int fd, const Message& msg);
    int		PONGCmd(int fd, const Message& msg);
};
