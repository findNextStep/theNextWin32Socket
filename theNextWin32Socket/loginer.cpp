#include "stdafx.h"
#include "broadcastUDP.h"
#include "ptopTCP.h"
#include "loginer.h"
#include "socketInformation.h"
#include "time.h"
#include <iostream>
using namespace std;
namespace theNextChater {
	loginer::loginer(string name) :
		check([this]() {
		::theNextSocket::broadcaseUDP udp(loginer::UDP_PORT);
		::nlohmann::json message = ::nlohmann::json::parse(udp.receive());
		if (message["state"]) {
			time_t now;
			time(&now);
			cout << message.dump() << endl;
			std::string name = message["info"]["name"];
			this->loginers[name]["ip"] = message["info"]["ip"];
			this->loginers[name]["mac"] = message["info"]["mac"];
			this->loginers[name]["lastTime"] = now;
		}
		else {
			std::string name = message["info"]["name"];
			cout << name << endl;
			if (this->loginers.find(name) != this->loginers.end()) {
				this->loginers.erase(this->loginers.find(name));
			}
			cout << "endl" << endl;
		}
		for (auto person : this->loginers) {
			cout << person.first << "\t" << person.second["ip"] << "\t" << person.second["mac"] << endl;
		}
	}), accept([this]() {
		::theNextSocket::ptopTCP tcp(loginer::TCP_PORT);
		std::string  recive = tcp.receive();
		::nlohmann::json message = ::nlohmann::json::parse(recive);
		if (message.find("name") != message.end()) {
			cout << message["name"] << " --> " << message["message"] << endl;
		}
		else if (message.dump() == "check") {

		}
	}), online([this]() {
		if (!this->information.is_null()){
			::nlohmann::json login_message;
			login_message["info"] = this->information;
			cout << this->information << endl;
			login_message["state"] = true;
			::theNextSocket::broadcaseUDP udp(loginer::UDP_PORT);
			udp.send(login_message.dump());
		}
		time_t now;
		time(&now);
		for (auto per : this->loginers) {
			if (now - per.second["lastTime"] > loginer::checkTime * 5) {
				string name = per.first;
				if (!tryChat(name)) {
					if (this->loginers.find(name) != this->loginers.end()) {
						this->loginers.erase(this->loginers.find(name));
					}
				}
				else {
					per.second["lastTime"] = now;
				}
			}
		}
	}) {
		online.setiInterval(checkTime);
		this->information["ip"] = ::theNextSocket::information::getIP();
		this->information["mac"] = ::theNextSocket::information::getMAC();
		this->information["name"] = name;
	}
	loginer::~loginer() {
		::nlohmann::json login_message;
		login_message["info"] = this->information;
		login_message["state"] = false;
		::theNextSocket::broadcaseUDP udp;
		udp.send(login_message.dump());
	}
	void loginer::chatTo(std::string name, std::string message) {
		::theNextSocket::ptopTCP tcp(loginer::TCP_PORT);
		std::string ip  = this->loginers[name]["ip"];
		std::string newip(ip.begin() + 1, ip.end() - 1);
		tcp.setIP(ip);
		::nlohmann::json j;
		j["name"] = this->information["name"];
		j["message"] = message;
		tcp.send(j.dump());
	}
	bool loginer::tryChat(std::string name) {
		auto connect_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (connect_socket == INVALID_SOCKET) {
			wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			exit(1);
		}
		SOCKADDR_IN sin;
		sin.sin_family = AF_INET;
		sin.sin_port = htons(TCP_PORT);
		string ip = this->loginers[name]["ip"];
		sin.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
		if (::connect(connect_socket, (sockaddr*)&sin, sizeof(sin)) == -1) {
			return false;
		}
		int front = 0;
		std::string message = "check";
		while (front < message.size()) {
			front += ::send(connect_socket, message.c_str(), message.size(), 0);
		}
	}
}