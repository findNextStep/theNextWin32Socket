#pragma once
#include "theNextThread.h"
#include "json.hpp"
#include <string>
#include <map>
namespace theNextChater {
using ::std::string;
class loginer {
public:
    loginer(string nickname);
    virtual ~loginer();
    const std::map<string,::nlohmann::json>& getLoginerss() {
        return this->loginers;
    }
private:
    ::nlohmann::json information;
    /**
     * @brief 用户名和用户状况查询
     * 状况包括:
     * - "ip"       IP地址
     * - "mac"      MAC地址
     * - "lastTime" 上一次检查时间
     */
    ::std::map<string,::nlohmann::json> loginers;
    ::theNextSocket::theNextThread check;
    ::theNextSocket::theNextThread accept;
};
}