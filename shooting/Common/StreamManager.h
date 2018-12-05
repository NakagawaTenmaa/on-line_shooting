#pragma once

#include <map>
#include <vector>
#include <Keyboard.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include "DrawData.h"

namespace Input
{
	/// <summary>
	/// 文字の入力
	/// </summary>
	class StreamManager
	{
	public:
		// デストラクタ
		~StreamManager();
		// 実体化
		static StreamManager* GetInstance();
		// 実体の削除
		static void DeleteInstance();
		
		// 更新
		void IdUpdate();
		void PassUpdate();

		// 描画
		void IdRender(DirectX::SimpleMath::Vector2 _pos);
		void PassRender(DirectX::SimpleMath::Vector2 _pos);

		// 文字の指定描画
		void Render(DirectX::SimpleMath::Vector2 _pos, const std::string _str);

		// getter
		std::string GetPass();
		std::string GetId();
	private:
		// コンストラクタ
		StreamManager();
		// コピーコンストラクタ
		StreamManager& operator=(StreamManager _val) {}
	private:
		// 自身のポインタ
		static StreamManager* m_instance;

		// 文字画像
		Draw::DrawData m_strImage;
		// 一文字のサイズ
		static int IMAGE_SIZE;


		std::vector<int*> m_strId;
		std::vector<int*> m_strPass;
	};
};