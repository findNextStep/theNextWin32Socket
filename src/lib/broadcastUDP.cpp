#include "broadcastUDP.h"
#include <iostream>
namespace theNextSocket {
using ::std::string;
broadcaseUDP::broadcaseUDP(int port) {
    this->init(port);
}
broadcaseUDP::broadcaseUDP() {
    this->init(defalut_port);
}
broadcaseUDP::~broadcaseUDP(){
    
}
void broadcaseUDP::init(int port) {
    this->wVersionRequested = MAKEWORD( 2, 2 );
    int err = WSAStartup( wVersionRequested, &wsaData );
    if ( err != 0 )
    {
        exit(-1);
    }
    connect_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(3779);
    sin.sin_addr.s_addr = 0;

    sin_from.sin_family = AF_INET;
    sin_from.sin_port = htons(3779);
    sin_from.sin_addr.s_addr = INADDR_BROADCAST;
    bool opt = true;
    ::setsockopt(connect_socket, SOL_SOCKET, SO_BROADCAST, (char*)&opt, sizeof(bool));
    ::bind(connect_socket, (SOCKADDR*)&sin, sizeof(SOCKADDR));
}

void broadcaseUDP::send(string message) {
    int nSendSize = sendto(connect_socket, message.c_str(), message.size(), 0, (SOCKADDR*)&sin_from, sizeof(SOCKADDR));
}
string broadcaseUDP::receive(int length) {
    const int MAX_BUF_LEN = 255;
    char buff[MAX_BUF_LEN] = "";
    int nAddrLen = sizeof(SOCKADDR);
    int nSendSize = recvfrom(connect_socket, buff, 255, 0, (SOCKADDR*)&sin, &nAddrLen);
    buff[nSendSize] = '\0';
    string result;
    // std::cout << nSendSize << std::endl;
    for (int i=0; i<nSendSize; ++i) {
        result.push_back(buff[i]);
    }
    // std::cout << std::endl;
    return result;
}
}