#include "socketInformation.h"
#include <iostream>
using namespace std;
int main() {
    cout << "ip  as :\t" << ::theNextSocket::information::getIP()  << endl;
    cout << "mac as :\t" << ::theNextSocket::information::getMAC() << endl;
}