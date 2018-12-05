
#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <codecvt>
#include <regex>

#include "Http.h"
#include "../Common/StreamManager.h"

using namespace std;
using namespace NetWork;

// 静的変数の初期化
Http* Http::m_instance = nullptr;
char Http::m_port[] = "80";
char Http::m_sever[] = "tenko117.verse.jp";
string Http::m_extension = ".png";
string Http::m_seveAdd = "Resources/";
string Http::m_address = "http://tenko117.verse.jp";

/// <summary>
/// デストラクタ
/// </summary>
Http::~Http() {}

/// <summary>
/// 実体化
/// </summary>
/// <returns></returns>
Http * Http::GetInstance()
{
	if (!m_instance)
	{
		m_instance = new Http();
	}
	return m_instance;
}

/// <summary>
/// 削除
/// </summary>
void Http::DeleteInstance()
{
	if (m_instance != nullptr) 
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

/// <summary>
/// 通信準備
/// </summary>
void Http::Initialize()
{
	//// 初期化
	WSAStartup(MAKEWORD(1, 1), &m_data);
	//// ソケットの作成
	m_soc = socket(PF_INET, SOCK_STREAM, 0);
	//// ホスト情報取得
	m_lpHost = gethostbyname(m_sever);
	if (m_lpHost == NULL) {
		m_addr = inet_addr(m_sever);
		m_lpHost = gethostbyaddr((char*)&m_addr, 4, AF_INET);
	}

	m_portNo = (unsigned short)atoi(m_port);
	//// Winsockの初期化
	memset(&m_sockAdd, 0, sizeof(m_sockAdd));
	m_sockAdd.sin_family = AF_INET;
	m_sockAdd.sin_port = htons(m_portNo);
	m_sockAdd.sin_addr = *((LPIN_ADDR)*m_lpHost->h_addr_list);
	connect(m_soc, (PSOCKADDR)&m_sockAdd, sizeof(m_sockAdd));
}

/// <summary>
/// データの取得
/// </summary>
/// <param name="_url"></param>
/// <returns></returns>
string Http::GetData(string _url)
{
	string str = "";
	char body[256];
	char rcv[256];

	// GETリクエスト
	sprintf_s(body, "GET http://%s%s HTTP/1.0\r\n%s\r\n”", m_sever, _url.c_str(), GetCookies().c_str());
	send(m_soc, body, (int)strlen(body), 0);

	while (true)
	{
		int re = 0;
		memset(rcv, 0, sizeof(rcv));

		re = recv(m_soc, rcv, (int)sizeof(rcv) - 1, 0);

		str += rcv;


		if (re == 0) 
		{
			break;
		}
		else if (re == SOCKET_ERROR) 
		{
			printf("エラー\n");
			break;
		}
	}

	return str;
}


/// <summary>
/// ハイスコアの記録
/// </summary>
/// <param name="_score"></param>
void Http::HighScoreSeve(int _score ,string _url)
{
	char body[256];
	char str[256];
	sprintf_s(body, "high=%d&name=%s", _score, Input::StreamManager::GetInstance()->GetId().c_str());
	sprintf_s(str, "POST http://%s%s HTTP/1.0\r\nContent-Length:%d\r\nContent-Type: application/x-www-form-urlencoded\r\n\%s\r\n%s", m_sever, _url.c_str(), strlen(body), GetCookies().c_str(), body);

	send(m_soc, str, (int)strlen(str), 0);
}

/// <summary>
/// Pngの読み込み
/// </summary>
/// <param name="_url">URL</param>
/// <param name="_fileName">保存名</param>
void Http::PngLoad(string _url, string _fileName)
{

	HINTERNET ieopen, ieurl;
	int tsize = 0;
	int rsize = 655360;
	char ch[655361];

	// 文字列の連結
	string url = m_address + _url;
	string file = m_seveAdd + _fileName + m_extension;

	// すでにある場合はスキップ
	FILE* fp = fopen(file.c_str(), "r");
	if (fp != NULL) 
	{
		fclose(fp);
		return;
	}

	fstream fs(file.c_str(), ios::out | ios::binary | ios::trunc);

	string name = "test";
	wstring wName = wstring(name.begin(), name.end());
	LPCWSTR tmpName = wName.c_str();

	wstring wUrl = wstring(url.begin(), url.end());
	LPCWSTR tmpUrl = wUrl.c_str();

	ieopen = InternetOpen(
		tmpName,
		INTERNET_OPEN_TYPE_PRECONFIG,
		NULL,
		NULL,
		0);

	ieurl = InternetOpenUrl(
		ieopen,
		tmpUrl,
		NULL,
		0,
		INTERNET_FLAG_RELOAD,
		0);

	while (1) {
		rsize = 655360;
		if (InternetReadFile(ieurl, ch, 655360, (LPDWORD)&rsize) && (rsize == 0))break;
		ch[rsize] = '\0';
		fs.write(reinterpret_cast<char*>(&ch), sizeof(ch));
		tsize += rsize;
	}
}

std::vector<std::string> Http::Search(std::string const & text, std::regex const & re)
{
	std::vector<std::string> result;

	_String_const_iterator<_String_val<_Simple_types<char>>> iter = text.cbegin();
	_String_const_iterator<_String_val<_Simple_types<char>>> end = text.cend();

	std::smatch m;

	while (std::regex_search(iter, end, m, re))
	{
		result.push_back(m.str());
		iter = m[0].second;
	}

	return result;
}

std::vector<std::string> Http::Match(std::string const & text, std::regex const & re)
{
	std::vector<std::string> result;

	std::smatch m;

	std::regex_match(text, m, re);

	for (auto && elem : m)
	{
		result.push_back(elem.str());
	}

	return result;
}

std::string NetWork::Http::GetCookies()
{
	// 何もない場合
	if (m_cookies.size() == 0) {
		return "";
	}

	string cookie = "cookie: ";
	for (map<string, string>::iterator it = m_cookies.begin(); it != m_cookies.end(); it++)
	{
		cookie += it->first + "=" + it->second + ";";
	}
	cookie += "\r\n";
	return cookie;
}


/// <summary>
/// ログイン
/// </summary>
/// <param name="_id">ID</param>
/// <param name="_poss">パスワード</param>
/// <returns></returns>
string NetWork::Http::Login(wstring _id, wstring _pass)
{
	char str[256];
	char body[256];
	char rcv[256];
	string tmp = "";
	wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
	string id = cv.to_bytes(_id);
	string pass = cv.to_bytes(_pass);
	sprintf_s(body, "userid=%s&password=%s", id.c_str(), pass.c_str());
	sprintf_s(str, "POST http://%s%s HTTP/1.0\r\nContent-Length:%d\r\nContent-Type: application/x-www-form-urlencoded\r\n%s\r\n%s", m_sever, "/php/shooting/Login.php", strlen(body), GetCookies().c_str(), body);
	send(m_soc, str, (int)strlen(str), 0);

	while (true)
	{
		int re = 0;
		memset(rcv, 0, sizeof(rcv));
		re = recv(m_soc, rcv, (int)sizeof(rcv) - 1, 0);
		tmp += rcv;

		if (re == 0)
		{
			break;
		}
		else if (re == SOCKET_ERROR)
		{
			printf("エラー\n");
			break;
		}
	}

	string retuStr = "";
	string header = tmp.substr(0, tmp.find("\r\n\r\n"));
	regex reline(R"(.+)");
	regex tag("^(.+): ?(.*)$");
	vector<string> lines = Search(header, reline);

	for (int i = 1; i < (int)lines.size(); i++) {
		string line = lines[i];
		vector<string> tags = Match(line, tag);
		string key = tags[1];
		string values = tags[2];
		if (key == "Set-Cookie") {
			unsigned int valState = values.find("=") + 1;
			unsigned int valEnd = values.find(";");
			unsigned int point = valEnd - valState;
			retuStr = values.substr(valState, point);
			m_cookies[values.substr(0, valState - 1)] = retuStr;
		}
	}


	std::string tmpData = strstr(tmp.c_str(), "\r\n\r\n\0");
	std::string data = "\r\n\r\nok\0";
	// 確認が取れない場合はfalse
	if (data == tmpData)
	{
		return retuStr;

	}
	return "";
}
