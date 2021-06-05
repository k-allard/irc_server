#include "../includes/Client.hpp"

Client::Client(int fd, struct sockaddr_in address) : _fd(fd), _address(address) {
    bzero(_buf, 1024);
}

Client::~Client()
{
}
