#include "broadcastUDP.h"
#include <iostream>
using namespace std;
int main(){
    ::theNextSocket::broadcaseUDP u;
    u.send("test in server");
}