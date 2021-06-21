#include "../includes/Server.hpp"

Server::Server(int port, std::string pass) : _port(port), _pass(pass), _server_fd(0) {
    time_t now = time(0);
    std::string dt(ctime(&now));
    dt.erase(dt.size() - 1, 1);
    this->_toc = dt;

    _name = "ircserv.net";
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
	std::cout << "A client disconnected" << std::endl;
//    printClients();
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
		std::cerr << "Error in select: " << strerror(errno) << std::endl;
		exit(5);
	}
}

//для дебага
//void Server::printClients() {
//std::cout << "Our clients: ";
//		std::map<int, Client*>::iterator it;
//		for (it = _clients.begin(); it != _clients.end(); ++it)
//		{
//    		std::cout << it->second->getFd();
//			if (it->second->getNick() != "")
//				std::cout << " Nick: " << it->second->getNick();
//			std::cout << " | ";
//		}
//		std::cout << std::endl << std::endl;
//}

std::string Server::getNamesNotInChannels()
{
	std::string names = "";

	for (std::map<int,Client *>::iterator it=_clients.begin(); it!=_clients.end(); ++it) {
		int isFound = 0;
		for (std::map<std::string, Channel *>::iterator it_ch=_channels.begin(); it_ch!=_channels.end() && isFound == 0; ++it_ch) {
			if (it_ch->second->getParticipantsFds()->find((*it).first) != it_ch->second->getParticipantsFds()->end())
				isFound = 1;
		}
		if (isFound == 0) {
			names += (*it).second->getNick();
			names += " ";
		}
	}
	if (!names.empty())
		names.erase(names.size() - 1, 1);
	return names;
}

void Server::processMessage(const Message *msg, int fd, Client *client, Cmds *cmds) {

    switch (msg->command->cmdType) {
		case MsgCmd__EMPTY :
			break;
        case MsgCmd_NICK : {
        	cmds->NICKCmd(fd, *msg);
            break;
        }
		case MsgCmd_JOIN : {
			cmds->JOINCmd(fd, *msg);
			break;
		}
        case MsgCmd_PASS : {
            cmds->PASSCmd(fd, *msg);
            break;
        }
        case MsgCmd_USER : {
            cmds->USERCmd(fd, *msg);
            break;
        }
		case MsgCmd_TOPIC : {
			cmds->TOPICCmd(fd, *msg);
			break;
		}
        case MsgCmd_PING : {
            cmds->PINGCmd(fd, *msg);
            break;
        }
        case MsgCmd_QUIT : {
            cmds->QUITCmd(fd, *msg);
            break;
        }
        case MsgCmd_PRIVMSG : {
            cmds->PRIVMSGCmd(fd, *msg);
            break;
        }
        case MsgCmd_NOTICE : {
            cmds->NOTICECmd(fd, *msg);
            break;
        }
        case MsgCmd_LIST : {
            cmds->LISTCmd(fd, *msg);
            break;
        }
		case MsgCmd_PART : {
            cmds->PARTCmd(fd, *msg);
            break;
        }
		case MsgCmd_LUSERS : {
			cmds->LUSERSCmd(fd, *msg);
			break;
		}
		case MsgCmd_KICK : {
            cmds->KICKCmd(fd, *msg);
            break;
        }
		case MsgCmd_NAMES : {
			cmds->NAMESCmd(fd, *msg);
            break;
		}
        case MsgCmd_WHO : {
            cmds->WHOCmd(fd, *msg);
            break;
        }
        case MsgCmd_WHOIS : {
            cmds->WHOISCmd(fd, *msg);
            break;
        }
        case MsgCmd_MOTD : {
            cmds->MOTDCmd(fd);
            break;
        }
        case MsgCmd_MODE : {
            cmds->MODECmd(fd, *msg);
            break;
        }
        default: {
            if(client->isReg()) {
                cmds->setReply(fd, ERR_UNKNOWNCOMMAND, ERR_UNKNOWNCOMMAND_MSG, msg->command->letters, "");
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
			std::cerr << "Error in accept: " << strerror(errno) << std::endl;
			exit(6);
		}
		fcntl(new_socket, F_SETFL, O_NONBLOCK);
		// Добавляем подключившегося клиента в список наших клиентов
		_clients_fd.insert(new_socket);
		// Создаем новый инстанс класса клиент, передаем ему его фд и адрес
		Client *client = new Client(new_socket, address);
		// добавить его в список (мапу) наших клиентов, поставив фд в каестве ключа
		_clients.insert(std::pair< int,Client* >(new_socket, client));
		std::cout << "[ircserv.net] New client joined!" << std::endl;
//		printClients();
	}
	for (std::set<int>::iterator it = _clients_fd.begin(); it != _clients_fd.end(); it++) {
		if (FD_ISSET(*it, &_readset)) {
			// Поступили данные от клиента, читаем их
			if ((bytes_read = recv(*it, _buf, 512, 0)) <= 0) {
				// Соединение разорвано, удаляем сокет из сета
				cmds.QUITCmd(*it);
				break ;
			}
			//std::cout <<  _buf <<std::endl;
			_clients.at(*it)->appendMessageBuffer(_buf);
			if(_clients.at(*it)->isMessageBufferComplete())
			{
				std::vector<Message> msgs = _parser->do_parsing(
						*it,
						_clients.at(*it)->messageBuf,
						_clients.at(*it)->_messageBufLength);
				for (std::vector<Message>::const_iterator msg = msgs.begin(); msg != msgs.end(); ++msg)
				{
                    this->processMessage(&(*msg), *it, _clients.at(*it), &cmds);
				}
				if(_clients.find(*it) != _clients.end())
				    _clients.at(*it)->clearMessageBuffer();
                else
                {
//                    _clients_fd.erase(*it);
                    break;
                }
			}
		}
		if (FD_ISSET(*it, &_writeset)) {
			// Посмотрим буфер этого клиента, если есть, что ему писать, то отправим это ему, буфер очистим
			if (!_clients.at(*it)->_buf.empty()) {
//			    std::cout << "Rpl: " << _clients.at(*it)->_buf.front();
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
		std::cerr << "Error in socket: " << strerror(errno) << std::endl;
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
		std::cerr << "Error in bind: " << strerror(errno) << std::endl;
		exit(3);
	}

	//listen - Объявить о желании принимать соединения. Слушает порт и ждет когда будет установлено соединение
	if (listen(_server_fd, 10) < 0) { // 10 - максимальное количество соединений, которые могут быть поставлены в очередь
		std::cerr << "Error in listen: " << strerror(errno) << std::endl;
		exit(4);
	}
}
