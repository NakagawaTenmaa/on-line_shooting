#include <CommonStates.h>
#include "../DeviceResources.h"
#include "DrawManager.h"

using namespace Draw;

// 静的変数の初期化
DrawManager* DrawManager::m_instance = nullptr;

/// <summary>
/// 実体化
/// </summary>
/// <returns>自身のポインタ</returns>
DrawManager* DrawManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new DrawManager();
	}
	return m_instance;
}

/// <summary>
/// 実体の削除
/// </summary>
void DrawManager::DeleteInstance()
{
	if (m_instance != nullptr)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="devise">デバイス</param>
void DrawManager::Initialize()
{
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(DX::DeviceResources::GetInstance()->GetD3DDeviceContext1());
}

/// <summary>
/// 描画
/// </summary>
/// <param name="_data">描画データ構造体</param>
void DrawManager::Render(DrawData& _data)
{	
	m_spriteBatch->Draw(
		(*_data.GetTexture()),
		_data.GetPos(),
		_data.GetRectPtn(),
		_data.GetColor(),
		_data.GetRot(),
		_data.GetOrigin(),
		_data.GetScale()
	);
}

/// <summary>
/// 描画前後処理
/// </summary>
void DrawManager::Begin()
{
	m_spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, DX::DeviceResources::GetInstance()->GetCommonStates()->NonPremultiplied());
}
void DrawManager::End()
{
	m_spriteBatch->End();
}

/// <summary>
/// テクスチャ読み込み
/// </summary>
/// <param name="pData">描画データ構造体</param>
/// <param name="fileName">ファイル名</param>
/// <returns>成功かどうか</returns>
bool DrawManager::LoadTexture(DrawData& _data, wchar_t* _fileName)
{
	// デバイスが無いので失敗
	//if (m_device == NULL)
	if (DX::DeviceResources::GetInstance()->GetD3DDevice1() == NULL)
	{
		return false;
	}

	DX::ThrowIfFailed
	(
		DirectX::CreateWICTextureFromFile
		(
			DX::DeviceResources::GetInstance()->GetD3DDevice1(),
			_fileName,
			nullptr,
			_data.GetTexture()
		)
	);
	return true;
}

bool DrawManager::LoadTexture(DxTexture& _texture, wchar_t* _fileName)
{
	// デバイスが無いので失敗
	if (DX::DeviceResources::GetInstance()->GetD3DDevice1() == NULL)
	{
		return false;
	}


	DX::ThrowIfFailed
	(
		DirectX::CreateWICTextureFromFile
		(
			DX::DeviceResources::GetInstance()->GetD3DDevice1(),
			_fileName,
			nullptr,
			&_texture
		)
	);

	return true;
}