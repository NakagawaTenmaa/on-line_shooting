#pragma once

#include <vector>
#include "Object.h"
#include "Bullet.h"

/// <summary>
/// プレイヤークラス
/// </summary>
class Player : public Object
{
public:
	// コンストラクタ
	Player();
	// デストラクタ
	~Player();

	// 更新
	bool Update();
	// 描画
	void Render();
private:
	// 弾の管理
	std::vector<Bullet*> m_bullet;
	static const int BULLET_SIZE;
	int m_timer;
	int m_power;

	// 画像の状態
	byte m_imageState;
};