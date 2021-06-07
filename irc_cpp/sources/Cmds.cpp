#include "../includes/Cmds.hpp"


Cmds::Cmds(std::map<int, Client*> *clients): _clients(clients)
{
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

int		Cmds::nickCmd(int fd, std::string args)
{
	Client *client = findClient(fd);
	if (client == NULL)
	{
		perror("clien not found");
		return -1;
	}
	// Проверить есть ли такой ник на сервере
	client->setNick(args);
	return 0;
}
