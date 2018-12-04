#include <SimpleMath.h>
#include <wchar.h>
#include <iostream>
#include <string>
#include "StreamManager.h"
#include "InputManager.h"
#include "DrawManager.h"

using namespace Input;
using namespace DirectX;

// 静的変数の初期化
StreamManager* StreamManager::m_instance = nullptr;
int StreamManager::IMAGE_SIZE = 32;

/// <summary>
/// コンストラクタ
/// </summary>
StreamManager::StreamManager()
{
	// 文字画像の読み込み
	Draw::DrawManager::GetInstance()->LoadTexture(m_strImage, L"Resources/string.png");
	m_strImage.SetOrigin(0, 0);
	m_strImage.SetRect(IMAGE_SIZE, IMAGE_SIZE);
	m_strImage.SetScale(0.8f, 0.8);
}

/// <summary>
/// 実体化
/// </summary>
/// <returns>自身のポインタ</returns>
StreamManager * StreamManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new StreamManager();
	}
	return m_instance;
}


/// <summary>
/// 実体の削除
/// </summary>
void StreamManager::DeleteInstance()
{
	if (m_instance != nullptr)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

/// <summary>
/// IDの更新
/// </summary>
void Input::StreamManager::IdUpdate()
{
	DirectX::Keyboard::Keys keys = Input::InputManager::GetInstance()->AllGet();
	if (DirectX::Keyboard::Keys::Back == keys)
	{
		if (m_strId.size() != 0)
		{
			std::vector<int*>::iterator endIt = m_strId.end() - 1;
			delete *endIt;
			*endIt = nullptr;
			m_strId.erase(endIt);
		}
	}
	else if (keys != '\0')
	{
		m_strId.push_back(new int(keys - 0x41));
	}
}

/// <summary>
/// パスの更新
/// </summary>
void Input::StreamManager::PassUpdate()
{
	DirectX::Keyboard::Keys keys = Input::InputManager::GetInstance()->AllGet();
	if (DirectX::Keyboard::Keys::Back == keys)
	{
		// バックスペース
		if (m_strPass.size() != 0)
		{
			std::vector<int*>::iterator endIt = m_strPass.end() - 1;
			delete *endIt;
			*endIt = nullptr;
			m_strPass.erase(endIt);
		}
	}
	else if (keys != '\0')
	{
		m_strPass.push_back(new int(keys - 0x41));
	}
}

/// <summary>
/// デストラクタ
/// </summary>
StreamManager::~StreamManager()
{
	
}

/// <summary>
/// 描画
/// </summary>
/// <param name="_pos">位置</param>
void StreamManager::IdRender(DirectX::SimpleMath::Vector2 _pos)
{
	// 文字列画像の描画
	int k = 0;
	int w = 6;
	m_strImage.SetPos(_pos);
	for (std::vector<int*>::iterator it = m_strId.begin(); it != m_strId.end(); it++,k++)
	{
		LONG tmp = IMAGE_SIZE * *(*it);
		LONG x = tmp % (w * (LONG)IMAGE_SIZE);
		LONG y = (tmp / (w * (LONG)IMAGE_SIZE)) * IMAGE_SIZE;
		LONG u = x + IMAGE_SIZE;
		LONG v = y + IMAGE_SIZE;

		m_strImage.SetRect(x, y, u, v);
		Draw::DrawManager::GetInstance()->Render(m_strImage);
		m_strImage.SetPos(m_strImage.GetPos().x + IMAGE_SIZE * 0.5f, m_strImage.GetPos().y);
	}
}

/// <summary>
/// 描画
/// </summary>
/// <param name="_pos">位置</param>
void Input::StreamManager::PassRender(DirectX::SimpleMath::Vector2 _pos)
{
	// 文字列画像の描画
	int k = 0;
	int w = 6;
	m_strImage.SetPos(_pos);
	for (std::vector<int*>::iterator it = m_strPass.begin(); it != m_strPass.end(); it++, k++)
	{
		LONG tmp = IMAGE_SIZE * *(*it);
		LONG x = tmp % (w * (LONG)IMAGE_SIZE);
		LONG y = (tmp / (w * (LONG)IMAGE_SIZE)) * IMAGE_SIZE;
		LONG u = x + IMAGE_SIZE;
		LONG v = y + IMAGE_SIZE;

		m_strImage.SetRect(x, y, u, v);
		Draw::DrawManager::GetInstance()->Render(m_strImage);
		m_strImage.SetPos(m_strImage.GetPos().x + IMAGE_SIZE * 0.5f, m_strImage.GetPos().y);
	}
}

/// <summary>
/// 文字の指定描画
/// </summary>
/// <param name="_pos">位置</param>
/// <param name="_str">文字</param>
void Input::StreamManager::Render(DirectX::SimpleMath::Vector2 _pos, const std::string _str)
{
	int k = 0;
	int w = 6;
	m_strImage.SetPos(_pos);
	for (size_t i = 0; i < _str.size(); i++)
	{
		if (_str[i] >= 'a' && _str[i] <= 'z')
		{
			LONG tmp = IMAGE_SIZE * (_str[i] - 0x61);
			LONG x = tmp % (w * (LONG)IMAGE_SIZE);
			LONG y = (tmp / (w * (LONG)IMAGE_SIZE)) * IMAGE_SIZE;
			LONG u = x + IMAGE_SIZE;
			LONG v = y + IMAGE_SIZE;

			m_strImage.SetRect(x, y, u, v);
			Draw::DrawManager::GetInstance()->Render(m_strImage);
			m_strImage.SetPos(m_strImage.GetPos().x + IMAGE_SIZE * 0.5f, m_strImage.GetPos().y);
		}
	}
}

/// <summary>
/// パスの文字列取得
/// </summary>
/// <returns></returns>
std::wstring Input::StreamManager::GetPass()
{
	std::wstring str = L"";
	for (std::vector<int*>::iterator it = m_strPass.begin(); it != m_strPass.end(); it++)
	{
		// 小文字変換
		str += *(*it) + 0x61;
	}

	return str;
}

/// <summary>
/// IDの文字列取得
/// </summary>
/// <returns></returns>
std::wstring Input::StreamManager::GetId()
{
	std::wstring str = L"";
	for (std::vector<int*>::iterator it = m_strId.begin(); it != m_strId.end(); it++)
	{
		// 小文字変換
		str += *(*it) + 0x61;
	}
	return str;
}
