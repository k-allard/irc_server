# IRC server in C++

:star: Functions to use:

Everything in C++ 98,  
`socket`,  
`setsockopt`,  
`getsockname`,  
`getprotobyname`,  
`gethostbyname`,  
`getaddrinfo`,  
`freeaddrinfo`,  
`bind`,  
`connect`,  
`listen`,  
`accept`,  
`htons`,   
`htonl`,  
`ntohs`,  
`ntohl`,  
`inet_addr`,  
`inet_ntoa`,  
`send`,  
`recv`,  
`signal`,  
`lseek`,  
`fstat`,  
`fcntl` (only `fcntl(fd, F_SETFL, O_NONBLOCK)`),  
`poll` (or equivalent like `select`, `kqueue`, `epoll`) 

:star: It is forbidden to `read`/`recv` or `write`/`send` in any FD without going through a `poll` (or equivalent)

:star: Communication between client and server must be done via `TCP/IP`(v4) or (v6)

:star: Executable will be used as follows:  
**```./ircserv [host:port_network:password_network] <port> <password>```**
- `host` is the hostname on which IRC must connect to join a already existing network
- `port_network` is the server port on which IRC must connect on host
- `password_network` is the password needed to connect on host
- `port` is the port number on which your server will accept incoming connections
- `password` is the password needed by any IRC client who wants to connect to your server
- If `host`, `port_network` and `password_network` aren’t given, you must create **a new IRC network**

:star: The server must be capable of handling **multiple clients at the same time** and never hang. Forking is not allowed, all I/O operations must be non blocking and use only 1 poll (or equivalent) for all (read, write, but also listen, ...)

:star: ERROR HANDLING! Verify absolutely every error and in cases where you might have a problem (partial data received, low bandwidth...)

:star: **No** need to code a client or to handle server to server communication

:star: Using the client on your server must be like using it on any official IRC server but to be sure we will list **the minimal required features**:

• to connect the reference client to your server without producing any error

• to authenticate, set a nickname, a username, join a channel, send and receive private messages using this client

• all messages from one client on a channel are sent to all other clients of the channel

• to have operators and regular users

• to have some operator’s specific actions/commands

:star: Documentation:  
https://tools.ietf.org/html/rfc1459  (на русском - https://ircnet.ru/rfc1459.html)  
https://tools.ietf.org/html/rfc2810  
https://tools.ietf.org/html/rfc2811  
https://tools.ietf.org/html/rfc2812  
https://tools.ietf.org/html/rfc2813  
https://tools.ietf.org/html/rfc7194  

:star: Useful links:

*socket programming:*
- https://www.geeksforgeeks.org/socket-programming-cc/  
- https://www.bogotobogo.com/cplusplus/sockets_server_client.php

*irc:*
- https://www.irchelp.org/protocol/rfc/
- https://ru.wikipedia.org/wiki/Список_IRC-команд
- 
