#pragma once
#include "../Common/DrawManager.h"
#include <vector>

/// <summary>
/// スコアの管理クラス
/// </summary>
class Score
{
public:
	// デストラクタ
	~Score();
	// 実体化
	static Score* GetInstance();
	// 削除
	static void DeleteInstance();
	
	// 点数の追加
	void AddScore(int _score);
	// 点数の取得
	int GetScore();
	// 点数のリセット
	void ReScore();

	// ハイスコアの更新
	void SeveHighScore();
	// ハイスコアのセット
	void SetHighScore(int _score);
	// ハイスコアの取得
	int GetHighScore();
	// 描画
	void Render(DirectX::SimpleMath::Vector2 _pos, bool _flag = true);
	// 数字の描画用
	void Render(DirectX::SimpleMath::Vector2 _pos, int _num);

	// ランキングの更新
	void UpDataRanking(std::vector<int> _score);
	// ランキングの描画
	void RankingRender(int _size);
private:
	// コンストラクタ
	Score();
	// コピーコンストラクタ
	Score& operator= (Score _val) {}
private:
	// 自身のポインタ
	static Score *m_instance;
	// スコア
	int m_score;
	DirectX::SimpleMath::Vector2 m_size;
	Draw::DrawData m_image;
	DirectX::SimpleMath::Vector2 m_position;
	int m_highScore;

	// 表示桁数
	static const int NUMBER_DIGITS;

	// ランキング用スコア
	std::vector<int> m_ranking;
};

