#include "stdafx.h"
#include <iostream>
namespace theNextSocket {
	int ::theNextSocket::WSAManager::count = 0;
	WSAManager::WSAManager() {
		if (!count) {
			WORD wVersionRequested = MAKEWORD(2, 0);
			WSADATA wsaData;
			int err = WSAStartup(wVersionRequested, &wsaData);
			if (err != 0) {
				exit(-1);
			}
		}
		++count;
	}
	WSAManager::~WSAManager() {
		if (!--count) {
			WSACleanup();
		}
	}
}