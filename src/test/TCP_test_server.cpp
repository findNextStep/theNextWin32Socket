#include "ptopTCP.h"
#include "theNextThread.h"
#include <iostream>
#include <thread>
using namespace std;
int main() {
    ::theNextSocket::ptopTCP p(23333);
    ::theNextSocket::ptopTCP re;
    std::string ip = "127.0.0.1";
    p.setIP(ip);
    re.setIP(ip);
    ::theNextSocket::theNextThread thread([&re]() {
        cout << "wait" << endl;
        auto str = re.receive();
        cout << "receive\t"<< str<<endl;
    });
    string se;
    while(cin >> se) {
        if (se == "quit") {
            break;
        }
        p.send(se);
    }
    return 0;
}