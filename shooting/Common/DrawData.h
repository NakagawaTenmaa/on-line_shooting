#pragma once

#include "WICTextureLoader.h"
#include "SimpleMath.h"
#include "SpriteBatch.h"
#include "../Utility/Flag.h"

namespace Draw
{
	typedef ID3D11ShaderResourceView* DxTexture;

	/// <summary>
	/// 描画データ
	/// </summary>
	struct DrawData
	{
	private:
		enum DrawManagerFlag
		{
			NOT_TEXTURE_DELETE = (1 << 0)
		};

		// フラグ
		Utility::Flag m_flag;
		// テクスチャ
		DxTexture m_texture;
		// 座標
		DirectX::SimpleMath::Vector2 m_pos;
		// 角度
		float m_rot;
		// 切り取り情報
		RECT m_rect;
		// 中心点
		DirectX::XMFLOAT2 m_origin;
		// スケール
		DirectX::XMFLOAT2 m_scale;
		// 色
		DirectX::SimpleMath::Color m_color;
	public:
		// コンストラクタ
		DrawData();
		// デストラクタ
		~DrawData();
	public: // getter
		// Texture
		DxTexture* GetTexture() { return &m_texture; }
		// 位置
		DirectX::SimpleMath::Vector2 GetPos() { return m_pos; }
		// 回転
		float GetRot() { return m_rot; }
		// 切り取り
		RECT GetRect() { return m_rect; }
		const RECT* GetRectPtn() { return &m_rect; }
		// アンカーポイント
		DirectX::XMFLOAT2 GetOrigin() { return m_origin; }
		// スケール
		DirectX::XMFLOAT2 GetScale() { return  m_scale; }
		// 色
		DirectX::SimpleMath::Color GetColor() { return m_color; }
	public: // setter
		// Texture
		void SetTexture(DxTexture _texture) 
		{
			m_texture = _texture;
			m_flag.On(DrawManagerFlag::NOT_TEXTURE_DELETE);
		}
		// 位置
		void SetPos(float _x, float _y) { m_pos.x = _x; m_pos.y = _y; }
		void SetPos(DirectX::SimpleMath::Vector2 _pos) { m_pos = _pos; }
		// 回転
		void SetRot(float _r) { m_rot = _r; }
		// 切り取り
		void SetRect(LONG _left, LONG _top, LONG _right, LONG _bottom) {
			m_rect.left = _left;
			m_rect.top = _top;
			m_rect.right = _right;
			m_rect.bottom = _bottom;
		}
		void SetRect(LONG _right, LONG _bottom) { SetRect(0, 0, _right, _bottom); }
		void SetRect(RECT _rect) { SetRect(_rect.left, _rect.top, _rect.right, _rect.bottom); }
		// アンカーポイント
		void SetOrigin(float _x, float _y) { m_origin.x = _x; m_origin.y = _y; }
		void SetOrigin(DirectX::SimpleMath::Vector2 _origin) { m_origin = _origin; }
		// サイズ
		void SetScale(float _x, float _y) { m_scale.x = _x; m_scale.y = _y; }
		void SetScale(DirectX::SimpleMath::Vector2 _scale) { m_scale = _scale; }
		// 色
		void SetColor(float _a) { m_color = DirectX::SimpleMath::Color(1, 1, 1, _a); }
		void SetColor(DirectX::SimpleMath::Color _color) { m_color = _color; }
	};

}