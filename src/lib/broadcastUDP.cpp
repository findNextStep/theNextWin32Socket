#include "broadcastUDP.h"
namespace theNextSocket {
using ::std::string;
broadcaseUDP::broadcaseUDP(int port):port(port),socketBase() {
}
void broadcaseUDP::init() {
    connect_socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    bool opt = true;
    ::setsockopt(connect_socket, SOL_SOCKET, SO_BROADCAST, (char*)&opt, sizeof(bool));
    ::bind(connect_socket, (SOCKADDR*)&sin, sizeof(SOCKADDR));
}

void broadcaseUDP::send(string message) {
    sin_from.sin_family = AF_INET;
    sin_from.sin_port = htons(port);
    sin_from.sin_addr.s_addr = INADDR_BROADCAST;
    this->init();
    int nSendSize = sendto(connect_socket, message.c_str(), message.size(),
                           0, (SOCKADDR*)&sin_from, sizeof(SOCKADDR));
    this->close();
}
string broadcaseUDP::receive(int length) {
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = 0;
    this->init();
    const int MAX_BUF_LEN = 255;
    char buff[MAX_BUF_LEN] = "";
    int nAddrLen = sizeof(SOCKADDR);
    int nSendSize = recvfrom(connect_socket, buff, 255, 0, (SOCKADDR*)&sin, &nAddrLen);
    buff[nSendSize] = '\0';
    string result;
    for (int i=0; i<nSendSize; ++i) {
        result.push_back(buff[i]);
    }
    this->close();
    return result;
}

void broadcaseUDP::close() {
    closesocket(connect_socket);
}
}