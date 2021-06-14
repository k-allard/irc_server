//
// Created by Anastasia on 14.06.2021.
//
#pragma once
#include "header.hpp"

/**
 *
 * @code
 * message  ::= [':' prefix SPACE ] command params crlf
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
class MessageParams {
public:
	MessageParams() { };
};
