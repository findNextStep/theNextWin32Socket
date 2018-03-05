#include "broadcastUDP.h"
#include <windows.h>
int main() {
    ::theNextSocket::broadcaseUDP u1;
    Sleep(100);
    u1.send("test in server");
    ::theNextSocket::broadcaseUDP u2;
    Sleep(100);
    u2.send("test in server");
}