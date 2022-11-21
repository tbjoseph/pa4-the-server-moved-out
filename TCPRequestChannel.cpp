#include "TCPRequestChannel.h"

//using namespace std;


TCPRequestChannel::TCPRequestChannel (const std::string _ip_address, const std::string _port_no) {
    if (_ip_address == "") {
        struct sockaddr_in server;
        int bind_stat, listen_stat;

        // Socket
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) throw std::invalid_argument("ERROR opening socket");

        // Bind
        bzero( (char *)&server, sizeof(server) );
        //memset(&server, 0, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons(atoi(_port_no.c_str()));
        server.sin_addr.s_addr = INADDR_ANY;
        //int portno = atoi(_port_no.c_str());

        bind_stat = bind(sockfd, (struct sockaddr *)&server, sizeof(server));
        if (bind_stat < 0) {
            throw std::invalid_argument("ERROR on binding");
        }

        // Listen
        listen_stat = listen(sockfd, 5);
        if (listen_stat < 0) throw std::invalid_argument("ERROR on listening");

        // Connect
        //accept_conn();
    }
    else {
        struct sockaddr_in server_info;
        int connect_stat;

        this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) throw std::invalid_argument("ERROR opening socket");

        bzero( (char *)&server_info, sizeof(server_info) );
        //memset(&server_info, 0, sizeof(server_info));
        server_info.sin_family = AF_INET;
        //int portno = atoi(_port_no.c_str());
        server_info.sin_port = htons(atoi(_port_no.c_str()));
        //inet_pton(AF_INET, _ip_address.c_str(), &server_info.sin_addr); //?
        inet_pton(AF_INET, _ip_address.c_str(), &server_info.sin_addr.s_addr);
        //server_info.sin_addr.s_addr = INADDR_ANY;

        connect_stat = connect(sockfd, (struct sockaddr *)&server_info, sizeof(server_info));
        if (connect_stat < 0) {
            throw std::invalid_argument("ERROR on connecting");
        }
    }
    
}

TCPRequestChannel::TCPRequestChannel (int _sockfd) {
    this->sockfd = _sockfd;
}

TCPRequestChannel::~TCPRequestChannel () {
    close(sockfd);
}

int TCPRequestChannel::accept_conn () {
    struct sockaddr_storage client_info;
    socklen_t len = sizeof(client_info);
    return accept(this->sockfd, (struct sockaddr *)&client_info, &len);
}

int TCPRequestChannel::cread (void* msgbuf, int msgsize) {
    return read (sockfd, msgbuf, msgsize);
}

int TCPRequestChannel::cwrite (void* msgbuf, int msgsize) {
    return write (sockfd, msgbuf, msgsize);
}
