#pragma once
// ****** FOR  TESTING!!!!!! ****** //
#define RPL_TESTING                 000 //"This server was created <date>"
#define RPL_TESTING_MSG             ":Hello! Your socket is #<id>. This server is created by <authors>"
// ADD TO TEST:	return setReply(fd, RPL_TESTING, RPL_TESTING_MSG, "unkown", "mmaida, kallard and tolya"); //
// ****** ****************** ****** //


#define RPL_WELCOME                 "001"
#define RPL_WELCOME_MSG             ":Welcome to the Internet Relay Network <prefix>"

#define RPL_YOURHOST                "002" //"Your host is <servername>, running version <ver>"
#define RPL_YOURHOST_MSG            ":Your host is ircserv.net, running version 1.0"

#define RPL_CREATED                 "003" //"This server was created <date>"
#define RPL_CREATED_MSG             ":This server was created <date>"

#define RPL_MYINFO                  "004" //"<servername> <version> <available user modes> <available channel modes>"
#define RPL_MYINFO_MSG              ":ircserv.net 1.0 o o"

//- The server sends Replies 001 to 004 to a user upon
//successful registration.

#define ERR_NOSUCHNICK				"401" //"<nickname> :No such nick/channel"
#define ERR_NOSUCHNICK_MSG			"<nickname> :No such nick/channel"
									//- Used to indicate the nickname parameter supplied to a
									// command is currently unused.

//#define ERR_NOSUCHSERVER			402 //"<server name> :No such server"
									//- Used to indicate the server name given currently
									// doesn't exist.

#define ERR_NOSUCHCHANNEL	403 
#define ERR_NOSUCHCHANNEL_MSG "<channel name> :No such channel"
									//- Used to indicate the given channel name is invalid.

#define ERR_CANNOTSENDTOCHAN		"404" //"<channel name> :Cannot send to channel"
#define ERR_CANNOTSENDTOCHAN_MSG     "<channel name> :Cannot send to channel"
									//- Sent to a user who is either (a) not on a channelnullptr
									// which is mode +n or (b) not a chanop (or mode +v) on
									// a channel which has mode +m set and is trying to send
									// a PRIVMSG message to that channel.

//#define ERR_TOOMANYCHANNELS			405 //"<channel name> :You have joined too many channels"
									//- Sent to a user when they have joined the maximum
									// number of allowed channels and they try to join
									// another channel.

// #define         406     ERR_WASNOSUCHNICK //"<nickname> :There was no such nickname"
//                 - Returned by WHOWAS to indicate there is no history
//                   information for that nickname.

// #define         407     ERR_TOOMANYTARGETS //"<target> :Duplicate recipients. No message delivered"
//                 - Returned to a client which is attempting to send a
//                   PRIVMSG/NOTICE using the user@host destination format
//                   and for a user@host which has several occurrences.

// #define         409     ERR_NOORIGIN //":No origin specified"
//                 - PING or PONG message missing the originator parameter
//                   which is required since these commands must work
//                   without valid prefixes.

#define ERR_NORECIPIENT "411"      // ":No recipient given (<command>)"
#define ERR_NORECIPIENT_MSG ":No recipient given (<command>)"
#define ERR_NOTEXTTOSEND "412" // ":No text to send"
#define ERR_NOTEXTTOSEND_MSG ":No text to send"
// #define         413     ERR_NOTOPLEVEL // "<mask> :No toplevel domain specified"
// #define         414     ERR_WILDTOPLEVEL // "<mask> :Wildcard in toplevel domain"

//                 - 412 - 414 are returned by PRIVMSG to indicate that
//                   the message wasn't delivered for some reason.
//                   ERR_NOTOPLEVEL and ERR_WILDTOPLEVEL are errors that
//                   are returned when an invalid use of
//                   "PRIVMSG $<server>" or "PRIVMSG #<host>" is attempted.

#define ERR_UNKNOWNCOMMAND				"421" // "<command> :Unknown command"
#define ERR_UNKNOWNCOMMAND_MSG			"<command> :Unknown command"
//                 - Returned to a registered client to indicate that the
//                   command sent is unknown by the server.

