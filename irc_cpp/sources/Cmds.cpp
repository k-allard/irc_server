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

int		Cmds::NICKCmd(int fd, std::string args)
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

int		Cmds::PASSCmd(int fd, std::string args)
{
	Client *client = findClient(fd);
	if (client == NULL)
	{
		perror("clien not found");
		return -1;
	}

	return 0;
}

int		Cmds::JOINCmd(int fd, std::string args)
{
	Client *client = findClient(fd);
	if (client == NULL)
	{
		perror("clien not found");
		return -1;
	}

	return 0;
}

int		Cmds::QUITCmd(int fd, std::string args)
{
	Client *client = findClient(fd);
	if (client == NULL)
	{
		perror("clien not found");
		return -1;
	}

	return 0;
}

int		Cmds::PARTCmd(int fd, std::string args)
{
	Client *client = findClient(fd);
	if (client == NULL)
	{
		perror("clien not found");
		return -1;
	}

	return 0;
}

int		Cmds::MOTDCmd(int fd, std::string args)
{
	Client *client = findClient(fd);
	if (client == NULL)
	{
		perror("clien not found");
		return -1;
	}

	return 0;
}

int		Cmds::PRIVMSGCmd(int fd, std::string args)
{
	Client *client = findClient(fd);
	if (client == NULL)
	{
		perror("clien not found");
		return -1;
	}

	return 0;
}

int		Cmds::MODECmd(int fd, std::string args)
{
	Client *client = findClient(fd);
	if (client == NULL)
	{
		perror("clien not found");
		return -1;
	}

	return 0;
}

int		Cmds::KICKCmd(int fd, std::string args)
{
	Client *client = findClient(fd);
	if (client == NULL)
	{
		perror("clien not found");
		return -1;
	}

	return 0;
}

int		Cmds::LUSERCmd(int fd, std::string args)
{
	Client *client = findClient(fd);
	if (client == NULL)
	{
		perror("clien not found");
		return -1;
	}

	return 0;
}

int		Cmds::USERCmd(int fd, std::string args)
{
	Client *client = findClient(fd);
	if (client == NULL)
	{
		perror("clien not found");
		return -1;
	}

	return 0;
}

int		Cmds::USERSCmd(int fd, std::string args)
{
	Client *client = findClient(fd);
	if (client == NULL)
	{
		perror("clien not found");
		return -1;
	}

	return 0;
}
