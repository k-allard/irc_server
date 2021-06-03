#include <iostream>
#include <fcntl.h>
#include <sys/socket.h> 
#include <netinet/in.h> //для sockaddr_in - используется для хранения адресов ipv4
#include <unistd.h> 
#include <cstdlib> // for atoi

int main(int argc, char **argv) {

	if(argc != 3) {
		std::cout << "Usage ./ircserv <port> <password>\n";
		return 0; 
	}
	int PORT = std::atoi(argv[1]);
	std::string PASS(argv[2]);


	int server_fd;
	// socket - Создать новый поточный Интернет-сокет (TCP/IP) и вернуть его файловый дескриптор
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
		std::cout << "Error creating socket\n"; 
		return 0; 
	}

	fcntl(server_fd, F_SETFL, O_NONBLOCK);  // устанавливается неблокирующий доступ к фд

	struct sockaddr_in address;

	memset((char *)&address, 0, sizeof(address)); 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(PORT);
	// bind - Связать сокет с IP-адресом и портом
	if (bind(server_fd,(struct sockaddr *)&address,sizeof(address)) < 0) { 
		std::cout << "Bind failed\n"; 
		return 0; 
	}

	//listen - Объявить о желании принимать соединения. Слушает порт и ждет когда будет установлено соединение
	if (listen(server_fd, 10) < 0) { // 10 - максимальное количество соединений, которые могут быть поставлены в очередь
		std::cout << "Listen error\n"; 
		return 0; 
	}
	int new_socket = 0;
	socklen_t size = sizeof(address);

	while(1) {
		std::cout << "\n+++++++ Waiting for new connection ++++++++\n\n";
		// accept - Принять запрос на установку соединения
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &size)) < 0) {
			std::cout << "Accept error\n"; 
			return 0; 
		}

	// fd_set fd_set_read;
	// fd_set fd_set_write;
	// FD_ZERO(&fd_set_read);
	// FD_ZERO(&fd_set_write);

/*

проходимся по всем дескрипторам, если встречаем тот, который
** 					 содержится в отслеживаемых селектом (т.е. он содержится в сете);
**					 - Если это дескриптор сервера, то нужно подтвердить соединение и
**		  			   установить тип этого дескриптора, как клиентский;
**					 - Если это дескриптор клиента - то нужно получить от него 
**					   сообщение и отослать серверу
*/




		char buffer[1024] = {0};

	//  recv - получение/чтение данных из сокета
		int valread = recv(new_socket, buffer, 1024, 0);
		std::cout << buffer;
		if (valread < 0) { 
			printf("No bytes are there to read");
		}
		std::string hello = "Hello from the server";
	//  send - отправка данных
		send(new_socket, hello.c_str(), hello.length(), 0);
		
		close(new_socket);
		return 0;
	}
}