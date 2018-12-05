#include "Score.h"
#include "../NetWork/Http.h"
#include "../Common/DrawManager.h"
#include "../Common/StreamManager.h"

using namespace DirectX::SimpleMath;

Score *Score::m_instance = nullptr;
const int Score::NUMBER_DIGITS = 4;

/// <summary>
/// コンストラクタ
/// </summary>
Score::Score()
{
	m_score = 0;	

	// 画像の読み込み
	m_size = Vector2(32, 32);
	Draw::DrawManager::GetInstance()->LoadTexture(m_image, L"Resources/number.png");
	m_image.SetOrigin(0, 0);
}

/// <summary>
/// デストラクタ
/// </summary>
Score::~Score(){}

/// <summary>
/// 実体化
/// </summary>
/// <returns></returns>
Score * Score::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new Score();
	}
	return m_instance;
}

/// <summary>
/// 削除
/// </summary>
void Score::DeleteInstance()
{
	if (m_instance != nullptr)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

/// <summary>
/// 点数の追加
/// </summary>
/// <param name="_score"></param>
void Score::AddScore(int _score)
{
	m_score += _score;
}

/// <summary>
/// 点数の取得
/// </summary>
/// <returns></returns>
int Score::GetScore()
{
	return m_score;
}

/// <summary>
/// 点数のリセット
/// </summary>
void Score::ReScore()
{
	m_score = 0;
}


/// <summary>
/// ハイスコアの更新
/// </summary>
/// <param name="_score"></param>
void Score::SeveHighScore()
{
	NetWork::Http::GetInstance()->Initialize();
	std::map<std::string, std::string> data;
	char str[256];

	sprintf_s(str,"%d", GetScore());
	data["high"] = str;
	data["name"] = Input::StreamManager::GetInstance()->GetId();
	NetWork::Http::GetInstance()->SendData(data,"/php/shooting/HishScore/SetHighScore.php");
}

/// <summary>
/// ハイスコアのセット
/// </summary>
/// <param name="_scoer"></param>
void Score::SetHighScore(int _score)
{
	m_highScore = _score;
}

/// <summary>
/// ハイスコアの取得
/// </summary>
/// <returns></returns>
int Score::GetHighScore()
{
	return m_highScore;
}


/// <summary>
/// 描画
/// </summary>
/// <param name="_pos">位置</param>
/// <param name="_flag">true=スコア false=ハイスコア</param>
void Score::Render(DirectX::SimpleMath::Vector2 _pos, bool _flag)
{
	int num[NUMBER_DIGITS];
	int score = (_flag) ? m_score : m_highScore;
	num[0] = score % 10000 / 1000;
	num[1] = score % 1000 / 100;
	num[2] = score % 100 / 10;
	num[3] = score % 10 / 1;

	int w = 4;
	for (int i = 0; i < NUMBER_DIGITS; i++)
	{
		m_image.SetPos(DirectX::SimpleMath::Vector2(_pos.x + i * (m_size.x - 10), _pos.y));
		LONG tmp = (LONG)m_size.x * (LONG)num[i];
		LONG x = tmp % (w * (LONG)m_size.x);
		LONG y = (tmp / (w * (LONG)m_size.x)) * (LONG)m_size.y;
		LONG u = x + (LONG)m_size.x;
		LONG v = y + (LONG)m_size.y;
		m_image.SetRect(x, y, u, v);
		Draw::DrawManager::GetInstance()->Render(m_image);
	}
}

/// <summary>
/// 数字の描画用
/// </summary>
/// <param name="_pos"></param>
/// <param name="_num"></param>
void Score::Render(DirectX::SimpleMath::Vector2 _pos, int _num)
{
	int num[NUMBER_DIGITS];
	int score = _num;
	num[0] = score % 10000 / 1000;
	num[1] = score % 1000 / 100;
	num[2] = score % 100 / 10;
	num[3] = score % 10 / 1;

	int w = 4;
	for (int i = 0; i < NUMBER_DIGITS; i++)
	{
		m_image.SetPos(DirectX::SimpleMath::Vector2(_pos.x + i * (m_size.x - 10), _pos.y));
		LONG tmp = (LONG)m_size.x * (LONG)num[i];
		LONG x = tmp % (w * (LONG)m_size.x);
		LONG y = (tmp / (w * (LONG)m_size.x)) * (LONG)m_size.y;
		LONG u = x + (LONG)m_size.x;
		LONG v = y + (LONG)m_size.y;
		m_image.SetRect(x, y, u, v);
		Draw::DrawManager::GetInstance()->Render(m_image);
	}
}

/// <summary>
/// ランキングの更新
/// </summary>
void Score::UpDataRanking(std::vector<int> _score)
{
	for (std::vector<int>::iterator it = _score.begin(); it != _score.end(); it++)
	{
		m_ranking.push_back(*it);
	}
}

/// <summary>
/// ランキングの描画
/// </summary>
void Score::RankingRender(int _size)
{
	for (int i = 0; i < _size; i++)
	{
		Render(DirectX::SimpleMath::Vector2(100.0f, 300.0f + (float)i * 50.0f), m_ranking[i]);
	}
}
