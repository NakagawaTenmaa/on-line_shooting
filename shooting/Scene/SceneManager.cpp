#include "SceneManager.h"

using namespace Scene;

// 静的変数の初期化
SceneManager* SceneManager::m_instance = nullptr;

// 名前空間
using namespace std;

/// <summary>
/// デストラクタ
/// </summary>
SceneManager::~SceneManager()
{
	for (list<SceneBase*>::iterator it = m_list.begin(); it != m_list.end(); it++)
	{
		delete (*it);
		(*it) = nullptr;
	}
	m_list.clear();
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
	// 消す予定のシーン削除
	RemoveTask();

	for (list<SceneBase*>::iterator it = m_list.begin(); it != m_list.end(); it++)
	{
		if (!(*it)->Update())
		{
			// 削除予約
			m_removeList.push_back((*it));
		}
	}
}

/// <summary>
/// 描画
/// </summary>
void SceneManager::Renrer()
{
	for (list<SceneBase*>::iterator it = m_list.begin(); it != m_list.end(); it++)
	{
		(*it)->RenderStart();
		(*it)->Render();
		(*it)->RenderEnd();
	}
}


/// <summary>
/// シーンの追加
/// </summary>
/// <param name="_task"> 追加したいタスク </param>
void SceneManager::AddScene(SceneBase * _task)
{
	m_list.push_back(_task);
}

/// <summary>
/// シーンの削除
/// </summary>
void SceneManager::RemoveTask()
{
	for (list<SceneBase*>::iterator it = m_removeList.begin(); it != m_removeList.end(); it++)
	{
		m_list.remove((*it));
		delete (*it);
		(*it) = nullptr;
	}
	// 削除リストを空にする
	m_removeList.clear();
}

