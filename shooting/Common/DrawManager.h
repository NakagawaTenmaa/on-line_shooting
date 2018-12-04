#pragma once

#include <list>


#include "WICTextureLoader.h"
#include "SimpleMath.h"
#include "SpriteBatch.h"
#include "DrawData.h"

namespace Draw
{
	typedef ID3D11ShaderResourceView* DxTexture;

	/// <summary>
	/// 描画マネージャー
	/// </summary>
	class DrawManager
	{
	public:
		// デストラクタ
		~DrawManager() {}
	
		// 実体化
		static DrawManager* GetInstance();
		// 実体の削除
		static void DeleteInstance();
		// 初期化処理
		void Initialize();
		// 描画
		void Render(DrawData& _data);
		// 描画前後処理
		void Begin();
		void End();

		// テクスチャ読み込み
		bool LoadTexture(DrawData& _data, wchar_t* _fileName);
		bool LoadTexture(DxTexture& _texture, wchar_t* _fileName);
	private:
		// コンストラクタ
		DrawManager() {}
		// コピーコンストラクタ
		DrawManager& operator=(DrawManager _val) {}
	private:
		// 自身のポインタ
		static DrawManager* m_instance;
		// スプライトバッチ
		std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	};
}