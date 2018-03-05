#pragma once
#include <string>
#include <array>
namespace theNextSocket {
/**
 * @brief sorcket封装接口
 *
 */
class socketBase {
public:
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
};
typedef std::array<unsigned char, 4> IPv4_t;
typedef std::array<unsigned char, 6> MAC_t;
typedef std::array<unsigned char,16> IPv6_t;
const int defalut_port = 8080;
}