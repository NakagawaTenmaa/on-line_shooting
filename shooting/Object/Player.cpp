#include <iostream>
#include "Player.h"
#include "../Common/InputManager.h"
#include "../Common/DrawManager.h"
#include "../NetWork/Http.h"
#include "../NetWork/Json.h"
#include "../Utility/Collision.h"

using namespace std;
using namespace DirectX::SimpleMath;

// 静的変数の初期化
const int Player::BULLET_SIZE = 100;

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
{
	m_size = Vector2(50, 50);
	
	// プレイヤーの初期化データ取得し設定
	NetWork::Http::GetInstance()->Initialize();
	std::map<std::string, picojson::value> initializeData = Json::Parse(NetWork::Http::GetInstance()->GetData("/php/shooting/PlayerConfig.php"));
	m_date.position = Vector2((float)initializeData["posx"].get<double>(), (float)initializeData["posy"].get<double>());
	m_date.speed = (float)initializeData["speed"].get<double>();
	m_date.vel = Vector2::Zero;
	m_date.r = 50 / 2;
	m_power = 1;

	// 描画設定
	Draw::DrawManager::GetInstance()->LoadTexture(m_image, L"Resources/player.png");
	m_image.SetPos(m_date.position);
	m_image.SetRect((LONG)m_size.x, (LONG)m_size.y);
	m_image.SetOrigin(m_size.x / 2, m_size.y / 2);
	
	// 弾の初期化
	m_bullet.resize(BULLET_SIZE, nullptr);
	m_timer = 0;

	// 当たり判定登録
	Collision::GetInstance()->Entry(PLAYER, this);
	m_hitFlag = NOME;
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	// 当たり判定解除
	Collision::GetInstance()->ListDelete(PLAYER, this);
	// 弾の削除
	for (vector<Bullet*>::iterator it = m_bullet.begin(); it != m_bullet.end(); it++)
	{
		if ((*it) != nullptr)
		{
			delete (*it);
			(*it) = nullptr;
		}
	}
}

/// <summary>
/// 更新
/// </summary>
/// <returns></returns>
bool Player::Update()
{
	m_date.vel = Vector2::Zero;
	m_timer++;

	// 移動処理
	if (Input::InputManager::GetInstance()->GetKeyState().Right && (m_date.position.x < 600 - m_size.x / 2))
	{
		m_imageState = 0x01;
		m_date.vel.x = m_date.speed;
	}
	else if (Input::InputManager::GetInstance()->GetKeyState().Left && (m_date.position.x > 0 + m_size.x / 2))
	{
		m_imageState = 0x02;
		m_date.vel.x = -m_date.speed;
	}
	else
	{
		m_imageState = 0x00;
	}
	
	for (vector<Bullet*>::iterator it = m_bullet.begin(); it != m_bullet.end(); it++)
	{
		// 弾の更新
		if ((*it) != nullptr)
		{
			if (!(*it)->Update())
			{
				delete (*it);
				(*it) = nullptr;
			}
		}
		// 弾の出現
		if (m_timer >= 10)
		{
			if ((*it) == nullptr)
			{
				(*it) = new Bullet(m_date.position);
				m_timer = 0;
				break;
			}
		}
	}

	// 当たった時の処理
	if (m_hitFlag  == ENEMY)
	{
		return false;
	}
	// アイテムをとった時
	else if (m_hitFlag == ITEM)
	{
		m_power += 1;
		SetHitFlag(NOME);
	}

	// 描画位置の決定
	m_date.position += m_date.vel;
	m_image.SetPos(m_date.position);
	
	return true;
}

/// <summary>
/// 描画
/// </summary>
void Player::Render()
{
	for (vector<Bullet*>::iterator it = m_bullet.begin(); it != m_bullet.end(); it++)
	{
		if ((*it) != nullptr) 
		{
			(*it)->Render();
		}
	}

	m_image.SetRect(m_size.x * m_imageState, m_size.y * 0, m_size.x * m_imageState + m_size.x, m_size.y * 0 + m_size.y);
	Draw::DrawManager::GetInstance()->Render(m_image);
}