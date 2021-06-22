#pragma once

#include "header.hpp"

/**
 * @a https://datatracker.ietf.org/doc/html/rfc1459#section-2.3.1
 * @code prefix ::= servername | nick [ '!' user ] [ '@' host ]
 */
class MessagePrefix {
public:
	std::string nick;
	std::string user;
	std::string host;

	MessagePrefix(std::string::iterator &it, const std::string::iterator &end);
    ~MessagePrefix();
};
