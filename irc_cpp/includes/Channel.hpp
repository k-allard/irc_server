#pragma once

#include "header.hpp"

class Channel
{
private:
	std::set<int>			_participants_fds;
	int						_operator_fd;
	std::string				_topic;
	Server&					_server;
	Channel();

public:
	Channel(int operator_fd, Server &server) : _operator_fd (operator_fd), _server(server) {
		_participants_fds.insert(operator_fd);
		_topic = "";
	};
	~Channel() { };

	void			setTopic(std::string topic) { _topic = topic; }
	std::string		getTopic() { return _topic; }
	std::string		getNumClients();
	int				getOperatorFd() { return _operator_fd; }
	void			setOperatorFd(int fd) {_operator_fd = fd;}
	void			delOperatorFd() {_operator_fd = 0;}
	std::string		getParticipantsNames();
	void			addParticipant(int fd);
	bool			ifExist(int fd);								// проверить, состоит ли участник в канале: 0 - нет 1 - да
	void			delParticipantIfExist(int fd);					// удалить участника канала по фд, если такой есть
	std::set<int>*	getParticipantsFds();
	void			sendMessToAll(int fd, std::string mess);		// всем в этом канале кроме отправителя разослать mess
};
