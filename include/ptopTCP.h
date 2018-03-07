#pragma once
#include "socketBase.h"
namespace theNextSocket{
class ptopTCP: public socketBase{
public:
    ptopTCP(int port);
    ptopTCP():ptopTCP(defalut_port) {}
    void setIP(std::string);
    virtual ~ptopTCP() {}
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
    std::string ip;
};
}