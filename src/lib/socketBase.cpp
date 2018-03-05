#include "socketBase.h"
#include <iostream>
namespace theNextSocket {
int ::theNextSocket::WSAManager::count = 0;
WSAManager::WSAManager() {
    if (!count) {
        WORD wVersionRequested = MAKEWORD( 2, 2 );
        WSADATA wsaData;
        int err = WSAStartup( wVersionRequested, &wsaData );
        if ( err != 0 ) {
            exit(-1);
        }
        std::cout << "init wsa" << std::endl;
    }
    ++count;
}
WSAManager::~WSAManager() {
    if(!--count) {
        WSACleanup();
    }
}
}