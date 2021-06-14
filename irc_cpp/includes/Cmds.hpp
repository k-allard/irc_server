#pragma once
#include "header.hpp"
#include "Client.hpp"
#include "Codes.hpp"

class Cmds
{
private:
	std::map<int, Client*>	*_clients;
	Server &_server;

	Client *findClientNick(const std::string& nick); // Ишет инстанс клиента по нику
	// int     checkClient(int fd); // TODO проверяет существует и зарегестрирован ли клиент (для вызова перед каждой коммандой кроме PASS NICK USER)
	int		writeToBuf(int fd, std::string mess); //Записать сообщение в буфер клиента для отправки
	int		setReply(int fd, int code, std::string mess, std::string args); // создает сообщение по коду ошибки и отправляет его в writeToBuf
	static int		checkNick(std::string nick); // проверка валидности ника max_len = 9, ascii 33-125 dec

public:
	Cmds(Server &server);
	~Cmds();

	Client *findClient(int fd); // Ишет инстанс клиента по fd

	int		NICKCmd(int fd, std::string args);
	int		PASSCmd(int fd, std::string args);
	int		JOINCmd(int fd, std::string args);
	int		QUITCmd(int fd, std::string args);
	int		PARTCmd(int fd, std::string args);
	int		MOTDCmd(int fd, std::string args);
	int		PRIVMSGCmd(int fd, std::string args);
	int		MODECmd(int fd, std::string args);
	int		KICKCmd(int fd, std::string args);
	int		LUSERCmd(int fd, std::string args);
	int		USERCmd(int fd, std::string args);
	int		USERSCmd(int fd, std::string args);
    int		PONGCmd(int fd, std::string args);
};
