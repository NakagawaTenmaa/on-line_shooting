#pragma once
#include <vector>
#include "../Object/Object.h"

/// <summary>
/// 判定するグループ
/// </summary>
enum Group
{
	PLAYER,
	BULLET,
	ENEMY,
	ITEM,

	NOME
};


class Object;
class CollisionData;

/// <summary>
/// 登録される情報
/// </summary>
struct Key
{
	Group group;
	Object *object;
	DirectX::SimpleMath::Rectangle rect;

	bool operator== (Key _key)
	{
		if ((group == _key.group) && object == _key.object)	return true;
		else return false;
	}
};

/// <summary>
/// 当たり判定
/// </summary>
class Collision
{
public:
	// 実体化
	static Collision *GetInstance();
	// 削除
	static void Destroy();
	// 登録関数
	bool Entry(Group _group, Object* _object);
	// 衝突判定
	void ExecHitCheck();
	// リスト削除
	void ListDelete(Group _group,Object *_object);
private:
	// 自分
	static Collision *m_collision;
	// コンストラクタ
	Collision();
	// 登録用変数
	std::vector<Key> m_group;
	// 登録をリセットする関数
	void Reset();
	// GameObject同士の衝突判定関数
	bool AABB(Object *_a, Object *_b);
	// 円と円の当たり判定
	bool CircleCollision(Object *_a, Object *_b);
private:
};

