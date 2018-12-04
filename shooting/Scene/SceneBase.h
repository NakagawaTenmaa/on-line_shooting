#pragma once

namespace Scene
{
	/// <summary>
	/// シーンベース
	/// </summary>
	class SceneBase
	{
	public:
		// コンストラクタ
		SceneBase() {}
		// デストラクタ
		virtual ~SceneBase() {}

		// 描画
		virtual bool Update() = 0;
		// 更新
		virtual void Render() = 0;

		// 描画開始
		virtual void RenderStart();
		// 終了
		virtual void RenderEnd();
	private:
	};
};