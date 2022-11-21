#include "TCPRequestChannel.h"

//using namespace std;


TCPRequestChannel::TCPRequestChannel (const std::string _ip_address, const std::string _port_no) {
    if (_ip_address == "") {
        struct sockaddr_in server;
        int server_sock, bind_stat, listen_stat;

        // Socket
        server_sock, sockfd = socket(AF_INET, SOCK_STREAM, 0);

        // Bind
        bzero( (char *)&server, sizeof(server) );
        //memset(&server, 0, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        int portno = atoi(_port_no.c_str());
        server.sin_port = htons(portno);

        bind_stat = bind(server_sock, (struct sockaddr *)&server, sizeof(server));

        // Listen
        listen_stat = listen(server_sock, 70);

        // Connect
        //accept_conn();
    }
    else {
        struct sockaddr_in server_info;
        int client_sock, connect_stat;

        client_sock, sockfd = socket(AF_INET, SOCK_STREAM, 0);

        bzero( (char *)&server_info, sizeof(server_info) );
        //memset(&server, 0, sizeof(server));
        server_info.sin_family = AF_INET;
        int portno = atoi(_port_no.c_str());
        server_info.sin_port = htons(portno);
        inet_pton(AF_INET, _ip_address.c_str(), &server_info.sin_addr); //?
        //inet_pton(AF_INET, _ip_address.c_str(), &server_info.sin_addr.s_addr);

        connect_stat = connect(client_sock, (struct sockaddr *)&server_info, sizeof(server_info));
    }
    
}

TCPRequestChannel::TCPRequestChannel (int _sockfd) {
    sockfd = _sockfd;
}

TCPRequestChannel::~TCPRequestChannel () {
    close(sockfd);
}

int TCPRequestChannel::accept_conn () {
    //struct sockaddr_storage client_info;
    //socklen_t len = sizeof(client_info);
    return accept(sockfd, nullptr, nullptr);
}

int TCPRequestChannel::cread (void* msgbuf, int msgsize) {
    return read (sockfd, msgbuf, msgsize);
}

int TCPRequestChannel::cwrite (void* msgbuf, int msgsize) {
    return write (sockfd, msgbuf, msgsize);
}
