#pragma once

#define RPL_WELCOME					"001"
#define RPL_WELCOME_MSG				":Welcome to the Internet Relay Network <prefix>"

#define RPL_YOURHOST				"002"
#define RPL_YOURHOST_MSG			":Your host is <name>, running version 1.0"

#define RPL_CREATED					"003"
#define RPL_CREATED_MSG				":This server was created <date>"

#define RPL_MYINFO					"004"
#define RPL_MYINFO_MSG				":<name> 1.0 o o"

#define ERR_NOSUCHNICK				"401"
#define ERR_NOSUCHNICK_MSG			"<nickname> :No such nick/channel"


#define ERR_NOSUCHCHANNEL			"403"
#define ERR_NOSUCHCHANNEL_MSG		"<channel name> :No such channel"

#define ERR_CANNOTSENDTOCHAN		"404"
#define ERR_CANNOTSENDTOCHAN_MSG	"<channel name> :Cannot send to channel"

#define ERR_NORECIPIENT				"411"
#define ERR_NORECIPIENT_MSG			":No recipient given (<command>)"

#define ERR_NOTEXTTOSEND			"412"
#define ERR_NOTEXTTOSEND_MSG		":No text to send"

#define ERR_UNKNOWNCOMMAND			"421"
#define ERR_UNKNOWNCOMMAND_MSG		"<command> :Unknown command"

#define ERR_NONICKNAMEGIVEN			"431"
#define ERR_NONICKNAMEGIVEN_MSG		":No nickname given"


#define ERR_ERRONEUSNICKNAME		"432"
#define ERR_ERRONEUSNICKNAME_MSG	"<nick> :Erroneus nickname"


#define ERR_NICKNAMEINUSE			"433"
#define ERR_NICKNAMEINUSE_MSG		"<nick> :Nickname is already in use"

#define ERR_USERNOTINCHANNEL		"441"
#define ERR_USERNOTINCHANNEL_MSG	"<nick> <channel> :They aren't on that channel"

#define ERR_NOTONCHANNEL			"442"
#define ERR_NOTONCHANNEL_MSG		"<channel> :You're not on that channel"

#define ERR_USERONCHANNEL			"443"
#define ERR_USERONCHANNEL_MSG		"<user> <channel> :is already on channel"

#define ERR_NOTREGISTERED			"451"
#define ERR_NOTREGISTERED_MSG		":You have not registered"

#define ERR_NEEDMOREPARAMS   		"461"
#define ERR_NEEDMOREPARAMS_MSG		"<command> :Not enough parameters"

#define ERR_ALREADYREGISTRED		"462"
#define ERR_ALREADYREGISTRED_MSG	":You may not reregister"

#define ERR_BADCHANNELKEY			"475"
#define ERR_BADCHANNELKEY_MSG		"<channel> :Cannot join channel (+k)"

#define ERR_CHANOPRIVSNEEDED		"482"
#define ERR_CHANOPRIVSNEEDED_MSG	"<channel> :You're not channel operator"

#define ERR_USERSDONTMATCH			"502"
#define ERR_USERSDONTMATCH_MSG		":Cant change mode for other users"

#define RPL_WHOISUSER				"311"
#define RPL_WHOISUSER_MSG			"<nick user> <host> * :<real name>"

#define RPL_WHOISSERVER				"312"
#define RPL_WHOISSERVER_MSG			"<nick> <server> :IRC server"

#define RPL_ENDOFWHOIS				"318"
#define RPL_ENDOFWHOIS_MSG			"<nick> :End of /WHOIS list"

#define RPL_WHOISCHANNELS			"319"
#define RPL_WHOISCHANNELS_MSG		"<nick> :<{[@|+]channel space}>"

#define RPL_LISTSTART				"321"
#define RPL_LISTSTART_MSG			"Channel :Users  Name"

#define RPL_LIST					"322"
#define RPL_LIST_MSG				"<channel> <visible> :"

#define RPL_LISTEND					"323"
#define RPL_LISTEND_MSG				":End of /LIST"

#define RPL_NOTOPIC					"331"
#define RPL_NOTOPIC_MSG				"<channel> :No topic is set"

#define RPL_TOPIC					"332"
#define RPL_TOPIC_MSG				"<channel> :<topic>"

#define RPL_WHOREPLY				"352"
#define RPL_WHOREPLY_MSG			"<channel user server> 127.0.0.1 <nickH> :0 <real name>"

#define RPL_ENDOFWHO				"315"
#define RPL_ENDOFWHO_MSG			"<name> :End of /WHO list"

#define RPL_NAMREPLY				"353"
#define RPL_NAMREPLY_MSG			"= <channel> :<names>"

#define RPL_ENDOFNAMES				"366"
#define RPL_ENDOFNAMES_MSG			":End of /NAMES list"

#define RPL_MOTDSTART				"375"
#define RPL_MOTDSTART_MSG			":- <server> Message of the day - "

#define RPL_MOTD					"372"
#define RPL_MOTD_MSG				":- <text>"

#define RPL_ENDOFMOTD				"376"
#define RPL_ENDOFMOTD_MSG			":End of /MOTD command"

#define RPL_LUSERCLIENT				"251"
#define RPL_LUSERCLIENT_MSG			":There are <integer> users and <integer> invisible on <integer> servers"

#define RPL_LUSEROP					"252"
#define RPL_LUSEROP_MSG				"<integer> :operator(s) online"

#define RPL_LUSERUNKNOWN			"253"
#define RPL_LUSERUNKNOWN_MSG		"<integer> :unknown connection(s)"

#define RPL_LUSERCHANNELS			"254"
#define RPL_LUSERCHANNELS_MSG		"<integer> :channels formed"

#define RPL_LUSERME					"255"
#define RPL_LUSERME_MSG				":I have <integer> clients and <integer> servers"
