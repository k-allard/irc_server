#include "../includes/Client.hpp"

Client::Client(int fd, struct sockaddr_in address) : _fd(fd), _address(address) {
	this->_buf = new char[1024];
    bzero(this->_buf, 1024);
}

Client::~Client()
{
	delete[] this->_buf;
}
