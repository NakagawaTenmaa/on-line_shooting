#pragma once

#include <list>
#include "SceneBase.h"

namespace Scene
{
	/// <summary>
	/// シーンマネージャー
	/// </summary>
	class SceneManager
	{
	public:
		// デストラクタ
		~SceneManager();

		// 実体化
		static SceneManager* GetInstance();
		// 実体の削除
		static void DeleteInstance();

		// 更新
		void Update();
		// 描画
		void Renrer();

		// シーンの追加
		void ChangeScene(SceneBase* _scene);
	private:
		// コンストラクタ
		SceneManager();
		// コピーコンストラクタ
		SceneManager& operator=(SceneManager _val) {}
	private:
		// 自身のポインタ
		static SceneManager* m_instance;
		// 現在のシーン
		SceneBase* m_scene;
	};
};