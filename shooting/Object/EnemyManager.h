#pragma once

#include <list>
#include <vector>
#include "Enemy.h"
#include "../Animation/Animation.h"

class Player;

/// <summary>
/// 敵のステータス表
/// </summary>
struct EnemyData
{
	int id;
	int hp;
	int score;

	int speed;
	int size_x;
	int size_y;
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_id">ID</param>
	/// <param name="_hp">体力</param>
	/// <param name="_score">スコア</param>
	EnemyData(int _id, int _hp, int _score)
	{
		id = _id;
		hp = _hp;
		score = _score;
	}
};

/// <summary>
/// 敵のマネージャー
/// </summary>
class EnemyManager
{
public:
	// コンストラクタ
	EnemyManager(Player *_player);
	// デストラクタ
	~EnemyManager();

	// 更新
	bool Update();
	// 描画
	void Render();

	// getter
	EnemyData GetData(int _index) { return *m_data[_index]; }
	int GetSize() { return m_data.size(); }
private:
	int Timer();
private:
	// 敵の情報リスト
	std::vector<EnemyData*> m_data;
	std::vector<EnemyData*> m_metData;
	// 敵のリスト
	std::vector<Enemy*> m_enemyList;
	//std::vector<Meteorite*> m_meteoList;
	// 経過時間
	int m_timer;
	// 敵の量
	int m_size;
	// 敵の最大数
	static int MAX_ENEMY;
	// 敵の出現間隔
	static int POP_ENEMY;
	// 爆発リスト
	std::list<Animation*> m_explosion;
	// プレイヤー
	Player *m_player;
};