#pragma once

#include "header.hpp"

class Server
{
private:
    std::string             _name;
	int						_port;
	std::string				_pass;
	int 					_server_fd;
	struct sockaddr_in		_address;		// для хранения адресов ipv4
	std::set<int>			_clients_fd;	// сет с клиентами, подключенными к нашему серверу
	char					_buf[512];		// буфер для чтения из сокетов
	fd_set					_readset;		// сет, в котором после селекта останутся фд клиентов, которые что-то написали серверу (то есть нам надо из них прочитать)
	fd_set					_writeset;		// сет, в котором после селекта останутся фд клиентов, которым нам можно писать
	int						_mx;			// максимальный номер фд среди всех
	Parser					*_parser;		// парсер входящих команд
	Server();

public:
	Server(int port, std::string pass);
	~Server();

	std::map<int, Client*>			_clients;
	std::map<std::string, Channel*>	_channels;
    std::string						_toc;

	int						disconnectClient(int fd);
	std::string				getPass() {return this->_pass;};
    std::string				getName() {return this->_name;};
	std::string				getNamesNotInChannels();
	int						getNumOfUsers() { return _clients_fd.size(); };
	void					mainLoop();

private:
	void					initServer();
	void					initFds();
	void					doSelect();
	void					checkFds();
	void					processMessage(const Message *msg, int fd, Client *client, Cmds *cmds);
};
