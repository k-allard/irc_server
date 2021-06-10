#include "../includes/Client.hpp"

Client::Client(int fd, struct sockaddr_in address) : _fd(fd), _address(address)
{
	this->_nick = "";
	this->_isreg = false;
	this->_ispass = false;
}

Client::Client(const Client &src)
{
	*this = src;
}

Client &Client::operator=(const Client &src)
{
	_nick = src._nick;
	_userdata = src._userdata;
	_isreg = src._isreg;
	_ispass = src._ispass;
	return *this;
}

Client::~Client()
{
}

void	Client::setUserdata(std::vector<std::string> data)
{
	this->_userdata = data;
	this->_isreg = true; 
}