// #define         422     ERR_NOMOTD // ":MOTD File is missing"
//                 - Server's MOTD file could not be opened by the server.

// #define         423     ERR_NOADMININFO // "<server> :No administrative info available"
//                 - Returned by a server in response to an ADMIN message
//                   when there is an error in finding the appropriate
//                   information.

// #define         424     ERR_FILEERROR // ":File error doing <file op> on <file>"
//                 - Generic error message used to report a failed file
//                   operation during the processing of a message.

#define ERR_NONICKNAMEGIVEN				"431" // ":No nickname given"
#define ERR_NONICKNAMEGIVEN_MSG			":No nickname given"
//                 - Returned when a nickname parameter expected for a
//                   command and isn't found.

#define ERR_ERRONEUSNICKNAME			"432"// "<nick> :Erroneus nickname"
#define ERR_ERRONEUSNICKNAME_MSG		"<nick> :Erroneus nickname"
//                 - Returned after receiving a NICK message which contains
//                   characters which do not fall in the defined set.  See
//                   section x.x.x for details on valid nicknames.

#define  ERR_NICKNAMEINUSE				"433"// "<nick> :Nickname is already in use"
#define  ERR_NICKNAMEINUSE_MSG			"<nick> :Nickname is already in use"
//                 - Returned when a NICK message is processed that results
//                   in an attempt to change to a currently existing
//                   nickname.

// #define         436     ERR_NICKCOLLISION // "<nick> :Nickname collision KILL"
//                 - Returned by a server to a client when it detects a
//                   nickname collision (registered of a NICK that
//                   already exists by another server).

// #define         441     ERR_USERNOTINCHANNEL // "<nick> <channel> :They aren't on that channel"
//                 - Returned by the server to indicate that the target
//                   user of the command is not on the given channel.

#define         ERR_NOTONCHANNEL 442   
#define ERR_NOTONCHANNEL_MSG "<channel> :You're not on that channel"

//                 - Returned by the server whenever a client tries to
//                   perform a channel effecting command for which the
//                   client isn't a member.

 #define              ERR_USERONCHANNEL "443"
 #define              ERR_USERONCHANNEL_MSG "<user> <channel> :is already on channel"
//                 - Returned when a client tries to invite a user to a
//                   channel they are already on.

// #define         444     ERR_NOLOGIN // "<user> :User not logged in"
//                 - Returned by the summon after a SUMMON command for a
//                   user was unable to be performed since they were not
//                   logged in.

// #define         445     ERR_SUMMONDISABLED // ":SUMMON has been disabled"
//                 - Returned as a response to the SUMMON command.  Must be
//                   returned by any server which does not implement it.

// #define         446     ERR_USERSDISABLED // ":USERS has been disabled"
//                 - Returned as a response to the USERS command.  Must be
//                   returned by any server which does not implement it.

#define    ERR_NOTREGISTERED     "451"      // ":You have not registered"
#define		ERR_NOTREGISTERED_MSG ":You have not registered"
//                 - Returned by the server to indicate that the client
//                   must be registered before the server will allow it
//                   to be parsed in detail.

#define     ERR_NEEDMOREPARAMS    "461"      //"<command> :Not enough parameters"
#define     ERR_NEEDMOREPARAMS_MSG "<command> :Not enough parameters"
//                 - Returned by the server by numerous commands to
//                   indicate to the client that it didn't supply enough
//                   parameters.

#define    ERR_ALREADYREGISTRED    "462"     // ":You may not reregister"
#define    ERR_ALREADYREGISTRED_MSG  ":You may not reregister"
//                 - Returned by the server to any link which tries to
//                   change part of the registered details (such as
//                   password or user details from second USER message).

// #define         463     ERR_NOPERMFORHOST // ":Your host isn't among the privileged"
//                 - Returned to a client which attempts to register with
//                   a server which does not been setup to allow
//                   connections from the host the attempted connection
//                   is tried.

// #define         464     ERR_PASSWDMISMATCH // ":Password incorrect"
//                 - Returned to indicate a failed attempt at registering
//                   a connection for which a password was required and
//                   was either not given or incorrect.

// #define         465     ERR_YOUREBANNEDCREEP // ":You are banned from this server"
//                 - Returned after an attempt to connect and register
//                   yourself with a server which has been setup to
//                   explicitly deny connections to you.

