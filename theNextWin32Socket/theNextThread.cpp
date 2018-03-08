#include "stdafx.h"
namespace theNextSocket {
	DWORD WINAPI ThreadProc(LPVOID lpParam) {
		theNextThread* th = (theNextThread*)lpParam;
		while (th->NeedRun()) {
			th->fun();
			Sleep(th->getInterval());
		}
		return 0;
	}
	theNextThread::~theNextThread() {
		TerminateThread(hThread, 12345);
		CloseHandle(hThread);
	}
	bool theNextThread::hasStop() {
		LPDWORD lpExitCode = 0;
		return !GetExitCodeThread(hThread, lpExitCode);
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
	theNextThread::theNextThread(const std::function<void(void)>& func) :fun(func) {
		timeInterval = 0;
		needRun = true;
		hThread = CreateThread(NULL, 0, ThreadProc, this, 0, &(this->threadID));
	}
	void theNextThread::stop() {
		needRun = false;
	}

}