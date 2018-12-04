#pragma once

#include <Mouse.h>
#include <Keyboard.h>
#include <SimpleMath.h>

namespace Input
{
	/// <summary>
	/// ����
	/// </summary>
	class InputManager
	{
	public:
		// ���̉�
		static InputManager* GetInstance();
		// ���̂̍폜
		static void DeleteInstance();
		// �}�E�X�̏�Ԏ擾
		DirectX::Mouse::State GetMouseState();
		// �L�[�{�[�h�̏�Ԏ擾
		DirectX::Keyboard::State GetKeyState();
		// Tracker�̎擾
		DirectX::Keyboard::KeyboardStateTracker GetKeyTracker();
		DirectX::Mouse::ButtonStateTracker GetTracker();
		// �����̃L�[�������ꂽ��
		DirectX::Keyboard::Keys AllGet();
		DirectX::SimpleMath::Vector3 Mood();

		void CCC();

		// �}�E�X���W�̎擾
		int GetMousePosX() { return GetMouseState().x; }
		int GetMousePosY() { return GetMouseState().y; }
		// �X�V
		void Update();
	private:
		// ���g�̃|�C���^
		static InputManager* m_instance;
		// �}�E�X
		std::unique_ptr<DirectX::Mouse> m_mouse;
		// �L�[�{�[�h
		std::unique_ptr<DirectX::Keyboard> m_keyboard;
		// Tracker
		DirectX::Mouse::ButtonStateTracker m_tracker;
		DirectX::Keyboard::KeyboardStateTracker m_keyTracker;
	private:
		// �R���X�g���N�^
		InputManager();
		// �R�s�[�R���X�g���N�^
		InputManager& operator=(InputManager _val) {}
	};
}