#include "LoginScene.h"
#include "../Common/InputManager.h"
#include "../Common/DrawManager.h"
#include "../NetWork/Http.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "DownloadScene.h"
#include "../Common/InputManager.h"
#include "../Utility/Fadein.h"
#include "../NetWork/UserData.h"

#include <SimpleMath.h>
#include <stdio.h>
#include <codecvt> 
#include <cstdio>

using namespace Scene;

/// <summary>
/// コンストラクタ
/// </summary>
LoginScene::LoginScene()
{
	m_textBox = new TextBox();
	m_distination = ID;

	// 画像の読み込み
	Draw::DrawManager::GetInstance()->LoadTexture(m_back, L"Resources/loginback.png");
	m_back.SetRect(600, 800);

	// 画像の読み込み
	Draw::DrawManager::GetInstance()->LoadTexture(m_nouser, L"Resources/nouser.png");
	m_nouser.SetPos(DirectX::SimpleMath::Vector2(200, 300));
	m_nouser.SetRect(256, 256);

	m_fadeFlag = false;
}

/// <summary>
/// デストラクタ
/// </summary>
LoginScene::~LoginScene()
{
	delete m_textBox;
	m_textBox = nullptr;
}

/// <summary>
/// 更新
/// </summary>
/// <returns> 継続確認 </returns>
bool LoginScene::Update()
{
	if (m_distination == ID)
	{
		if (Input::InputManager::GetInstance()->GetKeyTracker().pressed.Enter)
		{
			m_distination = PASSWORD;
		}
		Input::StreamManager::GetInstance()->IdUpdate();
	}
	else if (m_distination == PASSWORD)
	{
		Input::StreamManager::GetInstance()->PassUpdate();
		if (Input::InputManager::GetInstance()->GetKeyTracker().pressed.Enter)
		{
			// ログイン処理
			try
			{
				NetWork::Http::GetInstance()->Initialize();
				if (NetWork::Http::GetInstance()->Login(Input::StreamManager::GetInstance()->GetPass(), Input::StreamManager::GetInstance()->GetId()) != "")
				{
					// ログイン成功だとタイトルへ移動
					UserData::m_name = Input::StreamManager::GetInstance()->GetId();
					m_fadeFlag = true;
				}
				else
				{
					m_distination = END;
				}
			}
			catch (const std::exception&)
			{
				// 通信失敗
			}
		}
	}
	else if (m_distination == END) 
	{
		if (Input::InputManager::GetInstance()->GetKeyTracker().pressed.Enter)
		{
			m_distination = ID;
		}
	}

	if (m_fadeFlag)
	{
		 Fade::FadeIn();
		float a = Fade::GetA();
		if (a >= 1.0f)
		{
			SceneManager::GetInstance()->AddScene(new DownloadScene());
			return false;
		}
	}
	return true;
}

/// <summary>
/// 描画
/// </summary>
void LoginScene::Render()
{
	// 背景
	Draw::DrawManager::GetInstance()->Render(m_back);

	// 入力文字
	m_textBox->Render(DirectX::SimpleMath::Vector2(100,580));
	Fade::Render();

	// 確認が取れない場合のエラー画像
	if (m_distination == END) 
	{
		Draw::DrawManager::GetInstance()->Render(m_nouser);
	}
}