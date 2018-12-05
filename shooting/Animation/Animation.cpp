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
Animation::Animation(int _row, int _column, int _size, RECT _rect, wchar_t *_fileName)
{
	Draw::DrawManager::GetInstance()->LoadTexture(m_image, _fileName);
	m_row = _row;
	m_column = _column;
	m_size = _size;
	m_rect = _rect;
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

}

/// <summary>
/// 描画
/// </summary>
void Animation::Render()
{
	Draw::DrawManager::GetInstance()->Render(m_image);
}
