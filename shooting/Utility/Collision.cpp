#include "Collision.h"
#include "../Object/Object.h"
#include <algorithm>  
#include <iterator>   

using namespace std;
using namespace DirectX::SimpleMath;

// 静的変数の初期化
Collision *Collision::m_collision = nullptr;

/// <summary>
/// コンストラクタ
/// </summary>
Collision::Collision(){}

/// <summary>
/// 実体化
/// </summary>
/// <returns>実体</returns>
Collision * Collision::GetInstance()
{
	if (m_collision == nullptr)
	{
		m_collision = new Collision();
	}
	return m_collision;
}

/// <summary>
/// 削除
/// </summary>
void Collision::Destroy()
{
	if (m_collision != nullptr)
	{
		delete m_collision;
		m_collision = nullptr;
	}
}

/// <summary>
/// 登録
/// </summary>
/// <param name="_group">グループ</param>
/// <param name="object">登録したいもの</param>
/// <returns>失敗か成功か</returns>
bool Collision::Entry(Group group, Object *object)
{
	Key tmpKey = { group,object };

	vector<Key>::iterator cIter = find(m_group.begin(), m_group.end(),tmpKey);
	if (cIter == m_group.end())
	{
		m_group.push_back(tmpKey);
		return true;
	}
	return false;
}

/// <summary>
/// 当たり判定
/// </summary>
void Collision::ExecHitCheck()
{
	for (vector<Key>::iterator ita = m_group.begin(); ita != m_group.end(); ita++)
	{
		for (vector<Key>::iterator itb = m_group.begin(); itb != m_group.end(); itb++)
		{
			if (ita->group != itb->group)
			{
				if (CircleCollision(ita->object, itb->object))
				{
					ita->object->SetHitFlag(itb->group);
					itb->object->SetHitFlag(ita->group);
				}
			}
		}
	}
}

/// <summary>
/// リスト全破棄
/// </summary>
void Collision::Reset()
{
	
}

/// <summary>
/// 矩形当たり判定
/// </summary>
/// <param name="_a">対象A</param>
/// <param name="_b">対象B</param>
/// <returns>判定結果</returns>
bool Collision::AABB(Object * a, Object * b)
{
	float ra = a->GetPosition().x + a->GetSize().x / 2;
	float la = a->GetPosition().x - a->GetSize().x / 2;
	float ta = a->GetPosition().y - a->GetSize().y / 2;
	float ba = a->GetPosition().y + a->GetSize().y / 2;

	float rb = b->GetPosition().x + b->GetSize().x / 2;
	float lb = b->GetPosition().x - b->GetSize().x / 2;
	float tb = b->GetPosition().y - b->GetSize().y / 2;
	float bb = b->GetPosition().y + b->GetSize().y / 2;

	if ((ra > lb) && (la < rb) && (ba > tb) && (ta < bb))	return true;
	return false;
}

/// <summary>
/// 円と円の当たり判定
/// </summary>
/// <param name="_a">物体A</param>
/// <param name="_b">物体B</param>
/// <returns></returns>
bool Collision::CircleCollision(Object * _a, Object * _b)
{
	if ((_a->GetPosition().x - _b->GetPosition().x) * (_a->GetPosition().x - _b->GetPosition().x) +
		(_a->GetPosition().y - _b->GetPosition().y) * (_a->GetPosition().y - _b->GetPosition().y) <=
		(_a->GetRadius() + _b->GetRadius()) * (_a->GetRadius() + _b->GetRadius()))
	{
		return true;
	}
	return false;
}

/// <summary>
/// 特定のオブジェクトの削除
/// </summary>
/// <param name="_group">グループ</param>
/// <param name="_object">対象</param>
void Collision::ListDelete(Group group ,Object * _object)
{
	Key tmpKey = { group,_object };
	vector<Key>::iterator cIter = find(m_group.begin(), m_group.end(), tmpKey);
	if(cIter != m_group.end()) m_group.erase(cIter);
}