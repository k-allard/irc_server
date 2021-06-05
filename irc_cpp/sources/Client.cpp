#include "../includes/Client.hpp"

Client::Client(int fd, struct sockaddr_in address) : _fd(fd), _address(address)
{
	this->_nick = "";
	this->_user = "";
	this->_host = "";
	this->_server = "";
	this->_real = "";
	this->_isreg = false;
}

Client::Client(const Client &src)
{
	*this = src;
}

Client &Client::operator=(const Client &src)
{
	_user = src._user;
	_host = src._host;
	_server = src._server;
	_real = src._real;
	_isreg = src._isreg; 
	return *this;
}

Client::~Client()
{
}

void	Client::setUserData(const std::string &user, const std::string &host, 
							const std::string &server, const std::string &real)
{
	this->_user = user;
	this->_host = host;
	this->_server = server;
	this->_real = real;
	this->_isreg = true; 
}