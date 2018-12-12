#include "Enemy.h"
#include "../Common/DrawManager.h"
#include "../Utility/Collision.h"
#include "../Utility/Score.h"
//#include "../Item/ItemList.h"

using namespace DirectX::SimpleMath;


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_pos">位置</param>
/// <param name="_speed">速さ</param>S
/// <param name="_hp">体力</param>
/// <param name="_id">ID</param>
Enemy::Enemy(DirectX::SimpleMath::Vector2 _pos, float _speed, int _hp, int _id,int _score)
{
	m_score = _score;
	m_hp = _hp;
	m_date.speed = _speed;

	Draw::DrawManager::GetInstance()->LoadTexture(m_image, L"Resources/images/enemy.png");
	
	m_size = Vector2(128, 128);
	
	// 画像の切り取り
	switch (_id)
	{
	case 0:	m_image.SetRect(0, 0, (LONG)m_size.x, (LONG)m_size.y);						break;
	case 1:	m_image.SetRect((LONG)m_size.x, 0, (LONG)m_size.x * 2, (LONG)m_size.y);			break;
	case 2:	m_image.SetRect(0, (LONG)m_size.y, (LONG)m_size.x, (LONG)m_size.y * 2);			break;
	case 3:	m_image.SetRect((LONG)m_size.x, (LONG)m_size.y, (LONG)m_size.x * 2, (LONG)m_size.y * 2);break;
	default:																break;
	}	

	m_image.SetOrigin(m_size.x / 2, m_size.y / 2);
	m_date.vel = Vector2::Zero;

	m_date.r = 70;
	m_date.position = _pos;
	m_image.SetPos(m_date.position);

	// 当たり判定登録
	Collision::GetInstance()->Entry(ENEMY, this);
	m_hitFlag = NOME;
}

/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy()
{
	// 当たり判定解除
	Collision::GetInstance()->ListDelete(ENEMY, this);
}

/// <summary>
/// 更新処理
/// </summary>
bool Enemy::Update()
{
	m_date.vel.y = m_date.speed;
	m_date.position += m_date.vel;
	if (m_date.position.y  > 900) {
		return false;
	}

	if (m_hp <= 0)
	{
		return false;
	}
	return true;
}

/// <summary>
/// 描画
/// </summary>
void Enemy::Render()
{
	m_image.SetPos(m_date.position);
	Draw::DrawManager::GetInstance()->Render(m_image);
}

/// <summary>
/// ダメージ
/// </summary>
/// <param name="_val">受ける量</param>
void Enemy::Damage(int _val)
{
	// 弾に当たった時
	if (m_hitFlag == BULLET)
	{
		m_hp -= _val;
		if (m_hp <= 0)
		{
			Score::GetInstance()->AddScore(m_score);
		}
		else
		{
			SetHitFlag(NOME);
		}
	}
}
