#include "Fadein.h"
#include "../Common/DrawManager.h"

float Fade::m_a = 0;
Draw::DrawData Fade::m_image = Draw::DrawData();
bool Fade::m_flag = false;

/// <summary>
/// コンストラクタ
/// </summary>
Fade::Fade(){}

/// <summary>
/// デストラクタ
/// </summary>
Fade::~Fade(){}

/// <summary>
/// 初期化
/// </summary>
void Fade::Initialize()
{
	Draw::DrawManager::GetInstance()->LoadTexture(m_image, L"Resources/back.png");
	m_image.SetOrigin(0, 0);
	m_image.SetPos(0, 0);
	m_image.SetRect(600, 800);
	m_a = 0;
	m_image.SetColor(m_a);
}

/// <summary>
/// フェードインの開始
/// </summary>
void Fade::FadeOn()
{
	m_flag = true;
}

/// <summary>
/// フェードインの終了
/// </summary>
void Fade::FadeOff()
{
	m_flag = false;
}

/// <summary>
/// フェードイン
/// </summary>
void Fade::FadeIn()
{
	// アルファ値の変更
	if (m_a < 1.0f)
	{
		m_a += 0.009f;
		m_image.SetColor(m_a);
	}
}

/// <summary>
/// フェードアウト
/// </summary>
void Fade::FadeOut()
{
	// アルファ値の変更
	if (m_a > 0.0f)
	{
		m_a -= 0.009f;
		m_image.SetColor(m_a);
	}
}

/// <summary>
/// 描画
/// </summary>
void Fade::Render()
{
	Draw::DrawManager::GetInstance()->Render(m_image);
}
