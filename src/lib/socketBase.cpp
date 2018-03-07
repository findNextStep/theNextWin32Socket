#include "socketBase.h"
#include <iostream>
namespace theNextSocket {
int ::theNextSocket::WSAManager::count = 0;
::std::mutex WSAManager::mutex;
WSAManager::WSAManager() {
    std::lock_guard<std::mutex> lock(WSAManager::mutex);
    if (!count) {
        WORD wVersionRequested = MAKEWORD( 2, 2 );
        WSADATA wsaData;
        int err = WSAStartup( wVersionRequested, &wsaData );
        if ( err != 0 ) {
            exit(-1);
        }
    }
    ++count;
}
WSAManager::~WSAManager() {
    std::lock_guard<std::mutex> lock(WSAManager::mutex);
    if(!--count) {
        WSACleanup();
    }
}
}