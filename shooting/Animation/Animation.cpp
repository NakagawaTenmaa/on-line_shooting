#include "Animation.h"
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
Animation::Animation(int _row, int _column, int _size, RECT _rect, wchar_t *_fileName,int _time)
{
	Draw::DrawManager::GetInstance()->LoadTexture(m_image, _fileName);
	m_row = _row;
	m_column = _column;
	m_size = _size;
	m_rect = _rect;
	m_time = _time;
	m_timeCount = 0;
	m_count = 0;
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
void Animation::Update()
{
	m_time += Timer();
	if (m_time > 10)
	{

		m_time = 0;
	}
}

/// <summary>
/// 描画
/// </summary>
void Animation::Render()
{
	Draw::DrawManager::GetInstance()->Render(m_image);
}

/// <summary>
/// 一秒計測
/// </summary>
/// <returns></returns>
int Animation::Timer()
{
	m_timeCount++;
	if(m_timeCount > 60){
		m_timeCount = 0;
		return 1;
	}
	return 0;
}
