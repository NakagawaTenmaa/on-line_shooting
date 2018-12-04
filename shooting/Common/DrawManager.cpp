#include <CommonStates.h>
#include "../DeviceResources.h"
#include "DrawManager.h"

using namespace Draw;

// �ÓI�ϐ��̏�����
DrawManager* DrawManager::m_instance = nullptr;

/// <summary>
/// ���̉�
/// </summary>
/// <returns>���g�̃|�C���^</returns>
DrawManager* DrawManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new DrawManager();
	}
	return m_instance;
}

/// <summary>
/// ���̂̍폜
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
/// ����������
/// </summary>
/// <param name="devise">�f�o�C�X</param>
void DrawManager::Initialize()
{
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(DX::DeviceResources::GetInstance()->GetD3DDeviceContext1());
}

/// <summary>
/// �`��
/// </summary>
/// <param name="_data">�`��f�[�^�\����</param>
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
/// �`��O�㏈��
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
/// �e�N�X�`���ǂݍ���
/// </summary>
/// <param name="pData">�`��f�[�^�\����</param>
/// <param name="fileName">�t�@�C����</param>
/// <returns>�������ǂ���</returns>
bool DrawManager::LoadTexture(DrawData& _data, wchar_t* _fileName)
{
	// �f�o�C�X�������̂Ŏ��s
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
	// �f�o�C�X�������̂Ŏ��s
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