#include <iostream>
#include <fcntl.h>
#include <sys/socket.h> 
#include <netinet/in.h> //для sockaddr_in - используется для хранения адресов ipv4
#include <unistd.h>

int main() {

    int server_fd;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) { //создается поточный Интернет-сокет (TCP/IP)
        std::cout << "Error creating socket\n"; 
        return 0; 
    }

    // fcntl(server_fd, F_SETFL, O_NONBLOCK);  // устанавливается неблокирующий доступ к fd //???

    struct sockaddr_in address;
    const int PORT = 8080; //Where the clients can reach at

    memset((char *)&address, 0, sizeof(address)); 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = htonl(INADDR_ANY); 
    address.sin_port = htons(PORT); 
    if (bind(server_fd,(struct sockaddr *)&address,sizeof(address)) < 0) { 
        std::cout << "Bind failed\n"; 
        return 0; 
    }
    if (listen(server_fd, 10) < 0) { // 10 - максимальное количество соединений, которые могут быть поставлены в очередь
        std::cout << "Listen error\n"; 
        return 0; 
    }
    int new_socket = 0;
    socklen_t size = sizeof(address);

    while(1) {
        std::cout << "\n+++++++ Waiting for new connection ++++++++\n\n";
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &size)) < 0) {
            std::cout << "Accept error\n"; 
            return 0; 
        }

        char buffer[1024] = {0};

        int valread = recv(new_socket, buffer, 1024, 0); //  чтениe данных из сокета, flag равен нулю - считанные данные удаляются из сокета
        std::cout << buffer;
        if (valread < 0) { 
            printf("No bytes are there to read");
        }
        std::string hello = "Hello from the server";
        send(new_socket, hello.c_str(), hello.length(), 0);
        
        close(new_socket);
        return 0;
    }
}