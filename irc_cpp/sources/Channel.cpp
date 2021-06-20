#include "../includes/Channel.hpp"

std::string Channel::getParticipantsNames() {
	std::string names;
	std::map<int, Client *>::iterator itAfterLast = _server._clients.end();
	itAfterLast--;
	for (std::map<int, Client *>::iterator it=_server._clients.begin(); it!=_server._clients.end(); ++it) {
		names += (*it).second->getNick();
		if (it!=itAfterLast)
			names += " ";
	}
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