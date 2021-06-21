#include "../includes/header.hpp"
#include "../includes/Server.hpp"

int main(int argc, char **argv) {
	if (argc != 3 && argc != 4) {
		std::cout << "Error! Usage ./ircserv <port> <password>\n";
		exit(1); 
	}
	if (argc == 4) {
		Server server(std::atoi(argv[2]), argv[3]);
		server.mainLoop();
	}
	else {
		Server server(std::atoi(argv[1]), argv[2]);
		server.mainLoop();		
	}
	return 0;
}
