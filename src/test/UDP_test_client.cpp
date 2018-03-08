#include "broadcastUDP.h"
#include "ptopTCP.h"
#include "socketInformation.h"
#include "theNextThread.h"
#include <windows.h>
#include <iostream>
int main() {
	std::string others_ip;
	{
		::theNextSocket::broadcaseUDP udp;
		udp.send(::theNextSocket::information::getIP());
		others_ip = udp.receive();
	}
	::theNextSocket::ptopTCP tcp;
	::theNextSocket::ptopTCP tcp2;
	tcp.setIP(others_ip);
	// tcp2.setIP(others_ip);
	::theNextSocket::theNextThread thread([&tcp2](){
		::std::cout << tcp2.receive() << ::std::endl;
	});
	std::string mess;
	while (::std::cin >> mess) {
		tcp.send(mess);
	}
}