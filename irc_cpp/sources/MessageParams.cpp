//
// Created by Anastasia on 14.06.2021.
//

#include "../includes/MessageParams.hpp"

/**
 *
 * @code
 * message  ::= [':' prefix SPACE ] command <b><u>params</u></b> crlf
 * params   ::= SPACE [ ':' trailing | middle params ]
 * SPACE    ::= ' ' { ' ' }
 * middle   ::= Any *non-empty* sequence of octets
 *              not including SPACE or NUL or CR or LF,
 *              the first of which may not be ':'
 * trailing ::= Any, possibly *empty*, sequence of octets
 *              not including NUL or CR or LF
 * crlf     ::= CR LF
 *
 * @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-2.3.1">2.3.1 Message format in 'pseudo' BNF</A>
 */

MessageParams::MessageParams(std::string::const_iterator &it, const std::string::const_iterator &end)
{
	std::string str(it, end);
	std::istringstream stream(str);
	std::string tmp;
	while (std::getline(stream, tmp, ' ')) {
		if(tmp.empty())
			continue;
		//tmp.erase(tmp.size() - 1, 1);
		this->Params.push_back(tmp);
	}
}

std::string MessageParams::toString() {
	// print something from v to str, e.g: Str << v.getX();
	std::string str("");

	for (std::vector<std::string>::const_iterator i = this->Params.begin(); i != this->Params.end(); ++i)
	{
		str += *i;
		if(i + 1 < this->Params.end())
			str += " ";
	}
	return str;
}
