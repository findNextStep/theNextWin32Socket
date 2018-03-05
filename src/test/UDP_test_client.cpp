#include "broadcastUDP.h"
#include <iostream>
using namespace std;
int main(){
    ::theNextSocket::broadcaseUDP u;
   cout <<"receive :"<< u.receive() <<"."<< endl; 
}