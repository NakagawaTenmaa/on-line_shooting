#include "InputManager.h"

using namespace Input;

// 静的変数の初期化
InputManager* InputManager::m_instance = nullptr;

/// <summary>
/// コンストラクタ
/// </summary>
InputManager::InputManager()
{
	m_mouse = std::make_unique<DirectX::Mouse>();
	m_keyboard = std::make_unique<DirectX::Keyboard>();


}

/// <summary>
/// 実体化
/// </summary>
/// <returns>自身のポインタ</returns>
InputManager * InputManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new InputManager();
	}
	return m_instance;
}

/// <summary>
/// 実体の削除
/// </summary>
void Input::InputManager::DeleteInstance()
{
	if (m_instance != nullptr)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

/// <summary>
/// マウスの入力状態の取得
/// </summary>
/// <returns>入力状態</returns>
DirectX::Mouse::State InputManager::GetMouseState()
{
	return m_mouse->GetState();
}

/// <summary>
/// Trackerの取得
/// </summary>
/// <returns>Tracker</returns>
DirectX::Mouse::ButtonStateTracker InputManager::GetTracker()
{
	return m_tracker;
}


/// <summary>
/// 何かのキーが押されたら返す
/// </summary>
/// <returns>なんのキーが押されたのか</returns>
DirectX::Keyboard::Keys Input::InputManager::AllGet()
{
	if (GetKeyTracker().pressed.A)       return DirectX::Keyboard::Keys::A;
	else if (GetKeyTracker().pressed.B)  return DirectX::Keyboard::Keys::B;
	else if (GetKeyTracker().pressed.C)  return DirectX::Keyboard::Keys::C;
	else if (GetKeyTracker().pressed.D)  return DirectX::Keyboard::Keys::D;
	else if (GetKeyTracker().pressed.E)  return DirectX::Keyboard::Keys::E;
	else if (GetKeyTracker().pressed.F)  return DirectX::Keyboard::Keys::F;
	else if (GetKeyTracker().pressed.G)  return DirectX::Keyboard::Keys::G;
	else if (GetKeyTracker().pressed.H)  return DirectX::Keyboard::Keys::H;
	else if (GetKeyTracker().pressed.I)  return DirectX::Keyboard::Keys::I;
	else if (GetKeyTracker().pressed.J)  return DirectX::Keyboard::Keys::J;
	else if (GetKeyTracker().pressed.K)  return DirectX::Keyboard::Keys::K;
	else if (GetKeyTracker().pressed.L)  return DirectX::Keyboard::Keys::L;
	else if (GetKeyTracker().pressed.M)  return DirectX::Keyboard::Keys::M;
	else if (GetKeyTracker().pressed.N)  return DirectX::Keyboard::Keys::N;
	else if (GetKeyTracker().pressed.O)  return DirectX::Keyboard::Keys::O;
	else if (GetKeyTracker().pressed.P)  return DirectX::Keyboard::Keys::P;
	else if (GetKeyTracker().pressed.Q)  return DirectX::Keyboard::Keys::Q;
	else if (GetKeyTracker().pressed.R)  return DirectX::Keyboard::Keys::R;
	else if (GetKeyTracker().pressed.S)  return DirectX::Keyboard::Keys::S;
	else if (GetKeyTracker().pressed.T)  return DirectX::Keyboard::Keys::T;
	else if (GetKeyTracker().pressed.U)  return DirectX::Keyboard::Keys::U;
	else if (GetKeyTracker().pressed.V)  return DirectX::Keyboard::Keys::V;
	else if (GetKeyTracker().pressed.W)  return DirectX::Keyboard::Keys::W;
	else if (GetKeyTracker().pressed.X)  return DirectX::Keyboard::Keys::X;
	else if (GetKeyTracker().pressed.Y)  return DirectX::Keyboard::Keys::Y;
	else if (GetKeyTracker().pressed.Z)  return DirectX::Keyboard::Keys::Z;
	else if (GetKeyTracker().pressed.Back) return DirectX::Keyboard::Keys::Back;

	return DirectX::Keyboard::Keys();
}

/// <summary>
/// 何かのキーか押されたら何が押されたのか
/// </summary>
/// <returns>入力状態</returns>
DirectX::Keyboard::State InputManager::GetKeyState()
{
	return m_keyboard->GetState();
}

/// <summary>
/// キーボードトラッカーの取得
/// </summary>
/// <returns>キーボードトラッカーの状態</returns>
DirectX::Keyboard::KeyboardStateTracker InputManager::GetKeyTracker()
{
	return m_keyTracker;
}

/// <summary>
/// 更新処理
/// </summary>
void InputManager::Update()
{
	DirectX::Mouse::State state = GetMouseState();
	DirectX::Keyboard::State key = GetKeyState();

	m_keyTracker.Update(key);
	m_tracker.Update(state);
}