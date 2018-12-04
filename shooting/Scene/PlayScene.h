#pragma once

#include "SceneBase.h"
#include "../Common/DrawData.h"

class Player;
class EnemyManager;

namespace Scene
{
	/// <summary>
	/// プレイシーン
	/// </summary>
	class PlayScene : public SceneBase
	{
	public:
		// コンストラクタ
		PlayScene();
		// デストラクタ
		~PlayScene();

		// 更新
		bool Update() override;
		// 描画
		void Render() override;
	private:
		// プレイヤー
		Player* m_player;
		// 敵
		EnemyManager* m_enemyManager;

		// 背景
		Draw::DrawData m_back;
	};
}