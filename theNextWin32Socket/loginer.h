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
		 * ���ʱ����
		 */
		const static int checkTime = 300;
	private:
		/**
		* @brief ������Ϣ
		* ��Ϣ����:
		* - "ip"       IP��ַ
		* - "mac"      MAC��ַ
		* - "name"     �����ǳ�
		*/
		::nlohmann::json information;
		/**
		* @brief �û������û�״����ѯ
		* ״������:
		* - "ip"       IP��ַ
		* - "mac"      MAC��ַ
		* - "lastTime" ��һ�μ��ʱ��
		*/
		::std::map<string, ::nlohmann::json> loginers;
		/**
		 * �������˼����Ϣ�߳�
		 */
		::theNextSocket::theNextThread check;
		/**
		 * ��������TCP��Ϣ�߳�
		 */
		::theNextSocket::theNextThread accept;
		/**
		 * �����������������������������״��
		 */
		::theNextSocket::theNextThread online;
	};
}