// #define         467     ERR_KEYSET // "<channel> :Channel key already set"
// #define         471     ERR_CHANNELISFULL //"<channel> :Cannot join channel (+l)"
// #define         472     ERR_UNKNOWNMODE // "<char> :is unknown mode char to me"
// #define         473     ERR_INVITEONLYCHAN // "<channel> :Cannot join channel (+i)"
// #define         474     ERR_BANNEDFROMCHAN // "<channel> :Cannot join channel (+b)"
 #define              ERR_BADCHANNELKEY "475"
#define              ERR_BADCHANNELKEY_MSG "<channel> :Cannot join channel (+k)"
// #define         481     ERR_NOPRIVILEGES // ":Permission Denied- You're not an IRC operator"
//                 - Any command requiring operator privileges to operate
//                   must return this error to indicate the attempt was
//                   unsuccessful.

// #define         482     ERR_CHANOPRIVSNEEDED // "<channel> :You're not channel operator"
//                 - Any command requiring 'chanop' privileges (such as
//                   MODE messages) must return this error if the client
//                   making the attempt is not a chanop on the specified
//                   channel.

// #define        483     ERR_CANTKILLSERVER // ":You cant kill a server!"
//                 - Any attempts to use the KILL command on a server
//                   are to be refused and this error returned directly
//                   to the client.

// #define         491     ERR_NOOPERHOST // ":No O-lines for your host"
//                 - If a client sends an OPER message and the server has
//                   not been configured to allow connections from the
//                   client's host as an operator, this error must be
//                   returned.

// #define         501     ERR_UMODEUNKNOWNFLAG // ":Unknown MODE flag"
//                 - Returned by the server to indicate that a MODE
//                   message was sent with a nickname parameter and that
//                   the a mode flag sent was not recognized.

// #define         502     ERR_USERSDONTMATCH // ":Cant change mode for other users"
//                 - Error sent to any user trying to view or change the
//                   user mode for a user other than themselves.

// #define         300     RPL_NONE
//                         Dummy reply number. Not used.

// #define         302     RPL_USERHOST // ":[<reply>{<space><reply>}]"
//                 - Reply format used by USERHOST to list replies to
//                   the query list.  The reply string is composed as
//                   follows:
//                   <reply> ::= <nick>['*'] '=' <'+'|'-'><hostname>
//                   The '*' indicates whether the client has registered
//                   as an Operator.  The '-' or '+' characters represent
//                   whether the client has set an AWAY message or not
//                   respectively.

// #define         303     RPL_ISON // ":[<nick> {<space><nick>}]"
//                 - Reply format used by ISON to list replies to the
//                   query list.

// #define         301     RPL_AWAY // "<nick> :<away message>"
// #define         305     RPL_UNAWAY // ":You are no longer marked as being away"
// #define         306     RPL_NOWAWAY // ":You have been marked as being away"

//                 - These replies are used with the AWAY command (if
//                   allowed).  RPL_AWAY is sent to any client sending a
//                   PRIVMSG to a client which is away.  RPL_AWAY is only
//                   sent by the server to which the client is connected.
//                   Replies RPL_UNAWAY and RPL_NOWAWAY are sent when the
//                   client removes and sets an AWAY message.

// #define         311     RPL_WHOISUSER // "<nick> <user> <host> * :<real name>"
// #define         312     RPL_WHOISSERVER // "<nick> <server> :<server info>"
// #define         313     RPL_WHOISOPERATOR // "<nick> :is an IRC operator"
// #define         317     RPL_WHOISIDLE
//                         "<nick> <integer> :seconds idle"
// #define         318     RPL_ENDOFWHOIS
//                         "<nick> :End of /WHOIS list"
// #define         319     RPL_WHOISCHANNELS
//                         "<nick> :{[@|+]<channel><space>}"

