#pragma once
#include "header.hpp"
#include "../includes/Client.hpp"

class Server
{
private:
	int						_port;
	std::string				_pass;
	int 					_server_fd;
	struct sockaddr_in		_address;		// для хранения адресов ipv4
	std::set<int>			_clients_fd;	// сет с клиентами, подключенными к нашему серверу
	char					_buf[1024];		// буфер для чтения из сокетов
	fd_set					_readset;		// сет, в котором после селекта останутся фд клиентов, которые что-то написали серверу (то есть нам надо из них прочитать)
	fd_set					_writeset;		// сет, в котором после селекта останутся фд клиентов, которым нам можно писать
	int						_mx;			// максимальный номер фд среди всех
	std::map<int, Client*>	_clients;		// мапа клиентов с ключом - номером сокета и значением - ссылкой на инстанс клиента

public:
	Server(int port, std::string pass);
	~Server();
	void	mainLoop();

private:
	void	initServer();
	void	initFds();
	void	doSelect();
	void	checkFds();

	//********************//
	//  f o r _ d e b u g //
	//********************//
	void	printClients();

};

