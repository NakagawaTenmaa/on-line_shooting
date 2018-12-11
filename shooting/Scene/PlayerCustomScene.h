#pragma once
#include "SceneBase.h"

namespace Scene
{
	/// <summary>
	/// プレイヤーの強化シーン
	/// </summary>
	class PlayerCustomScene : public SceneBase
	{
	public:
		// コンストラクタ
		PlayerCustomScene();
		// デストラクタ
		~PlayerCustomScene();

		// 描画
		void Update() override;
		// 更新
		void Render() override;
	private:

	};
};