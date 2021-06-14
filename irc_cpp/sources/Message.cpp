//
// Created by Anastasia on 14.06.2021.
//

#include "../includes/Message.hpp"


Message::Message(std::string str) {
	std::string::const_iterator it = str.cbegin();
	std::string::const_iterator end = str.cend();
	this->prefix = new MessagePrefix(it, end);
	this->command = new MessageCommand(it, end);
	this->params = new MessageParams();
}

Message::~Message() {

}
