#include "ptopTCP.h"
#include <iostream>
#include <thread>
using namespace std;
int main() {
    ::theNextSocket::ptopTCP p("127.0.0.1",23333);
    ::std::thread thread([]() {
        ::theNextSocket::ptopTCP re("127.0.0.1");
        while (1) {
            auto str = re.receive();
            cout << "receive\t"<< str<<endl;
        }
    });
    string se;
    while(cin >> se) {
        if (se == "quit") {
            break;
        }

        p.send(se);
    }
    thread.detach();
    return 0;
}