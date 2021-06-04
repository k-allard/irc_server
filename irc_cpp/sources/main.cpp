#include <iostream>
#include <fcntl.h>
#include <sys/socket.h> 
#include <netinet/in.h> //для sockaddr_in
#include <unistd.h> 
#include <cstdlib> // for atoi
#include <set> // for std::set
#include <algorithm> // for std::max

int main(int argc, char **argv) {
	if (argc != 3) {
		std::cout << "Error! Usage ./ircserv <port> <password>\n";
		exit(1); 
	}

	int					PORT			= std::atoi(argv[1]);
	std::string			PASS(argv[2]);
	int 				server_fd		= 0;
	struct sockaddr_in	address;		// для хранения адресов ipv4
	socklen_t			size			= sizeof(address);
	char				buf[1024]		= {0}; // буфер для чтения из сокетов
    int					bytes_read		= 0;

	// socket - Создать новый поточный Интернет-сокет (TCP/IP) и вернуть его файловый дескриптор
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
		perror("socket");
        exit(2);
	}
	fcntl(server_fd, F_SETFL, O_NONBLOCK);  // устанавливается неблокирующий доступ к фд

	//Инициализация структуры с адресом
	memset((char *)&address, 0, sizeof(address)); 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(PORT);

	// bind - Связать сокет с IP-адресом и портом
	if (bind(server_fd,(struct sockaddr *)&address,sizeof(address)) < 0) { 
		perror("bind");
        exit(3);
	}

	//listen - Объявить о желании принимать соединения. Слушает порт и ждет когда будет установлено соединение
	if (listen(server_fd, 10) < 0) { // 10 - максимальное количество соединений, которые могут быть поставлены в очередь
		perror("listen");
        exit(4);
	}

	//сет с клиентами, подключенными к нашему серверу
	std::set<int> clients_fd;
    clients_fd.clear();

	int new_socket = 0;

	while(1) {
		// Заполняем сет сокетов на мониторинг готовности к чтению
		fd_set readset;
		FD_ZERO(&readset);
		FD_SET(server_fd, &readset);
		for(std::set<int>::iterator it = clients_fd.begin(); it != clients_fd.end(); it++)
            FD_SET(*it, &readset);

		// Заполняем сет сокетов на мониторинг готовности к записи
		fd_set writeset;
		FD_ZERO(&writeset);
		FD_SET(server_fd, &writeset);
		for(std::set<int>::iterator it = clients_fd.begin(); it != clients_fd.end(); it++)
            FD_SET(*it, &writeset);

		int mx = 0;
		// mx+1 - число, на единицу большее максимального файлового дескриптора в любом из наборов (1 аргумент selecta)
		if (!clients_fd.empty())
    		mx = std::max(server_fd, *clients_fd.rbegin());
		else    //the set is empty
			mx = server_fd;

		// select - Ждём события в одном из сокетов
		int total_fds = 0; 		// total_fds - суммарное кол-во фд, сработавших в селекте
		if ((total_fds = select(mx + 1, &readset, &writeset, NULL, NULL)) == -1) {
    		perror("select");
            exit(5);
		}

		// FD_ISSET - Определяем тип события и выполняем соответствующие действия:
		if (FD_ISSET(server_fd, &readset))
        {
			int new_socket = 0;
            // Поступил новый запрос на соединение, принимаем с помощью accept
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &size)) < 0) {
                perror("accept");
                exit(6);
            }
            fcntl(new_socket, F_SETFL, O_NONBLOCK);
            clients_fd.insert(new_socket);
			std::cout << "\n+++++++ New client joined! ++++++++\n\n";
        }

		for (std::set<int>::iterator it = clients_fd.begin(); it != clients_fd.end(); it++)
        {
            if (FD_ISSET(*it, &readset)) {
                // Поступили данные от клиента, читаем их
                if ((bytes_read = recv(*it, buf, 1024, 0)) <= 0) {
                    // Соединение разорвано, удаляем сокет из сета
                    close(*it);
                    clients_fd.erase(*it);
                    continue;
				}

                // Отправим данные от клиента парсеру
                // parser(*it, buf, bytes_read, 0); // (фд клиента, буфер с сообщением, размер сообщения)
            }
            if (FD_ISSET(*it, &writeset)) {
				std::string client_buf;
				client_buf.clear();
				// Посмотрим буфер этого клиента, если есть, что ему писать, то сливаем ему буфер, буфер очищаем
				if (!client_buf.empty())
					send(*it, client_buf.c_str(), client_buf.length(), 0);
			}
        }
	}
	return 0;
}