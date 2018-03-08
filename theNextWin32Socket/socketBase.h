#pragma once
#include <string>
#include <memory>
#include <WinSock2.h>
#include <windows.h>
namespace theNextSocket {
/**
 * @brief 通过全局使用计数统一管理webAPI的获取和释放
 * 
 */
class WSAManager {
public:
    WSAManager();
    virtual ~WSAManager();
private:
    static int count;
};
/**
 * @brief sorcket封装接口
 *
 */
class socketBase {
public:
    socketBase():manage() {}
    /**
     * @brief 接收数据
     *
     * @param length 接收数据的长度，如果长度为0，则由程序自己决定
     * @return std::string 接收到的数据
     */
    virtual std::string receive(int length = 0) = 0;
    /**
     * @brief 发送数据
     *
     * @param content 发送的数据内容
     */
    virtual void send(std::string content) = 0;

private:
    // web服务计数
    WSAManager manage;

};
const int defalut_port = 12800;
}