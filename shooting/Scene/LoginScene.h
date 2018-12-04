#pragma once

#include "SceneBase.h"
#include "../Common/StreamManager.h"
#include "../Common/DrawData.h"
#include "../Utility/TextBox.h"

namespace Scene
{	
	// 状態
	enum DESTINATION
	{
		ID,
		PASSWORD,
		END,

		NUM,
	};

	/// <summary>
	/// ログインシーン
	/// </summary>
	class LoginScene : public SceneBase
	{
	public:
		// コンストラクタ
		LoginScene();
		// デストラクタ
		~LoginScene();

		// 描画
		bool Update();
		// 更新
		void Render();

	private:
		// 背景S
		Draw::DrawData m_back;

		DESTINATION m_distination;
		
		// テキストボックス
		TextBox *m_textBox;
		

		// フェード確認Flag
		bool m_fadeFlag;
	};
};
