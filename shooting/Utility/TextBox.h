#pragma once
#include "../Common/DrawData.h"

class TextBox
{
public:
	// コンストラクタ
	TextBox();
	// デストラクタ
	~TextBox();
	
	// 更新
	void Update();
	// 描画
	void Render(DirectX::SimpleMath::Vector2 _pos);
private:
	// 外画像
	Draw::DrawData m_back;
	// テキスト
	Draw::DrawData m_text;
};

