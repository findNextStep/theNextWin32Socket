#include "theNextThread.h"
#include <iostream>
using namespace std;
int main(){
    ::theNextSocket::theNextThread a([](){
        cout << "test1"<<endl;
        Sleep(200);
        cout << "end??"<<endl;
    });
    a.stop();
    Sleep(100);
    cout << "test2" << endl;
}