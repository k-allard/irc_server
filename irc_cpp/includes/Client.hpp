#pragma once
#include "header.hpp"

class Client
{
private:
	int					_fd;
	struct sockaddr_in	_address;

public:
	Client(int fd, struct sockaddr_in address);
	~Client();
};
