#include "EndScene.h"

// コンストラクタ
EndScene::EndScene()
{

}

// 初期化
void EndScene::Initialize()
{

}

// 更新
SceneType EndScene::Update(float delta_time)
{
	InputManager& input = InputManager::GetInstance();

	if (input.GetButtonState(XINPUT_BUTTON_A) == eInputState::Pressed)
	{
		return SceneType::title;
	}
	// 親クラスの更新
	return __super::Update(delta_time);
}

// 描画
void EndScene::Draw() const
{
	DrawString(1280 / 2, 720 / 2, "EndScene", GetColor(255, 255, 255));
}

// 終了
void EndScene::Finalize()
{
}

// 現在のシーンタイプ取得
const SceneType EndScene::GetNowSceneType() const
{
	return SceneType::end;
}
