#include "InputManager.h"
#include <cmath>
#include <algorithm>

bool InputManager::GetNowButton(const int num) const
{
	return now_button[num];
}

void InputManager::Update()
{
	//コントローラー入力値の更新
	XINPUT_STATE input = {};
	GetJoypadXInputState(DX_INPUT_PAD1, &input);
	for (int i = 0; i < D_BUTTON_MAX; i++)
	{
		old_button[i] = now_button[i];
		now_button[i] = static_cast<bool>(input.Buttons[i]);
	}
	/*trigger[0] = TriggerNormalize(input.LeftTrigger);
	trigger[1] = TriggerNormalize(input.RightTrigger);*/
	Left_stick = Left_StickNormalize(input.ThumbLX, input.ThumbLY);		// 左スティックの更新処理
	Right_stick = Right_StickNormalize(input.ThumbRX, input.ThumbRY);	// 右スティックの更新処理
}

// ボタンの現在状態取得
eInputState InputManager::GetButtonState(int button) const
{
	//ボタンが押されているか
	if (CheckButtonRange(button) && (now_button[button] && old_button[button]))
	{
		return eInputState::Held;
	}

	//ボタンが押された瞬間か
	if (CheckButtonRange(button) && (now_button[button] && !old_button[button]))
	{
		return eInputState::Pressed;
	}

	//ボタンが離された瞬間か
	if (CheckButtonRange(button) && (!now_button[button] && old_button[button]))
	{
		return eInputState::Release;
	}

	return eInputState::None;
}

// デッドゾーン処理
Vector2D InputManager::StickNormalize(float x, float y) const
{
	x /= 32767.0f;
	y /= 32767.0f;

	// 大きさの取得
	float length = sqrtf(x * x + y * y);

	// 取得した大きさがDEAD_ZONEより小さい場合、全て０にする
	if (length < DEAD_ZONE)
	{
		return Vector2D(0.0f, 0.0f);
	}

	// 現在スティックの数値計算
	float normalized = (length - DEAD_ZONE) / (1.0f - DEAD_ZONE);
	if (normalized > 1.0f) normalized = 1.0f;

	// スティックの数値を渡す
	return Vector2D((x / length) * normalized,
		(y / length) * normalized);
}
// 左トリガー取得
float InputManager::GetLeftTrigger() const
{
	return trigger[0];
}

// 右トリガー取得
float InputManager::GetRightTrigger() const
{
	return trigger[1];
}

// 左スティック情報の取得
const Vector2D& InputManager::GetLeftStick() const
{
	return Left_stick;
}

// 右スティック情報の取得
const Vector2D& InputManager::GetRightStick() const
{
	return Right_stick;
}

// ボタンの範囲走査
bool InputManager::CheckButtonRange(int button) const
{
	return (0 <= button && button < D_BUTTON_MAX);
}

// 左スティックの範囲をVector2Dに変換
Vector2D InputManager::Left_StickNormalize(float x, float y) const
{
	return StickNormalize(x, y);
}

// 右スティックの範囲をVector2Dに変換
Vector2D InputManager::Right_StickNormalize(float x, float y) const
{
	return StickNormalize(x, y);
}