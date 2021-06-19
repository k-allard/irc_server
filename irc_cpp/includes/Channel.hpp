#pragma once
#include "header.hpp"

class Channel
{
private:
	std::set<int>			_participants_fds; // участники канала (их сокеты)
	int						_operator_fd; // сокет оператора канала
	std::string				_topic;
	Server					*_server;

public:
	Channel(int operator_fd, Server *server) : _operator_fd (operator_fd), _server(server) {
		_participants_fds.insert(operator_fd);
		_topic = "";
	};

	~Channel() { };

	void setTopic(std::string topic) { _topic = topic; }

	std::string getTopic() { return _topic; }



};
