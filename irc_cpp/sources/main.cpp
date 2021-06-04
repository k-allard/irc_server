#include "../includes/header.hpp"
#include "../includes/Server.hpp"

int main(int argc, char **argv) {
	if (argc != 3) {
		std::cout << "Error! Usage ./ircserv <port> <password>\n";
		exit(1); 
	}
	Server server(std::atoi(argv[1]), argv[2]);
	server.mainLoop();
	return 0;
}
