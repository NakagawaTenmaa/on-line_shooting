#pragma once

#include "SceneBase.h"

namespace Scene
{
	/// <summary>
	/// リソースダウンロードシーン
	/// </summary>
	class DownloadScene : public SceneBase
	{
	public:
		// コンストラクタ
		DownloadScene();
		// デストラクタ
		~DownloadScene();

		// 描画
		void Update() override;
		// 更新
		void Render() override;
	private:

	};
};