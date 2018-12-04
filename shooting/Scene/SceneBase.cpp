#include "SceneBase.h"
#include "../Common/DrawManager.h"

/// <summary>
/// 描画開始
/// </summary>
void Scene::SceneBase::RenderStart()
{
	Draw::DrawManager::GetInstance()->Begin();
}

/// <summary>
/// 描画終了
/// </summary>
void Scene::SceneBase::RenderEnd()
{
	Draw::DrawManager::GetInstance()->End();
}
