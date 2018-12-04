#include "DrawData.h"

using namespace Draw;

/// /// <summary>
/// コンストラクタ
/// </summary>
DrawData::DrawData()
{
	m_texture = NULL;
	m_rot = 0.0f;
	m_scale = DirectX::SimpleMath::Vector2(1.0f, 1.0f);
	m_color = DirectX::Colors::White;
	m_pos = DirectX::SimpleMath::Vector2(0, 0);
	m_origin = DirectX::SimpleMath::Vector2(0, 0);
	m_rect = { 0,0,0,0 };
}

/// <summary>
/// デストラクタ
/// </summary>
DrawData::~DrawData()
{
	if (m_texture == NULL)
	{
		return;
	}

	// フラグによる削除制限
	if (m_flag.Is(DrawManagerFlag::NOT_TEXTURE_DELETE))
	{
		return;
	}

	m_texture->Release();
}
