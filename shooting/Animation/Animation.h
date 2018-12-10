#pragma once
#include "../Common/DrawData.h"

class Animation
{
public:
	// コンストラクタ
	Animation();
	Animation(int _size, RECT _rect, wchar_t *_fileName, int _time = 1);
	Animation(int _size, RECT _rect, wchar_t *_fileName, DirectX::SimpleMath::Vector2 _pos ,int _time = 1);
	// デストラクタ
	~Animation();

	// 更新
	bool Update();
	
	// 描画
	void Render(DirectX::SimpleMath::Vector2 _pos);	
	void Render();
private:
	// 画像
	Draw::DrawData m_image;

	// 画像
	int m_size;
	// 画像サイズ
	RECT m_rect;
	// 切り替え時間
	float m_time;
	// 経過時間
	float m_timer;
	// 何枚目
	int m_count;
	// 時間計測用
	float m_timeCount;
};
