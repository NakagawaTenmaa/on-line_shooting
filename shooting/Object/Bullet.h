#pragma once

#include "Object.h"

/// <summary>
/// 弾クラス
/// </summary>
class Bullet : public Object
{
public:
	// コンストラクタ
	Bullet();
	Bullet(DirectX::SimpleMath::Vector2 _pos);
	// デストラクタ
	~Bullet();

	// 移動
	bool Update();
	// 描画
	void Render();
private:
};