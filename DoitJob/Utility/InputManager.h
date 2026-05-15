#pragma once
#include "Singleton.h"
#include "Vector2D.h"

//マクロ定義
#define D_BUTTON_MAX	(16)

enum eInputState
{
	None,
	Pressed,
	Release,
	Held
};

class InputManager : public Singleton<InputManager>
{
private:
	//コントローラー入力情報
	bool now_button[D_BUTTON_MAX];
	bool old_button[D_BUTTON_MAX];
	float trigger[2];
	Vector2D Left_stick;
	Vector2D Right_stick;
	static constexpr float STICK_MAX = 1.0f;	// スティックの最大入力範囲
	static constexpr float DEAD_ZONE = 0.5f;	// この値以下の数値を全て0にする

public:
	bool GetNowButton(int num) const;
	void Update();
	eInputState GetButtonState(int button) const;
	float GetLeftTrigger() const;
	float GetRightTrigger() const;
	const Vector2D& GetLeftStick() const;
	const Vector2D& GetRightStick() const;

private:
	bool CheckButtonRange(int button) const;
	/*float TriggerNormalize(unsigned char value) const;*/
	Vector2D Left_StickNormalize(float x,float y) const;
	Vector2D Right_StickNormalize(float x, float y) const;
	Vector2D StickNormalize(float x, float y) const;

};

