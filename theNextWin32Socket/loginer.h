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
		void chatTo(std::string name, std::string message);
		bool tryChat(std::string name);
		const std::map<string, ::nlohmann::json>& getLoginerss() {
			return this->loginers;
		}
		const static int TCP_PORT = 12833;
		const static int UDP_PORT = 12800;
		/**
		 * 检查时间间隔
		 */
		const static int checkTime = 300;
	private:
		/**
		* @brief 个人信息
		* 信息包括:
		* - "ip"       IP地址
		* - "mac"      MAC地址
		* - "name"     个人昵称
		*/
		::nlohmann::json information;
		/**
		* @brief 用户名和用户状况查询
		* 状况包括:
		* - "ip"       IP地址
		* - "mac"      MAC地址
		* - "lastTime" 上一次检查时间
		*/
		::std::map<string, ::nlohmann::json> loginers;
		/**
		 * 接收他人检查信息线程
		 */
		::theNextSocket::theNextThread check;
		/**
		 * 接收他人TCP消息线程
		 */
		::theNextSocket::theNextThread accept;
		/**
		 * 发送在线心跳包，并检查他人在线状况
		 */
		::theNextSocket::theNextThread online;
	};
}