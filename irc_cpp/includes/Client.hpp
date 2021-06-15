#pragma once
#include "header.hpp"

class Client
{
private:
	int					        _fd;
	struct sockaddr_in	        _address;
	std::string			        _nick;
	std::vector<std::string>    _userdata; //0 = username, 1 = host, 2 = server, 3 = real name
	std::string                 _prefix;
	bool                        _ispass; // отправлен ли правильный пароль (после PASS)
	bool				        _isreg; // зарегистрирован ли клиент (только после NICK USER)

	// Формула префикса для клиента: <nick>!<user>@<host>
	void        setPrefix();

public:
	Client(int fd, struct sockaddr_in address);
	Client(const Client& src);
	Client& operator=(const Client& src);
	~Client();
	std::queue<std::string>		_buf; // буфер каждого клиента для получения сообщений от сервера

	char		messageBuf[513];
	int			_messageBufLength; // длина текста в messageBuf
	void		clearMessageBuffer();
	void		appendMessageBuffer(char newInputBuf[512]);
	int			isMessageBufferComplete();

	
	// Set nick (для NICK)
	void		setNick(std::string nick) {this->_nick = nick;};

	// Set userdata и помечает клиента как зарегистрированный (для USER)
	void		setUserdata(std::vector<std::string> data) {this->_userdata = data;};
	void        setPass() {this->_ispass = true;};


	// Зарегистрирован ли клиент (незарегистрированному клиенту недоступны никакие команды кроме PASS USER NICK)
	bool		isReg() {return this->_isreg;};
	bool        isPass() {return this->_ispass;};

	// Getters
	int					getFd() {return this->_fd;};
	const std::string	&getNick() {return this->_nick;};
    std::vector<std::string> *getUserdata() {return &this->_userdata;};

    void                registr();
};
