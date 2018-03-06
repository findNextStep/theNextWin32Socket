#include "broadcastUDP.h"
#include "ptopTCP.h"
#include "socketInformation.h"
#include <windows.h>
#include <iostream>
int main() {
    std::string others_ip;
    {
        ::theNextSocket::broadcaseUDP udp;
        udp.send(::theNextSocket::information::getIP());
        others_ip = udp.receive();
    }
    ::theNextSocket::ptopTCP tcp(others_ip);
    std::string mess;
    while (::std::cin >> mess){
        tcp.send(mess);
    }
}