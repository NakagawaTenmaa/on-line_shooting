#include "EnemyManager.h"
#include <map>
#include "Enemy.h"
#include "../NetWork/picojson.h"
#include "../NetWork/Http.h"
#include "../NetWork/Json.h"

//#include "../Utility/Collision.h"
using namespace DirectX::SimpleMath;

// 静的変数の初期化
int EnemyManager::MAX_ENEMY = 5;
int EnemyManager::POP_ENEMY = 4;

/// <summary>
/// コンストラクタ
/// </summary>
EnemyManager::EnemyManager()
{
	// 敵の種類	(DBのカラムから取得 理想)
	m_size = 4;
	m_data.resize(m_size, nullptr);

	// データを取得し登録
	NetWork::Http::GetInstance()->Initialize();
	std::string tmp = NetWork::Http::GetInstance()->GetData("/php/shooting/EnemyList.php");
	picojson::array data = Json::StrToVal(Json::JsonToData(Json::JsonToData(tmp)));
	for (int i = 0; i < m_size; i++)
	{
		picojson::object &object = data[i].get<picojson::object>();
		int hp = atoi(object["hp"].get<std::string>().c_str());
		int id = atoi(object["id"].get<std::string>().c_str());
		int score = atoi(object["score"].get<std::string>().c_str());
		m_data[i] = new EnemyData(id, hp, score);
	}

	// 一度の出現数設定
	m_enemyList.resize(MAX_ENEMY, nullptr);

	// 経過時間の初期化
	m_timer = 0;
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyManager::~EnemyManager()
{
	// 敵の削除
	for (std::vector<Enemy*>::iterator it = m_enemyList.begin(); it != m_enemyList.end(); it++)
	{
		if ((*it) != nullptr)
		{
			delete (*it);
			(*it) = nullptr;
		}
	}

	for (int i = 0; i < m_size; i++)
	{
		delete m_data[i];
		m_data[i] = nullptr;
	}
}

/// <summary>
/// 更新
/// </summary>
/// <returns></returns>
bool EnemyManager::Update()
{
	// 時間のカウント
	int time = Timer();
	m_timer += time;

	int k = 0;
	for (std::vector<Enemy*>::iterator it = m_enemyList.begin(); it != m_enemyList.end(); it++, k++)
	{
		// 敵の更新
		if ((*it) != nullptr)
		{
			if (!(*it)->Update())
			{
				delete (*it);
				(*it) = nullptr;
			}
		}
		else if (m_timer >= POP_ENEMY)
		{
			// 敵の出現
			EnemyData *tmp = m_data[rand() % 4];
			(*it) = new Enemy(Vector2(120.0f * (float)k + 60.0f, 0.0f), 5.0f, tmp->hp, tmp->id, tmp->score);
			if (k == MAX_ENEMY - 1)
			{
				m_timer = 0;
			}
		}
	}
	return true;
}

/// <summary>
/// 描画
/// </summary>
void EnemyManager::Render()
{
	// 敵の描画
	for (std::vector<Enemy*>::iterator it = m_enemyList.begin(); it != m_enemyList.end(); it++)
	{
		if ((*it) != nullptr)
		{
			(*it)->Render();
		}
	}
}

/// <summary>
/// 経過時間のcount
/// </summary>
/// <returns>1秒立つと1</returns>
int EnemyManager::Timer()
{
	static int time = 0;
	time += 1;
	if (time >= 60) {
		time = 0;
		return 1;
	}
	return 0;
}
