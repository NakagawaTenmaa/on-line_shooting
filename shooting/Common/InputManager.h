#pragma once

#include <Mouse.h>
#include <Keyboard.h>
#include <SimpleMath.h>

namespace Input
{
	/// <summary>
	/// 入力
	/// </summary>
	class InputManager
	{
	public:
		// 実体化
		static InputManager* GetInstance();
		// 実体の削除
		static void DeleteInstance();
		// マウスの状態取得
		DirectX::Mouse::State GetMouseState();
		// キーボードの状態取得
		DirectX::Keyboard::State GetKeyState();
		// Trackerの取得
		DirectX::Keyboard::KeyboardStateTracker GetKeyTracker();
		DirectX::Mouse::ButtonStateTracker GetTracker();
		// 何かのキーが押されたら
		DirectX::Keyboard::Keys AllGet();
		DirectX::SimpleMath::Vector3 Mood();

		void CCC();

		// マウス座標の取得
		int GetMousePosX() { return GetMouseState().x; }
		int GetMousePosY() { return GetMouseState().y; }
		// 更新
		void Update();
	private:
		// 自身のポインタ
		static InputManager* m_instance;
		// マウス
		std::unique_ptr<DirectX::Mouse> m_mouse;
		// キーボード
		std::unique_ptr<DirectX::Keyboard> m_keyboard;
		// Tracker
		DirectX::Mouse::ButtonStateTracker m_tracker;
		DirectX::Keyboard::KeyboardStateTracker m_keyTracker;
	private:
		// コンストラクタ
		InputManager();
		// コピーコンストラクタ
		InputManager& operator=(InputManager _val) {}
	};
}