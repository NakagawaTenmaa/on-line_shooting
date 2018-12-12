#include "DownloadScene.h"
#include "SceneManager.h"
#include "../NetWork/Http.h"
#include "LoginScene.h"
#include "../Utility/Fadein.h"
#include <direct.h>

using namespace Scene;

/// <summary>
/// コンストラクタ
/// </summary>
DownloadScene::DownloadScene()
{
	_mkdir("Resources");
	_mkdir("Resources/images");

	// 画像のダウンロードS
	NetWork::Http* http =  NetWork::Http::GetInstance();
	http->Initialize();

	http->PngLoad("/shooting/image/images/enemy.png", "images/enemy");
	http->PngLoad("/shooting/image/images/player.png", "images/player");
	http->PngLoad("/shooting/image/images/back.png", "images/back");
	http->PngLoad("/shooting/image/images/power_up.png", "images/power_up");
	http->PngLoad("/shooting/image/images/number.png", "images/number");
	http->PngLoad("/shooting/image/images/bullet.png", "images/bullet");
	http->PngLoad("/shooting/image/images/loginstr.png", "images/loginstr");
	http->PngLoad("/shooting/image/images/textbox.png", "images/textbox");
	http->PngLoad("/shooting/image/images/loginback.png", "images/loginback");
	http->PngLoad("/shooting/image/images/explosion.png", "images/explosion");
	http->PngLoad("/shooting/image/images/nouser.png", "images/nouser");
	http->PngLoad("/shooting/image/images/playback.png", "images/playback");
	http->PngLoad("/shooting/image/images/rankingstr.png", "images/rankingstr");
	http->PngLoad("/shooting/image/images/score.png", "images/score");
	http->PngLoad("/shooting/image/images/string.png", "images/string");
	http->PngLoad("/shooting/image/images/titleback.png", "images/titleback");
	
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
void DownloadScene::Update()
{
	// シーンの移行
	Scene::SceneManager::GetInstance()->ChangeScene(new LoginScene());
}

/// <summary>
/// 描画
/// </summary>
void DownloadScene::Render() 
{
	// フェード描画
	Fade::Render();
}
