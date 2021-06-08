#pragma once
#include "header.hpp"
#include "Client.hpp"
#include "Codes.hpp"

class Cmds
{
private:
	std::map<int, Client*>	*_clients;

	// Client *findClientNick(std::string nick); // Ишет инстанс клиента по нику
	int		writeToBuf(int fd, std::string mess); //Записать сообщение в буфер клиента для отправки
	int		setReply(int fd, int code, std::string mess, std::string args); // создает сообщение по коду ошибки и отправляет его в writeToBuf
	int		checkNick(std::string nick); // проверка валидности ника max_len = 9, ascii 33-125 dec

public:
	Cmds(std::map<int, Client*> *clients);
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
};
