#pragma once

#include <winsock.h>
#include <wininet.h>
#include <map>
#include <string>
#include <regex>
#include "picojson.h"

#pragma comment(lib,"wininet.lib")

namespace NetWork
{
	/// <summary>
	/// Http通信
	/// </summary>
	class Http
	{
	public:
		// デストラクタ
		~Http();
		// 実体化
		static Http* GetInstance();
		// 削除
		static void DeleteInstance();
		// 通信準備
		void Initialize();

		// データの取得
		std::string GetData(std::string _url);
		// データの送信
		std::string SendData(std::map<std::string, std::string> _data, std::string _url);
		// Png画像の読み込み
		void PngLoad(std::string _url, std::string _fileName);
		// ログイン
		std::string Login(std::string _id, std::string _pass);

		std::string GetUserId() {
			return m_userId; 
		}
	private:
		// コンストラクタ
		Http();
		// コピーコンストラクタ
		Http& operator=(Http _val) {}

		// 正規表現用
		std::vector<std::string> Search(std::string const & text, std::regex const & re);
		std::vector<std::string> Match(std::string const & text, std::regex const & re);
		std::string GetCookies();

	private:
		// 自身の実体
		static Http *m_instance;

		// WinSock
		WSADATA m_data;
		// socket
		SOCKET m_soc;
		LPHOSTENT m_lpHost;
		SOCKADDR_IN m_sockAdd;
		// HTTPの設定
		static char m_sever[256];
		// ポート番号
		static char m_port[256];
		// 読み込み画像の拡張子
		static std::string m_extension;
		// 読み込み先
		static std::string m_address;
		// 保存先
		static std::string m_seveAdd;

		unsigned short m_portNo;
		unsigned int m_addr;

		// sessionIdの保管庫
		//std::string m_sesid;
		std::map<std::string, std::string> m_cookies;
		// ユーザーID
		std::string m_userId;
	};
};