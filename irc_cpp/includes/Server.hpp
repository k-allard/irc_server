#pragma once
#include "header.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Cmds.hpp"
#include "Parser.hpp"


class Server
{
private:
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

public:
	Server(int port, std::string pass);
	~Server();
	void	mainLoop();
	std::map<int, Client*>	_clients;		// мапа клиентов с ключом - номером сокета и значением - ссылкой на инстанс клиента
	//std::map<std::string, Channel*> _channels; // мапа каналов с ключом - названием канала

	std::string getPass() {return this->_pass;};

private:
	void	initServer();
	void	initFds();
	void	doSelect();
	void	checkFds();

	//********************//
	//  f o r _ d e b u g //
	//********************//
	void	printClients();
	void	temParser(int fd, char *buf, int size);
};

