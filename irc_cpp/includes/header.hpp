#pragma once



#include <iostream>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h> //для sockaddr_in
#include <unistd.h>
#include <cstdlib>      // for atoi
#include <set>          // for std::set
#include <map>          // for std::map
#include <vector>
#include <algorithm>    // for std::max
#include <utility>
#include <string>
#include <sstream>
#include <queue>

// Для Linux
#include <cstdio>
#include <cstring>

class MessageCommand;
class MessageParams;
class MessagePrefix;
class Message;

class Parser;
class Client;
class Cmds;
class Server;

#include "MessageCommandEnum.hpp"
#include "MessageCommand.hpp"
#include "MessageParams.hpp"
#include "MessagePrefix.hpp"
#include "Message.hpp"

#include "Parser.hpp"
#include "Client.hpp"
#include "Cmds.hpp"
#include "Server.hpp"

// std::string G_CMDS[12] = {"NICK", "PASS", "JOIN", "QUIT", "PART", "MOTD", "PRIVMSG", "MODE", "KICK", "LUSER", "USER", "USERS" };
