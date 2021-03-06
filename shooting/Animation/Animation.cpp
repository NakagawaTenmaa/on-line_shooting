﻿#include "Animation.h"
#include "../Common/DrawManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
Animation::Animation(){}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_row">     行</param>
/// <param name="_column">  列</param>
/// <param name="_fileName">ファイル名</param>
Animation::Animation(int _size, RECT _rect, wchar_t *_fileName,float _time)
{
	Draw::DrawManager::GetInstance()->LoadTexture(m_image, _fileName);
	m_size = _size;
	m_rect = _rect;
	m_time = _time;
	m_timeCount = 0;
	m_count = 0;
	m_timer = 0;
}

Animation::Animation(int _size, RECT _rect, wchar_t * _fileName, DirectX::SimpleMath::Vector2 _pos, float _time)
{
	Draw::DrawManager::GetInstance()->LoadTexture(m_image, _fileName);
	m_image.SetPos(_pos);
	m_image.SetOrigin((float)_rect.right / 2.0f, (float)_rect.top / 2.0f);
	m_size = _size;
	m_rect = _rect;
	m_time = _time;
	m_timeCount = 0;
	m_count = 0;
	m_timer = 0;
}

/// <summary>
/// デストラクタ
/// </summary>
Animation::~Animation()
{
}

/// <summary>
/// 更新
/// </summary>
bool Animation::Update()
{
	m_timer++;
	if (m_time < m_timer)
	{
		// 描画画像の変更
		m_count++;
		if (m_count  >= m_size )
		{
			m_count = 0;
			return true;
		}
		m_timer = 0;
	}
	return false;
}

/// <summary>
/// 描画
/// </summary>
void Animation::Render(DirectX::SimpleMath::Vector2 _pos)
{	
	// 画像の切り取りサイズ
	LONG    left = (m_rect.left + m_rect.right) * m_count;
	LONG    top  = m_rect.top;
	LONG    right  = left + m_rect.right;
	LONG    bottom = top + m_rect.bottom;

	// 画像の描画位置
	RECT rect = {left,top,right,bottom };
	
	m_image.SetRect(rect);
	m_image.SetPos(_pos);
	Draw::DrawManager::GetInstance()->Render(m_image);
}


/// <summary>
/// 描画
/// </summary>
void Animation::Render()
{	
	// 画像の切り取りサイズ
	LONG    left = (m_rect.left + m_rect.right) * m_count;
	LONG    top  = m_rect.top;
	LONG    right  = left + m_rect.right;
	LONG    bottom = top + m_rect.bottom;

	// 画像の描画位置
	RECT rect = {left,top,right,bottom };
	
	m_image.SetRect(rect);
	Draw::DrawManager::GetInstance()->Render(m_image);
}
