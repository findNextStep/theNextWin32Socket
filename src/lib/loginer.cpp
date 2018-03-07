#include "broadcastUDP.h"
#include "ptopTCP.h"
#include "socketInformation.h"
#include "loginer.h"
#include "time.h"
#include <iostream>
using namespace std;
namespace theNextChater {
loginer::loginer(string name):
    check([this]() {
    ::theNextSocket::broadcaseUDP udp;
    ::nlohmann::json message = ::nlohmann::json::parse(udp.receive());
    if (message["state"]) {
        time_t timep;
        time(&timep);
        std::string name = message["info"]["name"];
        this->loginers[name]["ip"]      = message["info"]["ip"];
        this->loginers[name]["mac"]     = message["info"]["mac"];
        this->loginers[name]["lastTime"]= timep;
        for (auto person : this->loginers) {
            cout << person.first << "\t" << person.second["ip"]<<"\t"<<person.second["mac"]<<endl;
        }
    } else {
        std::string name = message["info"]["name"];
        if (this->loginers.find(name)!= this->loginers.end()) {
            this->loginers.erase(this->loginers.find(name));
        }
    }
}), accept([this]() {
    ::theNextSocket::ptopTCP tcp;
    auto receive = tcp.receive();
}) {
    this->information["ip"] = ::theNextSocket::information::getIP();
    this->information["mac"] = ::theNextSocket::information::getMAC();
    this->information["name"] = name;
    {
        ::nlohmann::json login_message;
        login_message["info"] = this->information;
        login_message["state"] = true;
        ::theNextSocket::broadcaseUDP udp;
        udp.send(login_message.dump());
    }
}
loginer::~loginer() {
    ::nlohmann::json login_message;
    login_message["info"] = this->information;
    login_message["state"] = false;
    ::theNextSocket::broadcaseUDP udp;
    udp.send(login_message.dump());
}
}