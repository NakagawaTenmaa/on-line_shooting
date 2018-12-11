#include "PlayScene.h"
#include "../Object/Player.h"
#include "../Object/EnemyManager.h"
#include "../Utility/Collision.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "../Utility/Score.h"
#include "../Common/DrawManager.h"

using namespace Scene;

/// <summary>
/// コンストラクタ
/// </summary>
PlayScene::PlayScene()
{
	m_player = new Player();
	m_enemyManager = new EnemyManager(m_player);

	Draw::DrawManager::GetInstance()->LoadTexture(m_back, L"Resources/playback.png");
	m_back.SetRect(600, 800);
	m_back.SetColor(0.1f);
	m_back.SetOrigin(0, 0);
	m_back.SetPos(0, 0);
}

/// <summary>
/// デストラクタ
/// </summary>
PlayScene::~PlayScene()
{
	if (m_player != nullptr)
	{
		delete m_player;
		m_player = nullptr;
	}
	if (m_enemyManager != nullptr)
	{
		delete m_enemyManager;
		m_enemyManager = nullptr;
	}
}

/// <summary>
/// 更新
/// </summary>
/// <returns></returns>
void PlayScene::Update()
{
	// 敵の更新
	m_enemyManager->Update();
	// 当たり判定更新
	Collision::GetInstance()->ExecHitCheck();
	// プレイヤーの更新
	if (m_player != nullptr)
	{
		if (!m_player->Update())
		{
			delete m_player;
			m_player = nullptr;


			// ハイスコアの更新
			Score::GetInstance()->SeveHighScore();
			Score::GetInstance()->ReScore();

			// タイトルシーンに移行
			Scene::SceneManager::GetInstance()->ChangeScene(new TitleScene());
		}
	}
}

/// <summary>
/// 描画
/// </summary>
void PlayScene::Render()
{
	// 背景
	Draw::DrawManager::GetInstance()->Render(m_back);

	// プレイヤーの描画
	if (m_player != nullptr)
	{
		m_player->Render();
	}
	if (m_enemyManager != nullptr)
	{
		m_enemyManager->Render();
	}
	// スコアの描画
	Score::GetInstance()->Render(DirectX::SimpleMath::Vector2(10, 10));
}
