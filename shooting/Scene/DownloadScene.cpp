#include "DownloadScene.h"
#include "SceneManager.h"
#include "../NetWork/Http.h"
#include "TitleScene.h"
#include "../Utility/Fadein.h"

using namespace Scene;

/// <summary>
/// コンストラクタ
/// </summary>
DownloadScene::DownloadScene()
{
	// 画像のダウンロードS
	NetWork::Http* http =  NetWork::Http::GetInstance();
	http->Initialize();

	http->PngLoad("/shooting/image/enemy.png", "enemy");
	http->PngLoad("/shooting/image/Myplayer.png", "Myplayer");
	http->PngLoad("/shooting/image/a.png", "a");
	http->PngLoad("/shooting/image/back.png", "back");
	http->PngLoad("/shooting/image/power_up.png", "power_up");
	http->PngLoad("/shooting/image/number.png", "number");
	http->PngLoad("/shooting/image/bullet.png", "bullet");
	http->PngLoad("/shooting/image/met.png", "met");
	http->PngLoad("/shooting/image/loginstr.png", "loginstr");
	http->PngLoad("/shooting/image/textbox.png", "textbox");
	http->PngLoad("/shooting/image/loginback.png", "loginback");

	// 音のダウンロード

}

/// <summary>
/// デストラクタ
/// </summary>
DownloadScene::~DownloadScene(){}

/// <summary>
/// 更新
/// </summary>
/// <returns>継続確認</returns>
bool DownloadScene::Update()
{
	// シーンの移行
	Scene::SceneManager::GetInstance()->AddScene(new TitleScene());
	return false;
}

/// <summary>
/// 描画
/// </summary>
void DownloadScene::Render() 
{
	// フェード描画
	Fade::Render();
}
