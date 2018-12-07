#pragma once

#include "Object.h"
#include "../Animation/Animation.h"

/// <summary>
/// �G�N���X
/// </summary>
class Enemy : public Object
{
public:
	// �R���X�g���N�^
	Enemy(DirectX::SimpleMath::Vector2 _pos, float _speed, int _hp, int _id, int _score);
	// �f�X�g���N�^
	~Enemy();

	// �X�V
	bool Update();
	// �`��
	void Render();
private:
	// Hp
	int m_hp;
	// �X�R�A
	int m_score;
};