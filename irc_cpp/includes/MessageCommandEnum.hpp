//
// Created by Anastasia on 14.06.2021.
//
#pragma once

enum MessageCommandEnum {
	///	@section Connection/Registration
	/// @return ERR_NEEDMOREPARAMS
	/// @return ERR_ALREADYREGISTRED
	/// @example PASS secretpasswordhere
	/// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.1">4.1.1 Password message</A>
	MsgCmd_PASS,

	///	@section Connection/Registration
	/// @return ERR_NONICKNAMEGIVEN
	/// @return ERR_ERRONEUSNICKNAME
	/// @return ERR_NICKNAMEINUSE
	/// @return ERR_NICKCOLLISION
	/// @example
	/// NICK Wiz                        ; Introducing new nick "Wiz".
	/// @example
	/// :WiZ NICK Kilroy                ; WiZ changed his nickname to Kilroy.
	/// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.2">4.1.2 Nick message</A>
	MsgCmd_NICK,

	///	@section Connection/Registration
	/// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.3">4.1.3 User message</A>
	MsgCmd_USER,

	///	@section Connection/Registration
	/// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.4">4.1.4 Server message</A>
	MsgCmd_SERVER,

	///	@section Connection/Registration
	/// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.5">4.1.5 Oper</A>
	MsgCmd_OPER,

	///	@section Connection/Registration
	/// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.6">4.1.6 Quit</A>
	MsgCmd_QUIT,

	///	@section Connection/Registration
	/// @param server
	/// @param comment
	/// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.7">4.1.7 Server quit message</A>
	MsgCmd_SQUIT,

	// Channel Operations

	// Server queries and commands

	// Sending messages

	// User-based queries

	// Miscellaneous messages

	MsgCmd_JOIN,
	MsgCmd_MSG,
	MsgCmd_PRIVMSG,
	MsgCmd_LIST,
	MsgCmd_USERS,
	MsgCmd_MOTD,
	MsgCmd_LUSER,
	MsgCmd_PART,
	MsgCmd_PING,
	MsgCmd_PONG,

	MsgCmd__NUMBER,
	MsgCmd__UNKNOWN
};
