#pragma once
#include <WinSock2.h>
#include <windows.h>
#include <string>
#include "socketBase.h"
namespace theNextSocket {
class broadcaseUDP : public socketBase {
public:
    broadcaseUDP(int port);
    broadcaseUDP():broadcaseUDP(defalut_port) {}
    virtual ~broadcaseUDP() {}
    std::string receive(int length = 0);
    void send(std::string content);
protected:
    void close();
    void init();
private:
    int port;;
    SOCKET connect_socket;
    SOCKADDR_IN sin_from;
    SOCKADDR_IN sin;
};
}