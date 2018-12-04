#pragma once

#include "../Common/DrawData.h"

static class Fade
{
public:
	// コンストラクタ
	Fade();
	// デストラクタ
	~Fade();

	// 初期化
	static void Initialize();
	// フェードイン開始
	static void FadeOn();
	// フェードイン終了
	static void FadeOff();

	// フェードイン
	static void FadeIn();
	// フェードアウト
	static void FadeOut();
	// 描画
	static void Render();

	// アルファ値の取得
	static float GetA() { return m_a; }
private:
	// アルファブレンド
	static float m_a;
	// 画像
	static Draw::DrawData m_image;
	// 状態
	static bool m_flag;
};

