//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include "Scene\SceneManager.h"
#include "NetWork\Http.h"
#include "Scene\PlayScene.h"
#include "Common\InputManager.h"
#include "Common\DrawManager.h"
#include "Scene\DownloadScene.h"
#include "Utility\Score.h"
#include "Scene\LoginScene.h"
#include "Common\InputManager.h"
#include "Scene\TitleScene.h"
#include "Utility\Fadein.h"
extern void ExitGame();

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game()
{
	DX::DeviceResources::GetInstance()->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
	DX::DeviceResources::GetInstance()->SetWindow(window, width, height);

	DX::DeviceResources::GetInstance()->CreateDeviceResources();
    CreateDeviceDependentResources();

	DX::DeviceResources::GetInstance()->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

	// DrawManager初期化
	Draw::DrawManager::GetInstance()->Initialize();

	// フェード初期化
	Fade::Initialize();
	// 初期シーンの登録

	//Scene::SceneManager::GetInstance()->ChangeScene(new Scene::PlayScene());
	Scene::SceneManager::GetInstance()->ChangeScene(new Scene::LoginScene());
	//Scene::SceneManager::GetInstance()->ChangeScene(new Scene::TitleScene());
	//Scene:S:SceneManager::GetInstance()->ChangeScene(new Scene::DownloadScene());
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());
	elapsedTime;
	// 入力更新
	Input::InputManager::GetInstance()->Update();
	// シーンの更新
	Scene::SceneManager::GetInstance()->Update();
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

	DX::DeviceResources::GetInstance()->PIXBeginEvent(L"Render");
    auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
    // TODO: Add your rendering code here.
    context;

	// シーンの描画
	Scene::SceneManager::GetInstance()->Renrer();

	DX::DeviceResources::GetInstance()->PIXEndEvent();

    // Show the new frame.
	DX::DeviceResources::GetInstance()->Present();
}

// Helper method to clear the back buffers.S
void Game::Clear()
{
	DX::DeviceResources::GetInstance()->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
    auto renderTarget = DX::DeviceResources::GetInstance()->GetRenderTargetView();
    auto depthStencil = DX::DeviceResources::GetInstance()->GetDepthStencilView();

	context->ClearRenderTargetView(renderTarget, Colors::White);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto viewport = DX::DeviceResources::GetInstance()->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

	DX::DeviceResources::GetInstance()->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
    auto r = DX::DeviceResources::GetInstance()->GetOutputSize();
	DX::DeviceResources::GetInstance()->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!DX::DeviceResources::GetInstance()->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 600;
    height = 800;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = DX::DeviceResources::GetInstance()->GetD3DDevice();

    // TODO: Initialize device dependent objects here (independent of window size).
    device;
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
	
	// シングルトン削除
	// シーン
	Scene::SceneManager::DeleteInstance();
	// Http
	NetWork::Http::DeleteInstance();
	// 描画
	Draw::DrawManager::DeleteInstance();
	// 入力
	Input::InputManager::DeleteInstance();
	// スコア
	Score::DeleteInstance();
	// 文字の入力
	Input::StreamManager::DeleteInstance();
	// デバイスの削除
	DX::DeviceResources::LostInstance();
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
