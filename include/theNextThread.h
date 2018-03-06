#pragma once
#include <functional>
#include <Windows.h>
#include <mutex>
namespace theNextSocket {
class theNextThread {
public:
    /**
     * @brief 线程类的构造函数
     * 输入的函数将被重复调用直至线程运行终止
     */
    theNextThread(const std::function<void(void)>&);
    /**
     * @brief 析构函数
     * 线程会在析构函数调用后终止
     */
    virtual ~theNextThread();
    /**
     * @brief 检查线程是否已经停止运行
     *
     * @return true 已经停止运行
     * @return false 尚未停止运行
     */
    bool hasStop();
    /**
     * @brief 通知线程终止运行
     * 线程会在完成本次循环之后终止
     *
     */
    void stop();
    /**
     * @brief 设置线程循环调用的间隔时间
     *
     * @param erval 间隔时间（以微秒计）
     */
    void setiInterval(int interval);
    /**
     * @brief 获取当前线程循环调用间隔时间
     *
     * @return int 当前线程循环调用的间隔时间
     */
    int getInterval();
    /**
     * @brief 检查当前线程是否还会继续运行
     *
     * @return true 线程会持续循环
     * @return false 线程已经结束或者将在一次循环后结束
     */
    bool NeedRun();
    /**
     * @brief 线程循环调用的函数
     *
     */
    const std::function<void(void)> fun;
private:
    // 线程锁
    std::mutex mutex;
    bool needRun;
    int timeInterval;
    HANDLE hThread;
    DWORD threadID;
};
}