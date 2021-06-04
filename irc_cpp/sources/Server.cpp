#include "../includes/Server.hpp"
#include "header.hpp"

Server::~Server() {

}

void Server::initFd() { 
    if ((_server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
		perror("socket");
		exit(2);
	}
	fcntl(_server_fd, F_SETFL, O_NONBLOCK);  // устанавливается неблокирующий доступ к фд

	//Инициализация структуры с адресом
	memset((char *)&address, 0, sizeof(address)); 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(PORT);

	// bind - Связать сокет с IP-адресом и портом
	if (bind(_server_fd,(struct sockaddr *)&address,sizeof(address)) < 0) { 
		perror("bind");
		exit(3);
	}

	//listen - Объявить о желании принимать соединения. Слушает порт и ждет когда будет установлено соединение
	if (listen(_server_fd, 10) < 0) { // 10 - максимальное количество соединений, которые могут быть поставлены в очередь
		perror("listen");
		exit(4);
	}
}

void Server::doSelect() { 

}

void Server::checkFd() { 

}

