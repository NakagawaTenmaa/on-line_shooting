#pragma once

#include <Windows.h>
#include <string>
#include "picojson.h"

/// <summary>
/// Json関係機能
/// </summary>
class Json
{
public:
	// 敵情報のJson作成
	static void MakeJson(int _id, std::string _png, RECT _rect, picojson::object &_seve);
	// Jsonの分解
	static std::string JsonToData(std::string _data);
	// ファイルへの書き込み
	static void FileSeve(std::string _file, picojson::array _data);
	// Jsonのパース
	static std::map<std::string, picojson::value> Parse(std::string _data);
	static picojson::array StrToVal(std::string _data);
private:

};