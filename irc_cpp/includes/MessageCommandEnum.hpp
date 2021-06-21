//
// Created by Anastasia on 14.06.2021.
//
#pragma once

enum MessageCommandEnum {
	///	@section Connection/Registration
	/// @return ERR_NEEDMOREPARAMS
	/// @return ERR_ALREADYREGISTRED
	/// @example PASS secretpasswordhere
	/// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.1">4.1.1</A> Password message
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
	/// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.2">4.1.2</A> Nick message
	MsgCmd_NICK,

	///	@section Connection/Registration
	/// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.3">4.1.3</A> User message
	MsgCmd_USER,

	///	@section Connection/Registration
	/// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.4">4.1.4</A> Server message
	MsgCmd_SERVER,

	///	@section Connection/Registration
	/// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.5">4.1.5</A> Oper
	MsgCmd_OPER,

	///	@section Connection/Registration
	/// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.6">4.1.6</A> Quit
	MsgCmd_QUIT,

	///	@section Connection/Registration
	/// @param server
	/// @param comment
	/// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.7">4.1.7</A> Server quit message
	MsgCmd_SQUIT,

	// Channel Operations

	/// @section Channel Operations
	/// @param channel[,channel,...]
	/// @param [key,key,...]
    /// @return ERR_NEEDMOREPARAMS
    /// @return ERR_INVITEONLYCHAN
    /// @return ERR_CHANNELISFULL
    /// @return ERR_NOSUCHCHANNEL
    /// @return ERR_BANNEDFROMCHAN
    /// @return ERR_BADCHANNELKEY
    /// @return ERR_BADCHANMASK
    /// @return ERR_TOOMANYCHANNELS
    /// @return RPL_TOPIC
    /// @example JOIN #foobar                    ; join channel #foobar.
    /// @example JOIN &foo fubar                 ; join channel &foo using key "fubar".
    /// @example JOIN #foo,&bar fubar            ; join channel #foo using key "fubar" and &bar using no key.
    /// @example JOIN #foo,#bar fubar,foobar     ; join channel #foo using key "fubar". and channel #bar using key "foobar".
    /// @example JOIN #foo,#bar                  ; join channels #foo and #bar.
    /// @example :WiZ JOIN #Twilight_zone        ; JOIN message from WiZ
	/// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.1">4.2.1</A> Join message
    MsgCmd_JOIN,

    /// @section Channel Operations
    /// @param channel{,channel,...}
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.2">4.2.2</A> Part message
    MsgCmd_PART,

    /// @section Channel Operations
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.3">4.2.3</A> Mode message
    MsgCmd_MODE,

    /// @section Channel Operations
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.4">4.2.4</A> Topic message
    MsgCmd_TOPIC,

    /// @section Channel Operations
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.5">4.2.5</A> Names message
    MsgCmd_NAMES,

    /// @section Channel Operations
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.6">4.2.6</A> List message
    MsgCmd_LIST,

    /// @section Channel Operations
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.7">4.2.7</A> Invite message
    MsgCmd_INVITE,

    /// @section Channel Operations
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.2.8">4.2.8</A> Kick message
    MsgCmd_KICK,

	// Server queries and commands
	/// @section Server queries and commands
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.3.1">4.3.1</A> Version message
    MsgCmd_VERSION,

    /// @section Server queries and commands
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.3.2">4.3.2</A> Stats message
    MsgCmd_STATS,

    /// @section Server queries and commands
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.3.3">4.3.3</A> Links message
    MsgCmd_LINKS,

    /// @section Server queries and commands
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.3.4">4.3.4</A> Time message
    MsgCmd_TIME,

    /// @section Server queries and commands
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.3.5">4.3.5</A> Connect message
    MsgCmd_CONNECT,

    /// @section Server queries and commands
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.3.6">4.3.6</A> Trace message
    MsgCmd_TRACE,

    /// @section Server queries and commands
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.3.7">4.3.7</A> Admin command
    MsgCmd_ADMIN,

    /// @section Server queries and commands
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.3.8">4.3.8</A> Info command
    MsgCmd_INFO,

	// 4.4 Sending messages

	/// @section Sending messages
	/// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.4.1">4.4.1</A> Private messages
	MsgCmd_PRIVMSG,

    /// @section Sending messages
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.4.2">4.4.2</A> Notice
	MsgCmd_NOTICE,

	// 4.5 User based queries
    /// @section User based queries
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.5.1">4.5.1</A> Who query
	MsgCmd_WHO,

    /// @section User based queries
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.5.2">4.5.2</A> Whois query
    MsgCmd_WHOIS,

    /// @section User based queries
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.5.3">4.5.3</A> Whowas
    MsgCmd_WHOWAS,

	// 4.6 Miscellaneous messages

    /// @section User based queries
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.6.1">4.6.1</A> Kill message
    MsgCmd_KILL,

    /// @section User based queries
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.6.2">4.6.2</A> Ping message
    MsgCmd_PING,

    /// @section User based queries
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.6.3">4.6.3</A> Pong message
    MsgCmd_PONG,

    /// @section User based queries
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-4.6.4">4.6.4</A> Error
    MsgCmd_ERROR,

    //5. OPTIONALS

    /// @section OPTIONALS
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-5.1">5.1</A> Away
    MsgCmd_AWAY,

    /// @section OPTIONALS
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-5.2">5.2</A> Rehash message
    MsgCmd_REHASH,

    /// @section OPTIONALS
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-5.3">5.3</A> Restart message
    MsgCmd_RESTART,

    /// @section OPTIONALS
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-5.4">5.4</A> Summon message
    MsgCmd_SUMMON,

    /// @section OPTIONALS
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-5.5">5.5</A> Users
    MsgCmd_USERS,

    /// @section OPTIONALS
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-5.6">5.6</A> Operwall message
    MsgCmd_WALLOPS,

    /// @section OPTIONALS
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-5.7">5.7</A> Userhost message
    MsgCmd_USERHOST,

    /// @section OPTIONALS
    /// @see <A HREF="https://datatracker.ietf.org/doc/html/rfc1459#section-5.8">5.8</A> Ison message
    MsgCmd_ISON,

    // OTHER

	MsgCmd_MSG,
	MsgCmd_MOTD,
	MsgCmd_LUSERS,

    // INTERNAL

    /// @section INTERNAL
	MsgCmd__NUMBER,


    /// @section INTERNAL
    /// Неизвестная команда
	MsgCmd__UNKNOWN
};
