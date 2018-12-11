#pragma once

#include "SceneBase.h"
#include "../Common/DrawData.h"
#include <vector>

namespace Scene
{
	class TitleScene : public SceneBase
	{
	public:
		// コンストラクタ
		TitleScene();
		// デストラクタ
		~TitleScene();

		// 描画
		void Update() override;
		// 更新
		void Render() override;

		void Timer();
	private:
		// ハイスコア画像
		Draw::DrawData m_highScore;

		// スタートボタン画像
		Draw::DrawData m_button;

		// 背景
		Draw::DrawData m_back;

		// ranking画像
		Draw::DrawData m_ranking;

		// トップ3
		std::vector<int> m_topScore;
		// 名前
		std::vector <std::string> m_name;

		// 点滅時間
		int m_time;
		bool m_flag;

		// フェード
		bool m_fadeFlag;

		// カーソル
		Draw::DrawData m_cursor;
		// メニュー
		Draw::DrawData m_menu;
	};
};