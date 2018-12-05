#pragma once
#include "../Common/DrawData.h"

class Animation
{
public:
	// コンストラクタ
	Animation();
	Animation(int _row, int _column, int _size, RECT _rect, wchar_t *_fileName);
	// デストラクタ
	~Animation();

	// 更新
	void Update();
	// 描画
	void Render();
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
};
