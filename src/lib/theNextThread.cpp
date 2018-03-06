#include "theNextThread.h"
#include <iostream>
using namespace std;
namespace theNextSocket {
DWORD ThreadProc(LPVOID lpParam) {
    theNextThread* th = (theNextThread*)lpParam;
    while (th->NeedRun()) {
        th->fun();
        Sleep(th->getInterval());
    }
    return 0;
}
theNextThread::~theNextThread() {
    CloseHandle(hThread);
}
bool theNextThread::hasStop() {
    LPDWORD lpExitCode;
    return !GetExitCodeThread(hThread,lpExitCode);
}
void theNextThread::setiInterval(int interval) {
    std::lock_guard<std::mutex> lock(mutex);
    this->timeInterval = interval;
}
int theNextThread::getInterval() {
    return this->timeInterval;
}
bool theNextThread::NeedRun() {
    std::lock_guard<std::mutex> lock(mutex);
    return this->needRun;
}
theNextThread::theNextThread(const std::function<void(void)>& func):fun(func) {
    timeInterval = 0;
    needRun = true;
    hThread = CreateThread(NULL,0,ThreadProc,this,0,&(this->threadID));
    // fun = func;
}
void theNextThread::stop() {
    CloseHandle(hThread);
}

}