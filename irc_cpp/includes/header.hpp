#pragma once

#include <iostream>
#include <fcntl.h>
#include <sys/socket.h> 
#include <netinet/in.h> //для sockaddr_in
#include <unistd.h> 
#include <cstdlib>      // for atoi
#include <set>          // for std::set
#include <algorithm>    // for std::max