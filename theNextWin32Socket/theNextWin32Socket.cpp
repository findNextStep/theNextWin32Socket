// theNextWin32Socket.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include "loginer.h"
#include <iostream>
int main() {
	::std::string name;
	std::cin >> name;
	::theNextChater::loginer a(name);
	while (std::cin >> name) {
		if (name == "quit") {
			break;
		}
		std::string mess;
		std::cin >> mess;
		
		a.chatTo(name, mess);
	}
}