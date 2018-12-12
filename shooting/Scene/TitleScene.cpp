#include "TitleScene.h"
#include "../Common/InputManager.h"
#include "PlayScene.h"
#include "SceneManager.h"
#include "../Utility/Score.h"
#include "../NetWork/Http.h"
#include "../NetWork/Json.h"
#include "../Utility/Score.h"
#include "../Common/DrawManager.h"
#include "../Common/StreamManager.h"
#include "../Utility/Fadein.h"
#include "../NetWork/UserData.h"

using namespace std;
using namespace Scene;

/// <summary>
/// コンストラクタ
/// </summary>
TitleScene::TitleScene()
{
	m_time = 0;
	m_flag = true;
	m_fadeFlag = true;

	NetWork::Http::GetInstance()->Initialize();
	picojson::array data = Json::StrToVal(Json::JsonToData(Json::JsonToData(NetWork::Http::GetInstance()->GetData("/php/shooting/HishScore/GetHighScore.php"))));
	for (int i = 0; i < 3; i++)
	{
		picojson::object &object = data[i].get<picojson::object>();
		m_topScore.push_back(atoi(object["score"].get<std::string>().c_str()));
		m_name.push_back(object["name"].get<std::string>());
		

	}

	for (int i = 0; i < (int)data.size(); i++)
	{
		// 自分のハイスコアを取得
		picojson::object &object = data[i].get<picojson::object>();
		if (object["name"].get<std::string>() == UserData::m_name)
		{
			Score::GetInstance()->SetHighScore(atoi(object["score"].get<std::string>().c_str()));
			break;
		}
	}

	Score::GetInstance()->UpDataRanking(m_topScore);

	Draw::DrawManager::GetInstance()->LoadTexture(m_ranking, L"Resources/images/rankingstr.png");
	m_ranking.SetOrigin(0, 0);
	m_ranking.SetRect(128, 32);
	m_ranking.SetPos(10, 250);

	// ハイスコア
	Draw::DrawManager::GetInstance()->LoadTexture(m_highScore, L"Resources/images/score.png");
	m_highScore.SetOrigin(0, 0);
	m_highScore.SetPos(10, 50);
	m_highScore.SetRect(0, 0, 128, 64);

	// スタートボタン
	Draw::DrawManager::GetInstance()->LoadTexture(m_button, L"Resources/images/space.png");
	m_button.SetPos(300 - 128, 650);
	m_button.SetRect(256, 64);

	// 背景
	Draw::DrawManager::GetInstance()->LoadTexture(m_back, L"Resources/images/titleback.png");
	m_back.SetPos(0, 0);
	m_back.SetRect(600, 800);
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene(){}

/// <summary>
/// 更新
/// </summary>
/// <returns>継続確認</returns>
void TitleScene::Update()
{
	Timer();
	if (m_fadeFlag)
	{
		// フェードアウト
		Fade::FadeOut();
		if (Fade::GetA() < 0) m_fadeFlag = false;
	}
	// キーが押されたらプレイ画面に移行
	if (Input::InputManager::GetInstance()->GetKeyState().Space && Fade::GetA() < 0.1f)
	{
		Scene::SceneManager::GetInstance()->ChangeScene(new PlayScene());
	}
}

/// <summary>
/// 描画
/// </summary>
void TitleScene::Render()
{
	// 背景
	Draw::DrawManager::GetInstance()->Render(m_back);

	// ハイスコアの描画
	Score::GetInstance()->Render(DirectX::SimpleMath::Vector2(150, 60), false);
	Draw::DrawManager::GetInstance()->Render(m_highScore);

	Draw::DrawManager::GetInstance()->Render(m_ranking);

	// スタートボタン
	if (m_flag) Draw::DrawManager::GetInstance()->Render(m_button);

	Score::GetInstance()->RankingRender(3);


	for (int i = 0; i < 3; i++)
	{
		Input::StreamManager::GetInstance()->Render(DirectX::SimpleMath::Vector2(250.0f, 300.0f + (float)i * 50.0f),m_name[i]);
	}
	Fade::Render();
}


void TitleScene::Timer()
{
	m_time++;
	if (m_time > 60)
	{
		m_time = 0;
		m_flag = m_flag ? false : true;
	}
	
}