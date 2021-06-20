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

std::string Channel::getNumClients()
{
    std::stringstream ss;
    ss << _participants_fds.size();
    return ss.str();
}

void Channel::addParticipant(int fd) { _participants_fds.insert(fd); }

void Channel::delParticipantIfExist(int fd) { _participants_fds.erase(fd); }

bool Channel::ifExist(int fd) { return (_participants_fds.find(fd) != _participants_fds.end()); }

std::set<int> *Channel::getParticipantsFds() { return &_participants_fds; }

// всем в этом канале разослать mess кроме fd (если есть)
void Channel::sendMessToAll(int fd, std::string mess) {
	for (std::set<int>::iterator it=_participants_fds.begin(); it!=_participants_fds.end(); ++it) {
		mess += "\r\n";
		if(*it != fd)
		    _server._clients[*it]->_buf.push(mess);
	}
}