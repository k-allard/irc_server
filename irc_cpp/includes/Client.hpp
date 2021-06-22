#pragma once
#include "header.hpp"

class Client
{
private:
	int					        _fd;
	std::string			        _nick;
	std::vector<std::string>    _userdata; //0 = username, 1 = host, 2 = server, 3 = real name
	bool                        _ispass;
	bool				        _isreg;
	Client();

public:
	Client(int fd);
	Client(const Client& src);
	Client& operator=(const Client& src);
	~Client() { }

	std::queue<std::string>		_buf;
	char						messageBuf[513];
	int							_messageBufLength;
	void						clearMessageBuffer();
	void						appendMessageBuffer(char newInputBuf[512]);
	int							isMessageBufferComplete();
	void						setNick(std::string nick) {this->_nick = nick;};
	void						setUserdata(std::vector<std::string> data) {this->_userdata = data;};
	void						setPass() {this->_ispass = true;};
	bool						isReg() {return this->_isreg;};
	bool						isPass() {return this->_ispass;};
    void						registr() {this->_isreg = true;};

	// Getters
	int							getFd() {return this->_fd;};
	const std::string&			getNick() {return this->_nick;};
	const std::string&			getUsername() {return this->_userdata[0];};
    const std::string&			getHost() {return this->_userdata[1];};
    const std::string&			getServer() {return this->_userdata[2];};
    const std::string&			getRealname() {return this->_userdata[3];};
    std::string					getPrefix();
    std::vector<std::string>*	getUserdata() {return &this->_userdata;}
};
