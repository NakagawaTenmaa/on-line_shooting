#pragma once

#include <list>


#include "WICTextureLoader.h"
#include "SimpleMath.h"
#include "SpriteBatch.h"
#include "DrawData.h"

namespace Draw
{
	typedef ID3D11ShaderResourceView* DxTexture;

	/// <summary>
	/// �`��}�l�[�W���[
	/// </summary>
	class DrawManager
	{
	public:
		// �f�X�g���N�^
		~DrawManager() {}
	
		// ���̉�
		static DrawManager* GetInstance();
		// ���̂̍폜
		static void DeleteInstance();
		// ����������
		void Initialize();
		// �`��
		void Render(DrawData& _data);
		// �`��O�㏈��
		void Begin();
		void End();

		// �e�N�X�`���ǂݍ���
		bool LoadTexture(DrawData& _data, wchar_t* _fileName);
		bool LoadTexture(DxTexture& _texture, wchar_t* _fileName);
	private:
		// �R���X�g���N�^
		DrawManager() {}
		// �R�s�[�R���X�g���N�^
		DrawManager& operator=(DrawManager _val) {}
	private:
		// ���g�̃|�C���^
		static DrawManager* m_instance;
		// �X�v���C�g�o�b�`
		std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	};
}