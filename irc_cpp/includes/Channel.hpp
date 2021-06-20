#pragma once

#include "header.hpp"

class Channel
{
private:
	std::set<int>			_participants_fds; // участники канала (их сокеты)
	int						_operator_fd; // сокет оператора канала
	std::string				_topic;
	Server					&_server;

public:
	Channel(int operator_fd, Server &server) : _operator_fd (operator_fd), _server(server) {
		_participants_fds.insert(operator_fd);
		_topic = "";
	};
	~Channel() { };

	void setTopic(std::string topic) { _topic = topic; }
	std::string getTopic() { return _topic; }
	int getOperatorFd() { return _operator_fd; }
	std::string getParticipantsNames();
	void addParticipant(int fd);
	int isClientinChannel(int fd);
	bool ifExist(int fd); // проверить, состоит ли учатник в канале: 0 - нет 1 - да
	void delParticipantIfExist(int fd); //удалить учатника канала по фд, если такой есть
	std::set<int> *getParticipantsFds();
	// всем в этом канале разослать mess
	void sendMessToAll(std::string mess);

};
