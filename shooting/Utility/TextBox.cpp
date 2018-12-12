#include "TextBox.h"
#include "../Common/DrawManager.h"
#include "../Common/StreamManager.h"

/// <summary>
/// デストラクタ
/// </summary>
TextBox::TextBox()
{
	// 画像の読み込み
	Draw::DrawManager::GetInstance()->LoadTexture(m_text, L"Resources/images/textbox.png");
	m_text.SetRect(128, 64);
	m_text.SetPos(280, 390);
	m_text.SetScale(2.0f, 0.6f);
	Draw::DrawManager::GetInstance()->LoadTexture(m_back, L"Resources/images/loginstr.png");
}

/// <summary>
/// デストラクタ
/// </summary>
TextBox::~TextBox()
{
}

/// <summary>
/// 更新
/// </summary>
void TextBox::Update()
{
}

/// <summary>
/// 描画
/// </summary>
void TextBox::Render(DirectX::SimpleMath::Vector2 _pos)
{
	// テキスト名
	m_back.SetPos(_pos);
	m_back.SetRect(0, 64, 128, 128);
	Draw::DrawManager::GetInstance()->Render(m_back);
	m_back.SetPos(DirectX::SimpleMath::Vector2(_pos.x, _pos.y + 60));
	m_back.SetRect(0, 0, 128, 64);
	Draw::DrawManager::GetInstance()->Render(m_back);

	// テキストボックス
	m_text.SetPos(DirectX::SimpleMath::Vector2(_pos.x + 180, _pos.y + 10));
	Draw::DrawManager::GetInstance()->Render(m_text);
	m_text.SetPos(DirectX::SimpleMath::Vector2(_pos.x + 180, _pos.y + 70));
	Draw::DrawManager::GetInstance()->Render(m_text);

	// 文字の入力
	Input::StreamManager::GetInstance()->IdRender(DirectX::SimpleMath::Vector2(_pos.x + 200, _pos.y + 20));
	Input::StreamManager::GetInstance()->PassRender(DirectX::SimpleMath::Vector2(_pos.x + 200, _pos.y + 80));
}
