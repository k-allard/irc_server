#pragma once

class Server
{
private:
	/* data */
public:
	Server(/* args */);
	~Server();
	void mainLoop();
	
private:
	void initFd();
	void doSelect();
	void checkFd();

};

