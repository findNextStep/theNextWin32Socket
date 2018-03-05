#include "broadcastUDP.h"
#include <iostream>
using namespace std;

int main() {
    ::theNextSocket::broadcaseUDP u;
    while (true)
        cout <<"receive :"<< u.receive() <<"."<< endl;
}