//                 - Replies 311 - 313, 317 - 319 are all replies
//                   generated in response to a WHOIS message.  Given that
//                   there are enough parameters present, the answering
//                   server must either formulate a reply out of the above
//                   numerics (if the query nick is found) or return an
//                   error reply.  The '*' in RPL_WHOISUSER is there as
//                   the literal character and not as a wild card.  For
//                   each reply set, only RPL_WHOISCHANNELS may appear
//                   more than once (for long lists of channel names).
//                   The '@' and '+' characters next to the channel name
//                   indicate whether a client is a channel operator or
//                   has been granted permission to speak on a moderated
//                   channel.  The RPL_ENDOFWHOIS reply is used to mark
//                   the end of processing a WHOIS message.

// #define         314     RPL_WHOWASUSER
//                         "<nick> <user> <host> * :<real name>"
// #define         369     RPL_ENDOFWHOWAS
//                         "<nick> :End of WHOWAS"

//                 - When replying to a WHOWAS message, a server must use
//                   the replies RPL_WHOWASUSER, RPL_WHOISSERVER or
//                   ERR_WASNOSUCHNICK for each nickname in the presented

//                   list.  At the end of all reply batches, there must
//                   be RPL_ENDOFWHOWAS (even if there was only one reply
//                   and it was an error).

// #define         321     RPL_LISTSTART
//                         "Channel :Users  Name"
#define             RPL_LIST  "322"
#define             RPL_LIST_MSG "<channel> # visible :<topic>"
#define           RPL_LISTEND "323"
#define           RPL_LISTEND_MSG ":End of /LIST"

//                 - Replies RPL_LISTSTART, RPL_LIST, RPL_LISTEND mark
//                   the start, actual replies with data and end of the
//                   server's response to a LIST command.  If there are
//                   no channels available to return, only the start
//                   and end reply must be sent.

// #define         324     RPL_CHANNELMODEIS
//                         "<channel> <mode> <mode params>"

// #define         331     RPL_NOTOPIC
//                         "<channel> :No topic is set"
 #define             RPL_TOPIC "332"
#define              RPL_TOPIC_MSG  "<channel> :<topic>"

//                 - When sending a TOPIC message to determine the
//                   channel topic, one of two replies is sent.  If
//                   the topic is set, RPL_TOPIC is sent back else
//                   RPL_NOTOPIC.

// #define         341     RPL_INVITING
//                         "<channel> <nick>"

//                 - Returned by the server to indicate that the
//                   attempted INVITE message was successful and is
//                   being passed onto the end client.

// #define         342     RPL_SUMMONING
//                         "<user> :Summoning user to IRC"

//                 - Returned by a server answering a SUMMON message to
//                   indicate that it is summoning that user.

// #define         351     RPL_VERSION
//                         "<version>.<debuglevel> <server> :<comments>"

//                 - Reply by the server showing its version details.
//                   The <version> is the version of the software being

//                   used (including any patchlevel revisions) and the
//                   <debuglevel> is used to indicate if the server is
//                   running in "debug mode".

//                   The "comments" field may contain any comments about
//                   the version or further version details.

// #define         352     RPL_WHOREPLY
//                         "<channel> <user> <host> <server> <nick> 
//                          <H|G>[*][@|+] :<hopcount> <real name>"
// #define         315     RPL_ENDOFWHO
//                         "<name> :End of /WHO list"

//                 - The RPL_WHOREPLY and RPL_ENDOFWHO pair are used
//                   to answer a WHO message.  The RPL_WHOREPLY is only
//                   sent if there is an appropriate match to the WHO
//                   query.  If there is a list of parameters supplied
//                   with a WHO message, a RPL_ENDOFWHO must be sent
//                   after processing each list item with <name> being
//                   the item.

 #define               RPL_NAMREPLY "353"
#define              RPL_NAMREPLY_MSG    "<channel> :<names>"

 #define              RPL_ENDOFNAMES "366"
#define 				RPL_ENDOFNAMES_MSG ":End of /NAMES list"

//                 - To reply to a NAMES message, a reply pair consisting
//                   of RPL_NAMREPLY and RPL_ENDOFNAMES is sent by the
//                   server back to the client.  If there is no channel
//                   found as in the query, then only RPL_ENDOFNAMES is
//                   returned.  The exception to this is when a NAMES
//                   message is sent with no parameters and all visible
//                   channels and contents are sent back in a series of
//                   RPL_NAMEREPLY messages with a RPL_ENDOFNAMES to mark
//                   the end.

