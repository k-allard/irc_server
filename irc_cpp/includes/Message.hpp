#pragma once

#include "header.hpp"

/**
 * @a https://datatracker.ietf.org/doc/html/rfc1459#section-2.3.1
 * @code message  ::= [':' prefix SPACE ] command params crlf
 */
class Message {
public:
	Message(std::string str);
	~Message();

	MessagePrefix*	prefix;
	MessageCommand*	command;
	MessageParams*	params;
private:
	Message();
};
