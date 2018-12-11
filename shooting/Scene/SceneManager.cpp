#include "SceneManager.h"

using namespace Scene;

// 静的変数の初期化
SceneManager* SceneManager::m_instance = nullptr;

// 名前空間
using namespace std;

/// <summary>
/// コンストラクタ
/// </summary>
Scene::SceneManager::SceneManager()
{
	m_scene = nullptr;
}

/// <summary>
/// デストラクタ
/// </summary>
SceneManager::~SceneManager()
{
	delete m_scene;
	m_scene = nullptr;
}

/// <summary>
/// 実体化
/// </summary>
/// <returns> 自身のポインタ </returns>
SceneManager * SceneManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new SceneManager();
	}
	return m_instance;
}

/// <summary>
/// 実体の削除
/// </summary>
void SceneManager::DeleteInstance()
{
	delete m_instance;
	m_instance = nullptr;
}

/// <summary>
/// 更新
/// </summary>
void SceneManager::Update()
{
	// 更新
	m_scene->Update();
}

/// <summary>
/// 描画
/// </summary>
void SceneManager::Renrer()
{
	m_scene->RenderStart();
	m_scene->Render();
	m_scene->RenderEnd();
}

/// <summary>
/// シーンの変更
/// </summary>
/// <param name="_scene"></param>
void Scene::SceneManager::ChangeScene(SceneBase * _scene)
{
	// チェック
	if (m_scene != nullptr)
	{
		delete m_scene;
		m_scene = nullptr;
	}
	// 新規シーン
	m_scene = _scene;
}


