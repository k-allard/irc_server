#pragma once
#include "header.hpp"

class Client
{
private:
	int					        _fd;
	struct sockaddr_in	        _address;
	std::string			        _nick;
	std::vector<std::string>    _userdata;
	bool                        _ispass; // отправлен ли правильный пароль (после PASS)
	bool				        _isreg; // зарегистрирован ли клиент (только после NICK USER)

public:
	Client(int fd, struct sockaddr_in address);
	Client(const Client& src);
	Client& operator=(const Client& src);
	~Client();
	std::queue<std::string>		_buf; // буфер каждого клиента для получения сообщений от сервера TODT

	// Set nick (для NICK)
	void		setNick(std::string nick) {this->_nick = nick;};

	// Set userdata и помечает клиета как зарегестрированный (для USER)
	void		setUserdata(std::vector<std::string> data);
	void        setPass() {this->_ispass = true;};

	// Зарегестрированн ли клиент (незарегестрированному клиенту недоступны никакие команды кроме PASS USER NICK)
	bool		isReg() {return this->_isreg;};
	bool        isPass() {return this->_ispass;};

	// Getters
	int					getFd() {return this->_fd;};
	const std::string	&getNick() {return this->_nick;};
};
