#include "../includes/Server.hpp"

Server::Server(int port, std::string pass) : _port(port), _pass(pass), _server_fd(0) {
	initServer();
	_clients_fd.clear();
	_clients.clear();
};

Server::~Server() {
	std::map<int, Client*>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); ++it)
		delete it->second;
	_clients.clear();
}

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

//для дебага
void Server::printClients() {
std::cout << "Our clients: ";
		std::map<int, Client*>::iterator it;
		for (it = _clients.begin(); it != _clients.end(); ++it)
		{
    		std::cout << it->second->getFd();
			if (it->second->getNick() != "")
				std::cout << " Nick: " << it->second->getNick();
			std::cout << " | ";
		}
		std::cout << std::endl << std::endl;
}

//для дебага
void Server::temParser(int fd, char *buf, int size)
{
	Cmds cmds(*this);
	std::string com(buf);
	std::istringstream stream(com);
	std::queue<std::string> data;
	std::string tmp;
	while (std::getline(stream, tmp, '\n')) {
		if(tmp.empty())
			continue;
		tmp.erase(tmp.size() - 1, 1);
		//std::cout << "[" << tmp << "]\n";
		data.push(tmp);
	}
	while(!data.empty())
	{
		if (data.front().compare(0, 4, "NICK") == 0) {
			std::cout << "NICK cmd" << std::endl;
			std::string nick = "";
			if (data.front().size() > 4)
				nick = data.front().substr(5, data.front().npos);
			if (cmds.NICKCmd(fd, nick) == -1)
				perror("NICK err");
		}
		else if (data.front().compare(0, 4, "PASS") == 0) {
			std::cout << "PASS cmd" << std::endl;
			std::string args = "";
			if (data.front().size() > 4)
				args = data.front().substr(5, data.front().npos);
			if (cmds.PASSCmd(fd, args) == -1)
				perror("PASS err");
		}
		else if (data.front().compare(0, 4, "USER") == 0) {
			std::cout << "USER cmd" << std::endl;
			std::string args = "";
			if (data.front().size() > 4)
				args = data.front().substr(5, data.front().npos);
			if (cmds.USERCmd(fd, args) == -1)
				perror("USER err");
		}
		else if (data.front().compare(0, 3, "PMN") == 0) // для дебага. нет такой команды)
		{
			Client *client = cmds.findClient(fd);
			std::string nick = client->getNick();
			if (nick == "")
				std::cout << fd << " fd`s nick is not set\n";
			else
				std::cout << fd << " fd`s nick: " << client->getNick() << std::endl;
		}
		data.pop();
	}
}

void Server::checkFds() {
	int					bytes_read		= 0;
	struct sockaddr_in	address;		// структура для хранения адресов ipv4

	bzero(_buf, 512);

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
		Client *client = new Client(new_socket, address);
		// добавить его в список (мапу) наших клиентов, поставив фд в каестве ключа
		_clients.insert(std::pair< int,Client* >(new_socket, client));
		std::cout << "\n+++++++ New client joined! ++++++++\n\n";
		printClients();
	}
	for (std::set<int>::iterator it = _clients_fd.begin(); it != _clients_fd.end(); it++) {
		if (FD_ISSET(*it, &_readset)) {
			// Поступили данные от клиента, читаем их
			if ((bytes_read = recv(*it, _buf, 512, 0)) <= 0) {
				// Соединение разорвано, удаляем сокет из сета
				close(*it);
				_clients.erase(*it);
				_clients_fd.erase(*it);
				std::cout << "\n+++++++ Сlient gone away! ++++++++\n\n";
				printClients();
				break ;
			}
			_clients.at(*it)->appendMessageBuffer(_buf);
			if(_clients.at(*it)->isMessageBufferComplete())
			{
				temParser(*it, _clients.at(*it)->messageBuf, _clients.at(*it)->_messageBufLength);
				_clients.at(*it)->clearMessageBuffer();
			}

			// Отправим данные от клиента парсеру
			// parser(*it, buf, bytes_read, 0); // (фд клиента, буфер с сообщением, размер сообщения)

			// Parser *parser = new Parser(*this);
			// parser->do_parsing(*it, _buf, bytes_read);

		}
		if (FD_ISSET(*it, &_writeset)) {
			// Посмотрим буфер этого клиента, если есть, что ему писать, то отправим это ему, буфер очистим
			if (!_clients.at(*it)->_buf.empty()) {
				send(*it, _clients.at(*it)->_buf.front().c_str(), _clients.at(*it)->_buf.front().size(), 0);
				_clients.at(*it)->_buf.pop();
			}
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
