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

	int		nickCmd(int fd, std::string args);
};