// #define         364     RPL_LINKS
//                         "<mask> <server> :<hopcount> <server info>"
// #define         365     RPL_ENDOFLINKS
//                         "<mask> :End of /LINKS list"

//                 - In replying to the LINKS message, a server must send
//                   replies back using the RPL_LINKS numeric and mark the
//                   end of the list using an RPL_ENDOFLINKS reply.

// #define         367     RPL_BANLIST
//                         "<channel> <banid>"
// #define         368     RPL_ENDOFBANLIST
//                         "<channel> :End of channel ban list"

//                 - When listing the active 'bans' for a given channel,
//                   a server is required to send the list back using the
//                   RPL_BANLIST and RPL_ENDOFBANLIST messages.  A separate
//                   RPL_BANLIST is sent for each active banid.  After the
//                   banids have been listed (or if none present) a
//                   RPL_ENDOFBANLIST must be sent.

// #define         371     RPL_INFO
//                         ":<string>"
// #define         374     RPL_ENDOFINFO
//                         ":End of /INFO list"

//                 - A server responding to an INFO message is required to
//                   send all its 'info' in a series of RPL_INFO messages
//                   with a RPL_ENDOFINFO reply to indicate the end of the
//                   replies.

// #define         375     RPL_MOTDSTART
//                         ":- <server> Message of the day - "
// #define         372     RPL_MOTD
//                         ":- <text>"
// #define         376     RPL_ENDOFMOTD
//                         ":End of /MOTD command"

//                 - When responding to the MOTD message and the MOTD file
//                   is found, the file is displayed line by line, with
//                   each line no longer than 80 characters, using
//                   RPL_MOTD format replies.  These should be surrounded
//                   by a RPL_MOTDSTART (before the RPL_MOTDs) and an
//                   RPL_ENDOFMOTD (after).

// #define         381     RPL_YOUREOPER
//                         ":You are now an IRC operator"

//                 - RPL_YOUREOPER is sent back to a client which has
//                   just successfully issued an OPER message and gained
//                   operator status.

// #define         382     RPL_REHASHING
//                         "<config file> :Rehashing"

//                 - If the REHASH option is used and an operator sends
//                   a REHASH message, an RPL_REHASHING is sent back to
//                   the operator.

// #define         391     RPL_TIME

//                         "<server> :<string showing server's local time>"

//                 - When replying to the TIME message, a server must send
//                   the reply using the RPL_TIME format above.  The string
//                   showing the time need only contain the correct day and
//                   time there.  There is no further requirement for the
//                   time string.

// #define         392     RPL_USERSSTART
//                         ":UserID   Terminal  Host"
// #define         393     RPL_USERS
//                         ":%-8s %-9s %-8s"
// #define         394     RPL_ENDOFUSERS
//                         ":End of users"
// #define         395     RPL_NOUSERS
//                         ":Nobody logged in"

//                 - If the USERS message is handled by a server, the
//                   replies RPL_USERSTART, RPL_USERS, RPL_ENDOFUSERS and
//                   RPL_NOUSERS are used.  RPL_USERSSTART must be sent
//                   first, following by either a sequence of RPL_USERS
//                   or a single RPL_NOUSER.  Following this is
//                   RPL_ENDOFUSERS.

// #define         200     RPL_TRACELINK
//                         "Link <version & debug level> <destination> 
//                          <next server>"
// #define         201     RPL_TRACECONNECTING
//                         "Try. <class> <server>"
// #define         202     RPL_TRACEHANDSHAKE
//                         "H.S. <class> <server>"
// #define         203     RPL_TRACEUNKNOWN
//                         "???? <class> [<client IP address in dot form>]"
// #define         204     RPL_TRACEOPERATOR
//                         "Oper <class> <nick>"
// #define         205     RPL_TRACEUSER
//                         "User <class> <nick>"
// #define         206     RPL_TRACESERVER
//                         "Serv <class> <int>S <int>C <server> 
//                          <nick!user|*!*>@<host|server>"
// #define         208     RPL_TRACENEWTYPE
//                         "<newtype> 0 <client name>"
// #define         261     RPL_TRACELOG
//                         "File <logfile> <debug level>"

