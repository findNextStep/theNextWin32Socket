#include "ptopTCP.h"
namespace theNextSocket {
ptopTCP::ptopTCP(std::string ip,int port)
    :ip(ip),port(port),socketBase() {}
void ptopTCP::init() {
    connect_socket = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (connect_socket == INVALID_SOCKET) {
        wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        exit(1);
    }
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
}
void ptopTCP::send(std::string message) {
    this->init();
    int err;
    if ((err = ::bind(connect_socket,(SOCKADDR *) &sin,sizeof(sin)))!= WSANOTINITIALISED){
wprintf(L"bind function failed with error: %ld\n", err);
    }
    auto i = connect(connect_socket,(sockaddr*)&sin,sizeof(sin));
    if (i == SOCKET_ERROR) {
        wprintf(L"connect function failed with error: %ld\n", WSAGetLastError());
        exit(1);
    }
    int front =  0;
    while(front < message.size()) {
        front += ::send(connect_socket, message.c_str(), message.size(), 0);
    }
    this->close();
}
std::string ptopTCP::receive(int length) {
    char buff[256];
    this->init();
    ::bind(connect_socket,(SOCKADDR *) &sin,sizeof(sin));
    ::listen(connect_socket,1);
    SOCKET accept_socket = accept(connect_socket,NULL,NULL);
    int rece = ::recv(accept_socket,buff,256,0);
    this->close();
    closesocket(accept_socket);
    std::string re;
    for (int i=0; i<rece; ++i) {
        re.push_back(buff[i]);
    }
    return re;
}
void ptopTCP::close() {
    closesocket(connect_socket);
}
}