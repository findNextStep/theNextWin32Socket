#include "loginer.h"
#include <iostream>
int main(){
    ::std::string name;
    std::cin >> name;
    ::theNextChater::loginer a(name);
    while (std::cin >> name){
        std::string mess;
        std::cin >> mess;
        a.chatTo(name,mess);
    }
}