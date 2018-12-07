#pragma once
#include "../Common/DrawData.h"

class Animation
{
public:
	// コンストラクタ
	Animation();
	Animation(int _size, RECT _rect, wchar_t *_fileName, int _time = 1);
	// デストラクタ
	~Animation();

	// 更新
	void Update();
	// 描画
	void Render(DirectX::SimpleMath::Vector2 _pos);

private:
	// 時間計測
	int Timer();

private:
	// 画像
	Draw::DrawData m_image;

	// 画像
	int m_size;
	// 画像サイズ
	RECT m_rect;
	// 切り替え時間
	int m_time;
	// 経過時間
	int m_timer;
	// 何枚目
	int m_count;
	// 時間計測用
	int m_timeCount;
};
