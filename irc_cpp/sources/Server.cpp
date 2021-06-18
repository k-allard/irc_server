#include "../includes/Server.hpp"

Server::Server(int port, std::string pass) : _port(port), _pass(pass), _server_fd(0) {
	initServer();
	_clients_fd.clear();
	_clients.clear();
	_parser = new Parser(*this);
};

Server::~Server() {
	std::map<int, Client*>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); ++it)
		delete it->second;
	_clients.clear();
	delete _parser;
}

int     Server::disconnectClient(int fd)
{
    close(fd);
    _clients.erase(fd);
    _clients_fd.erase(fd);
    std::cout << "\n+++++++ Сlient gone away! ++++++++\n\n";
    printClients();
    return 0;
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

void Server::checkPerror(int code, const char* errorMessage)
{
    if (code == -1)
        perror(errorMessage);
}

void Server::processMessage(const Message *msg, int fd, Client *client, Cmds *cmds) {
    switch (msg->command->cmdType) {
        case MsgCmd_NICK : {
            checkPerror (cmds->NICKCmd(fd, *msg), "NICK err");
            break;
        }
        case MsgCmd_PASS : {
            checkPerror (cmds->PASSCmd(fd, *msg), "PASS err");
            break;
        }
        case MsgCmd_USER : {
            checkPerror (cmds->USERCmd(fd, *msg), "USER err");
            break;
        }
        case MsgCmd_PING : {
            checkPerror (cmds->PONGCmd(fd, *msg), "PONG err");
            break;
        }
        case MsgCmd_QUIT : {
            checkPerror (cmds->QUITCmd(fd, (*msg).params->toString()), "QUIT err");
            break;
        }
        case MsgCmd_PRIVMSG : {
            checkPerror (cmds->PRIVMSGCmd(fd, *msg), "PRIVMSG err");
            break;
        }
        default: {
            if(client->isReg()) {
                cmds->setReply(fd, ERR_UNKNOWNCOMMAND, ERR_UNKNOWNCOMMAND_MSG, msg->command->letters);
            }
            break;
        }
    }
}

void Server::checkFds() {
	int					bytes_read		= 0;
	struct sockaddr_in	address;		// структура для хранения адресов ipv4
    Cmds cmds(*this);

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
				cmds.QUITCmd(*it, "");
				break ;
			}
			_clients.at(*it)->appendMessageBuffer(_buf);
			if(_clients.at(*it)->isMessageBufferComplete())
			{
				std::vector<Message> msgs = _parser->do_parsing(
						*it,
						_clients.at(*it)->messageBuf,
						_clients.at(*it)->_messageBufLength);
				// temParser(*it, _clients.at(*it)->messageBuf, _clients.at(*it)->_messageBufLength);
				for (std::vector<Message>::const_iterator msg = msgs.begin(); msg != msgs.end(); ++msg)
				{
                    this->processMessage(&(*msg), *it, _clients.at(*it), &cmds);


				}
                if (_clients.count(*it))
				    _clients.at(*it)->clearMessageBuffer();
                else
                {
                    _clients_fd.erase(*it);
                    break;
                }
			}
		}
		if (FD_ISSET(*it, &_writeset)) {
			// Посмотрим буфер этого клиента, если есть, что ему писать, то отправим это ему, буфер очистим
			if (!_clients.at(*it)->_buf.empty()) {
			    std::cout << "Rpl: " << _clients.at(*it)->_buf.front();
				send(*it, _clients.at(*it)->_buf.front().c_str(), _clients.at(*it)->_buf.front().size(), 0);
				_clients.at(*it)->_buf.front().erase();
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
