#include "../includes/Message.hpp"

Message::Message(std::string str) {
	std::string::iterator it = str.begin();
	std::string::iterator end = str.end();
	this->prefix = new MessagePrefix(it, end);
	this->command = new MessageCommand(it, end);
	this->params = new MessageParams(it, end);
}

Message::~Message() {
    delete this->prefix;
    delete this->command;
    delete this->params;
}
