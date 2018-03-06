#include "broadcastUDP.h"
#include "ptopTCP.h"
#include "socketInformation.h"
#include <windows.h>
#include <iostream>
int main() {
    std::string others_ip;
    {
        ::theNextSocket::broadcaseUDP udp;
        others_ip = udp.receive();
        udp.send(::theNextSocket::getIP());
    }
    ::theNextSocket::ptopTCP tcp(others_ip);
    std::string mess;
    while (1) {
        mess = tcp.receive();
        std::cout << mess<<::std::endl; 
    }
}