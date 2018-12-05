#pragma once
#include "../Common/DrawData.h"

class Animation
{
public:
	// コンストラクタ
	Animation();
	Animation(int _row, int _column, int _size, RECT _rect, wchar_t *_fileName, int _time = 1);
	// デストラクタ
	~Animation();

	// 更新
	void Update();
	// 描画
	void Render();

private:
	// 時間計測
	int Timer();

private:
	// 画像
	Draw::DrawData m_image;
	// 行
	int m_row;
	// 列
	int m_column;
	// 画像
	int m_size;
	// 画像サイズ
	RECT m_rect;
	// 時間
	int m_time;
	// 何枚目
	int m_count;
	// 時間計測用
	int m_timeCount;
};
