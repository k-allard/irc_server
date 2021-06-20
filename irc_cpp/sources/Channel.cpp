#include "../includes/Channel.hpp"

std::string Channel::getParticipantsNames() {
	std::string names = "";

	for (std::set<int>::iterator it=_participants_fds.begin(); it!=_participants_fds.end(); ++it) {
		if (*it == _operator_fd)
			names += "@";
		names += _server._clients[*it]->getNick();
		names += " ";
	}
	if (!names.empty())
		names.erase(names.size() - 1, 1);
	return names;
}

void Channel::addParticipant(int fd) { _participants_fds.insert(fd); }

void Channel::delParticipantIfExist(int fd) { _participants_fds.erase(fd); }

bool Channel::ifExist(int fd) { return (_participants_fds.find(fd) != _participants_fds.end()); }

std::set<int> *Channel::getParticipantsFds() { return &_participants_fds; }

// всем в этом канале разослать mess
void Channel::sendMessToAll(std::string mess) {
	for (std::set<int>::iterator it=_participants_fds.begin(); it!=_participants_fds.end(); ++it) {
		mess += "\r\n";
		_server._clients[*it]->_buf.push(mess);
	}
}

int Channel::isClientinChannel(int fd)
{
    std::set<int>::iterator it=_participants_fds.find(fd);
    if(it == _participants_fds.end())
        return 0;
    return 1;
}