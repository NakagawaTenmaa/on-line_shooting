#include "Bullet.h"
#include "../Common/DrawManager.h"
#include "../Utility/Collision.h"

/// <summary>
/// コンストラクタ
/// </summary>
Bullet::Bullet(){}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_pos">位置</param>
Bullet::Bullet(DirectX::SimpleMath::Vector2 _pos)
{
	m_date.speed = 6;
	Draw::DrawManager::GetInstance()->LoadTexture(m_image, L"Resources/images/bullet.png");
	m_size = DirectX::SimpleMath::Vector2(25, 25);
	m_image.SetRect((LONG)m_size.x, (LONG)m_size.y);
	m_image.SetOrigin(m_size.x / 2, m_size.y / 2);
	
	m_date.vel = DirectX::SimpleMath::Vector2::Zero;
	m_date.vel.y = -m_date.speed;
	m_date.r = 15;
	m_date.position = _pos;
	
	// 当たり判定登録
	m_hitFlag = NOME;
	Collision::GetInstance()->Entry(BULLET, this);
}

/// <summary>
/// デストラクタ
/// </summary>
Bullet::~Bullet()
{
	// 当たり判定解除
	Collision::GetInstance()->ListDelete(BULLET, this);
}

/// <summary>
/// 移動
/// </summary>
bool Bullet::Update()
{
	m_date.position += m_date.vel;
	if (m_date.position.y <= 0) {
		return false;
	}

	// 敵に当たった時
	if (m_hitFlag == ENEMY)
	{
		return false;
	}
	return true;
}

/// <summary>
/// 描画処理
/// </summary>
void Bullet::Render()
{
	m_image.SetPos(m_date.position);
	Draw::DrawManager::GetInstance()->Render(m_image);
}
