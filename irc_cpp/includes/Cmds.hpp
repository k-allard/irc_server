#pragma once
#include "header.hpp"
#include "Client.hpp"

class Cmds
{
private:
	std::map<int, Client*>	*_clients;
	
public:
	Cmds(std::map<int, Client*> *clients);
	~Cmds();

	Client *findClient(int fd); // Ишет инстанс клиента по fd
	int		setMessage(int fd, std::string message); //Записать сообщение в буфер клиента для отправки

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
