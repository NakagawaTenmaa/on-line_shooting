#include "Json.h"

#include <iostream>
#include <fstream>

using namespace std;

/// <summary>
/// 敵情報のJson作成
/// </summary>
/// <param name="_id">ID</param>
/// <param name="_png">画像パス</param>
/// <param name="_rect">RECT</param>
/// <param name="_seve">書き込み先</param>
void Json::MakeJson(int _id, std::string _png, RECT _rect, picojson::object & _seve)
{
	picojson::object rect;
	rect.insert(make_pair("bottom", picojson::value((double)_rect.bottom)));
	rect.insert(make_pair("top", picojson::value((double)_rect.top)));
	rect.insert(make_pair("right", picojson::value((double)_rect.right)));
	rect.insert(make_pair("left", picojson::value((double)_rect.left)));

	picojson::object data;
	// idの作成
	data.insert(std::make_pair("id", picojson::value((double)_id)));
	// 画像サイズ
	data.insert(std::make_pair("rect", picojson::value(rect)));
	data.insert(make_pair("png", picojson::value(_png)));
	// 敵データの作成
	_seve.insert(std::make_pair("enemy_" + to_string(_id), data));
}

/// <summary>
/// Jsonの分解
/// </summary>
string Json::JsonToData(string _data)
{
	// データのみを取り除く
	string json = strstr(_data.c_str(), "\r\n\r\n");
	picojson::value val;
	string err = picojson::parse(val, json);

	// エラー処理
	if (!err.empty())
	{
		return string();
	}	
	return json;
}

/// <summary>
/// ファイルへの書き込み
/// </summary>
/// <param name="_file">ファイルパス</param>
/// <param name="_data">書き込むデータ</param>
void Json::FileSeve(std::string _file, picojson::array _data)
{
	ofstream file(_file);
	file << picojson::value(_data);
	file.close();
}

/// <summary>
/// Jsonのパース
/// </summary>
/// <param name="_data">分解したいデータ</param>
/// <returns>分解した結果</returns>
std::map<std::string, picojson::value> Json::Parse(std::string _data)
{
	// データのみを取り除く
	string json = strstr(_data.c_str(), "\r\n\r\n");
	picojson::value val;
	string err = picojson::parse(val, json);

	// エラー処理
	if (!err.empty())
	{
		return map<string, picojson::value>();
	}
	map<string, picojson::value> data = val.get<picojson::object>();

	return data;
}

/// <summary>
/// Jsonのパース
/// </summary>
/// <param name="_data">データ</param>
/// <returns>結果</returns>
picojson::array Json::StrToVal(std::string _data)
{
	picojson::value val;
	std::string err = picojson::parse(val, _data);
	return  val.get<picojson::array>();
}
