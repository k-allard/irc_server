//
// Created by Anastasia on 14.06.2021.
//

#include "../includes/MessagePrefix.hpp"

/**
 * @b Format (BNF):
 *
 * @code
 * message    ::= [':' <b>prefix SPACE</b> ] command params crlf
 * prefix     ::= servername | nick [ '!' user ] [ '@' host ]
 * SPACE      ::= ' ' { ' ' }
 * servername ::= host
 * host       ::= see RFC 952 [DNS:4] for details on allowed hostnames
 * nick       ::= letter { letter | number | special }
 * letter     ::= 'a' ... 'z' | 'A' ... 'Z'
 * number     ::= '0' ... '9'
 * special    ::= '-' | '[' | ']' | '\' | '`' | '^' | '{' | '}'
 *
 * @param it
 * @param end
 */
MessagePrefix::MessagePrefix(std::string::iterator &it, const std::string::iterator &end)
{
	if(it < end && *it == ':')
	{

	} else {
		this->nick = "";
		this->user = "";
		this->host = "";
	}
}
