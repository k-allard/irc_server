#include "../includes/Client.hpp"

Client::Client(int fd, struct sockaddr_in address) : _fd(fd), _address(address)
{
	this->_nick = "";
	this->_isreg = false;
	this->_ispass = false;

	this->_messageBufLength = 0;
	this->messageBuf[0] = '\0';
}

Client::Client(const Client &src)
{
	*this = src;
}

std::string        Client::getPrefix()
{
	if (!_userdata.empty())
    	return (_nick + "!" + _userdata[0] + "@" + _userdata[1]);
	else 
		return ("nick!user@host");
}

Client &Client::operator=(const Client &src)
{
	_nick = src._nick;
	_userdata = src._userdata;
	_isreg = src._isreg;
	_ispass = src._ispass;

	_messageBufLength = src._messageBufLength;
	strcpy(messageBuf, src.messageBuf);

	return *this;
}

Client::~Client()
{
}

void	Client::clearMessageBuffer()
{
	this->_messageBufLength = 0;
	this->messageBuf[0] = 0;
}
void	Client::appendMessageBuffer(char newInputBuf[512])
{
	int i = 0;
	while (_messageBufLength < 512 && i < 512 && newInputBuf[i] != 0)
	{
		messageBuf[_messageBufLength] = newInputBuf[i];
		i++;
		_messageBufLength++;
		messageBuf[_messageBufLength] = 0;
	}
	if(_messageBufLength == 512 && !isMessageBufferComplete())
	{
		//messageBuf[510] = 0x0D;
		messageBuf[511] = 0x0A;
		messageBuf[512] = 0x00;
	}
}
int		Client::isMessageBufferComplete()
{
	int isComplete = 0;
	if(_messageBufLength > 1)
	{
		if (messageBuf[_messageBufLength-1] == 0x0A)
		{
			isComplete = 1;
		}
	}
	return (isComplete);
}
