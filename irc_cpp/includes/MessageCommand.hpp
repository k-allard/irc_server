#pragma once

#include "header.hpp"

/**
 * @a https://datatracker.ietf.org/doc/html/rfc1459#section-2.3.1
 * @code command  ::= letter { letter } | number number number
 */
class MessageCommand {
public:
	MessageCommand(std::string::iterator &it, const std::string::iterator &end);
	~MessageCommand();

	std::string			letters;
	int					numbers;
	MessageCommandEnum	cmdType;
private:
	std::string			getLettersOrSetNumbers(std::string::iterator &it, const std::string::iterator &end);
	MessageCommandEnum	str2enum(std::string &string);
	MessageCommand();
};
