//
// Created by Anastasia on 14.06.2021.
//

#pragma once
#include "header.hpp"

/**
 * @a https://datatracker.ietf.org/doc/html/rfc1459#section-2.3.1
 * @code command  ::= letter { letter } | number number number
 */
class MessageCommand {
public:

	MessageCommand(int numbers);
	MessageCommand(std::string::const_iterator &it, const std::string::const_iterator &end);
	MessageCommand(std::string string);
	MessageCommand(char *string);
	~MessageCommand();

	std::string letters;
	int numbers;
	MessageCommandEnum cmdType;
private:
	std::string getLetters(std::string::const_iterator &it, const std::string::const_iterator &end);
	MessageCommandEnum str2enum(std::string &string);

};
