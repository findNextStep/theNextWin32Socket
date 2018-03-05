#include "socketInformation.h"
#include <iostream>
using namespace std;
using namespace ::theNextSocket;
int main() {
    cout << "ip  as :\t" << getIP()  << endl;
    cout << "mac as :\t" << getMAC() << endl;
}