#pragma once
#include "header.hpp"

class Client
{
private:
	int					_fd;
	struct sockaddr_in	_address;
	std::string			_nick;
	std::string			_user;
	std::string			_host;
	std::string			_server;
	std::string			_real;
	bool				_isreg; // зарегистрирован ли клиент (только после NICK USER)

public:
	Client(int fd, struct sockaddr_in address);
	Client(const Client& src);
	Client& operator=(const Client& src);
	~Client();
	char*				_buf; // буфер каждого клиента для получения сообщений от сервера

	// Set nick (для NICK)
	void		setNick(std::string nick) {this->_nick = nick;};

	// Set userdata и помечает клиета как зарегестрированный (для USER)
	void		setUserData(const std::string &user, const std::string &host, 
							const std::string &server, const std::string &real);

	// Зарегестрированн ли клиент (незарегестрированному клиенту недоступны никакие команды кроме PASS USER NICK)
	bool		isReg() {return this->_isreg;};

	// Getters
	int					getFd() {return this->_fd;};
	const std::string	&getNick() {return this->_nick;};
	const std::string	&getUser() {return this->_user;};
	const std::string	&getHost() {return this->_host;};
	const std::string	&getServer() {return this->_server;};
	const std::string	&getReal() {return this->_real;};
};
