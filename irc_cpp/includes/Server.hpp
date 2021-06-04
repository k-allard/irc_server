#pragma once


class Server
{
private:
	int					_port;
	std::string			_pass;
	int 				_server_fd;

public:
	Server(int port, std::string pass) : _port(port), _pass(pass), _server_fd(0) {};
	~Server();
	void mainLoop();
	
private:
	void initFd();
	void doSelect();
	void checkFd();

};

