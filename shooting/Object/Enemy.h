#pragma once

#include "Object.h"
#include "../Animation/Animation.h"

/// <summary>
/// 敵クラス
/// </summary>
class Enemy : public Object
{
public:
	// コンストラクタ
	Enemy(DirectX::SimpleMath::Vector2 _pos, float _speed, int _hp, int _id, int _score);
	// デストラクタ
	~Enemy();

	// 更新
	bool Update();
	// 描画
	void Render();
private:
	// Hp
	int m_hp;
	// スコア
	int m_score;
};