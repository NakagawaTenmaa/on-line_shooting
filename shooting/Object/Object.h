#pragma once

#include "../Common/DrawData.h"

enum Group;

/// <summary>
/// オブジェクトの基本データ
/// </summary>
struct ObjectDate
{
	// 位置
	DirectX::SimpleMath::Vector2 position;
	DirectX::SimpleMath::Vector2 vel;

	float speed;
	float r;
};

/// <summary>
/// ゲームオブジェクト
/// </summary>
class Object
{
public:
	// コンストラクタ
	Object();
	// デストラクタ
	virtual ~Object();

	// 位置の取得
	DirectX::SimpleMath::Vector2 GetPosition() { return m_date.position; }
	// サイズの取得
	DirectX::SimpleMath::Vector2 GetSize() { return m_size; }
	// 半径の取得
	float GetRadius() { return m_date.r; }

	// 当たり判定の取得
	void SetHitFlag(Group _flag) { m_hitFlag = _flag; }
protected:
	// データ
	ObjectDate m_date;
	// 画像データ
	Draw::DrawData m_image;
	// オブジェクトサイズ
	DirectX::SimpleMath::Vector2 m_size;
	// 当たり判定Flag
	Group m_hitFlag;
};