//                 - The RPL_TRACE* are all returned by the server in
//                   response to the TRACE message.  How many are
//                   returned is dependent on the the TRACE message and

//                   whether it was sent by an operator or not.  There
//                   is no predefined order for which occurs first.
//                   Replies RPL_TRACEUNKNOWN, RPL_TRACECONNECTING and
//                   RPL_TRACEHANDSHAKE are all used for connections
//                   which have not been fully established and are either
//                   unknown, still attempting to connect or in the
//                   process of completing the 'server handshake'.
//                   RPL_TRACELINK is sent by any server which handles
//                   a TRACE message and has to pass it on to another
//                   server.  The list of RPL_TRACELINKs sent in
//                   response to a TRACE command traversing the IRC
//                   network should reflect the actual connectivity of
//                   the servers themselves along that path.
//                   RPL_TRACENEWTYPE is to be used for any connection
//                   which does not fit in the other categories but is
//                   being displayed anyway.

// #define         211     RPL_STATSLINKINFO
//                         "<linkname> <sendq> <sent messages> 
//                          <sent bytes> <received messages> 
//                          <received bytes> <time open>"
// #define         212     RPL_STATSCOMMANDS
//                         "<command> <count>"
// #define         213     RPL_STATSCLINE
//                         "C <host> * <name> <port> <class>"
// #define         214     RPL_STATSNLINE
//                         "N <host> * <name> <port> <class>"
// #define         215     RPL_STATSILINE
//                         "I <host> * <host> <port> <class>"
// #define         216     RPL_STATSKLINE
//                         "K <host> * <username> <port> <class>"
// #define         218     RPL_STATSYLINE
//                         "Y <class> <ping frequency> <connect 
//                          frequency> <max sendq>"
// #define        219     RPL_ENDOFSTATS
//                         "<stats letter> :End of /STATS report"
// #define         241     RPL_STATSLLINE
//                         "L <hostmask> * <servername> <maxdepth>"
// #define         242     RPL_STATSUPTIME
//                         ":Server Up %d days %d:%02d:%02d"
// #define         243     RPL_STATSOLINE
//                         "O <hostmask> * <name>"
// #define         244     RPL_STATSHLINE
//                         "H <hostmask> * <servername>"

// #define         221     RPL_UMODEIS
//                         "<user mode string>"
//                         - To answer a query about a client's own mode,
//                           RPL_UMODEIS is sent back.

// #define         251     RPL_LUSERCLIENT
//                         ":There are <integer> users and <integer>
//                          invisible on <integer> servers"
// #define         252     RPL_LUSEROP
//                         "<integer> :operator(s) online"
// #define         253     RPL_LUSERUNKNOWN
//                         "<integer> :unknown connection(s)"
// #define         254     RPL_LUSERCHANNELS
//                         "<integer> :channels formed"
// #define         255     RPL_LUSERME
//                         ":I have <integer> clients and <integer>
//                           servers"

//                         - In processing an LUSERS message, the server
//                           sends a set of replies from RPL_LUSERCLIENT,
//                           RPL_LUSEROP, RPL_USERUNKNOWN,
//                           RPL_LUSERCHANNELS and RPL_LUSERME.  When
//                           replying, a server must send back
//                           RPL_LUSERCLIENT and RPL_LUSERME.  The other
//                           replies are only sent back if a non-zero count
//                           is found for them.

// #define         256     RPL_ADMINME
//                         "<server> :Administrative info"
// #define         257     RPL_ADMINLOC1
//                         ":<admin info>"
// #define         258     RPL_ADMINLOC2
//                         ":<admin info>"
// #define         259     RPL_ADMINEMAIL
//                         ":<admin info>"

//                         - When replying to an ADMIN message, a server
//                           is expected to use replies RLP_ADMINME
//                           through to RPL_ADMINEMAIL and provide a text
//                           message with each.  For RPL_ADMINLOC1 a
//                           description of what city, state and country
//                           the server is in is expected, followed by
//                           details of the university and department
//                           (RPL_ADMINLOC2) and finally the administrative
//                           contact for the server (an email address here
//                           is required) in RPL_ADMINEMAIL.
