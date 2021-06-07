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

int		Cmds::writeToBuf(int fd, std::string mess)
{
	Client *client = findClient(fd);
	if (client == NULL)
	{
		perror("clien not found");
		return -1;
	}
	bzero(client->_buf, 1024);
	mess += "\r\n";
	strcpy(client->_buf, mess.c_str());
	std::cout << "MSG: " << client->_buf << std::endl;
	return 1;
}

// Формат ответа:
// Префикс с названием хоста + код ошибки в формате трехзначного числа + ник получателя (если нет то *) + аргументы полученой команды (если есть) + сообщение по коду
// Пример: ":irc.example.com 001 borja :Welcome to the Internet Relay Network borja!borja@polaris.cs.uchicago.edu"

int		Cmds::setReply(int fd, int code, std::string mess, std::string args)
{
	std::string res;
	Client *client = findClient(fd);
	if (client == NULL)
	{
		perror("clien not found");
		return -1;
	}
	// Добавить префикс
	res = std::to_string(code);
	if(!client->getNick().empty())
		res += " " + client->getNick();
	else
		res += " *";
	if(!args.empty())
		res += " " + args;
	res += " " + mess;
	writeToBuf(fd, res);
	return 1;
}

int		Cmds::NICKCmd(int fd, std::string args)
{
	Client *client = findClient(fd);
	if (client == NULL)
	{
		perror("clien not found");
		return -1;
	}
	if(args.empty())
	{
		setReply(fd, ERR_NONICKNAMEGIVEN, ERR_NONICKNAMEGIVEN_MSG, "");
		return 0;
	}
	// Проверить валидность ника
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
