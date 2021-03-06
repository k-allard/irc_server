#pragma once

#include <iostream>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h> // for sockaddr_in
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

// for Linux
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
class Channel;

#include "MessageCommandEnum.hpp"
#include "MessageCommand.hpp"
#include "MessageParams.hpp"
#include "MessagePrefix.hpp"
#include "Message.hpp"
#include "Parser.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "Channel.hpp"
