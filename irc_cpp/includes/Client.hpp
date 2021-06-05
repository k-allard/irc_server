#pragma once
#include "header.hpp"

class Client
{
private:
	int					_fd;
	struct sockaddr_in	_address;
	char				_buf[1024];		// буфер каждого клиента для получения сообщений от сервера

public:
	Client(int fd, struct sockaddr_in address);
	~Client();
};
