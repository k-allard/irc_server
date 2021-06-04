#include "../includes/Server.hpp"

Server::Server(int port, std::string pass) : _port(port), _pass(pass), _server_fd(0) {
	initServer();
	_clients_fd.clear();
	_clients.clear();
};

Server::~Server() { }

void Server::initFds() {

	FD_ZERO(&_readset);
	FD_SET(_server_fd, &_readset);
	for (std::set<int>::iterator it = _clients_fd.begin(); it != _clients_fd.end(); it++)
		FD_SET(*it, &_readset);

	FD_ZERO(&_writeset);
	FD_SET(_server_fd, &_writeset);
	for (std::set<int>::iterator it = _clients_fd.begin(); it != _clients_fd.end(); it++)
		FD_SET(*it, &_writeset);

	_mx = 0;
	if (!_clients_fd.empty())
		_mx = std::max(_server_fd, *_clients_fd.rbegin());
	else
		_mx = _server_fd;
}

// select - Ждём события в одном из сокетов
void Server::doSelect() {
	int total_fds = 0; 		// total_fds - суммарное кол-во фд, сработавших в селекте
	if ((total_fds = select(_mx + 1, &_readset, &_writeset, NULL, NULL)) == -1) {
		perror("select");
		exit(5);
	}
}

void Server::checkFds() {
	int					bytes_read		= 0;
	struct sockaddr_in	address;		// структура для хранения адресов ipv4

	bzero(_buf, 1024);

	int new_socket = 0;
	// FD_ISSET - Определяем тип события и выполняем соответствующие действия:
	if (FD_ISSET(_server_fd, &_readset)) {
		int			new_socket	= 0;
		socklen_t	size		= sizeof(address);
		// Поступил новый запрос на соединение, принимаем с помощью accept
		if ((new_socket = accept(_server_fd, (struct sockaddr *)&address, &size)) < 0) {
			perror("accept");
			exit(6);
		}
		fcntl(new_socket, F_SETFL, O_NONBLOCK);
		// Добавляем подключившегося клиента в список наших клиентов
		_clients_fd.insert(new_socket);
		// Создаем новый инстанс класса клиент, передаем ему его фд и адрес
		Client client(new_socket, address);
		// добавить его в список (мапу) наших клиентов, поставив фд в каестве ключа
		_clients.insert( std::pair< int,Client* >(new_socket, &client));
		std::cout << "\n+++++++ New client joined! ++++++++\n\n";
		std::cout << "\n+++++++ Our clients' fds: ++++++++\n";
		std::map<int,Client*>::iterator it;
		for (it=_clients.begin(); it!=_clients.end(); ++it)
    		std::cout << it->first << "||| "; 
		std::cout << "\n";
		std::cout.flush();
	}
	for (std::set<int>::iterator it = _clients_fd.begin(); it != _clients_fd.end(); it++) {
		if (FD_ISSET(*it, &_readset)) {
			// Поступили данные от клиента, читаем их
			if ((bytes_read = recv(*it, _buf, 1024, 0)) <= 0) {
				// Соединение разорвано, удаляем сокет из сета
				close(*it);
				_clients_fd.erase(*it);
				//удалить из мапы "клиенты" 
				std::cout << "\n+++++++ Сlient gone away! ++++++++\n\n";
				break ;
			}
			std::string clientWrote(_buf);
			std::cout << "Client " << *it << " wrote: " << clientWrote; 
			// Отправим данные от клиента парсеру
			// parser(*it, buf, bytes_read, 0); // (фд клиента, буфер с сообщением, размер сообщения)
		}
		if (FD_ISSET(*it, &_writeset)) {
			std::string client_buf;
			client_buf.clear();
			// Посмотрим буфер этого клиента, если есть, что ему писать, то отправим это ему, буфер очистим
			if (!client_buf.empty())
				send(*it, client_buf.c_str(), client_buf.length(), 0);
		}
	}
}


void Server::mainLoop() {
	while (1) {
		initFds();
		doSelect();
		checkFds();
	}
}

void Server::initServer() {
    if ((_server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(2);
	}
	fcntl(_server_fd, F_SETFL, O_NONBLOCK);  // устанавливается неблокирующий доступ к фд

	//Инициализация структуры с адресом
	memset((char *)&_address, 0, sizeof(_address));
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = htonl(INADDR_ANY);
	_address.sin_port = htons(_port);

	// bind - Связать сокет с IP-адресом и портом
	if (bind(_server_fd,(struct sockaddr *)&_address,sizeof(_address)) < 0) {
		perror("bind");
		exit(3);
	}

	//listen - Объявить о желании принимать соединения. Слушает порт и ждет когда будет установлено соединение
	if (listen(_server_fd, 10) < 0) { // 10 - максимальное количество соединений, которые могут быть поставлены в очередь
		perror("listen");
		exit(4);
	}
}
