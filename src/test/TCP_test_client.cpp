#include "ptopTCP.h"
#include "theNextThread.h"
#include <iostream>
#include <thread>
using namespace std;
int main() {
    ::theNextSocket::ptopTCP p("127.0.0.1");
    ::theNextSocket::ptopTCP re("127.0.0.1",23333);
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