#include "Title.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h""

// コンストラクタ
Title::Title()
{
	
}

// 初期化
void Title::Initialize()
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	ResourceManager& RM = ResourceManager::GetInstance();

	bgm = RM.GetSoundResource("BGM/Title/Title.mp3");
	select = RM.GetSoundResource("SE/Title/select.wav");
	Push_A = RM.GetSoundResource("SE/Title/pushA.wav");
	title = RM.GetImageResource("Title/TitleNrogo.png")[0];
	ge_murogo = RM.GetImageResource("Title/ge-murogo.png")[0];
	end_off = RM.GetImageResource("Title/end_off.png")[0];
	end_on= RM.GetImageResource("Title/end_on.png")[0];
	help_off= RM.GetImageResource("Title/help_off.png")[0];
	help_on= RM.GetImageResource("Title/help_on.png")[0];
	ranking_off= RM.GetImageResource("Title/ranking_off.png")[0];
	ranking_on= RM.GetImageResource("Title/ranking_on.png")[0];
	start_off= RM.GetImageResource("Title/start_off.png")[0];
	start_on= RM.GetImageResource("Title/start_on.png")[0];
	fade_out = RM.GetImageResource("Title/fadeout.png")[0];

	y = 358;
	rogo_y = -100;
	mode_select_x = 0;
	mode_select_y = 0;
	mode_switch = 0;
	time = 0.0f;
	time_rug = 0.5f;
	blend = 255;
	blend_rug = 1.0f;
	
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
}

// 更新
SceneType Title::Update(float delta_time)
{
	time += delta_time;

	if (mode_switch == 0)
	{
		time_rug += delta_time;
	}
	if (blend > 0)
	{
		blend_rug += delta_time;
	}

	InputManager& input = InputManager::GetInstance();

	if (input.GetButtonState(XINPUT_BUTTON_DPAD_DOWN) == eInputState::Pressed && mode_switch == 0)//下矢印キーが押された時
	{
		mode_select_y++;
		PlaySoundMem(select, DX_PLAYTYPE_BACK);
		
		if (mode_select_y > 2)
		{
			mode_select_y = 0;
			
		}
		if (mode_select_x == 1)
		{
			mode_select_x = 0;
		}
	}

	if (input.GetButtonState(XINPUT_BUTTON_DPAD_UP) == eInputState::Pressed && mode_switch == 0)//上矢印キーが押された時
	{
		mode_select_y--;
		PlaySoundMem(select, DX_PLAYTYPE_BACK);
		
		if (mode_select_y < 0)
		{
			mode_select_y = 2;
			
		}
		if (mode_select_x == 1)
		{
			mode_select_x = 0;
		}
	}

	if (input.GetButtonState(XINPUT_BUTTON_DPAD_RIGHT) == eInputState::Pressed && mode_switch == 0)//右矢印キーが押された時
	{
		mode_select_x++;
		mode_select_y = 1;
		PlaySoundMem(select, DX_PLAYTYPE_BACK);

		if (mode_select_x > 1)
		{
			mode_select_x = 0;
		}
	}

	if (input.GetButtonState(XINPUT_BUTTON_DPAD_LEFT) == eInputState::Pressed && mode_switch == 0)//左矢印キーが押された時
	{
		mode_select_x--;
		mode_select_y = 1;
		PlaySoundMem(select, DX_PLAYTYPE_BACK);

		if (mode_select_x < 0)
		{
			mode_select_x = 1;
		}
	}

	if (input.GetButtonState(XINPUT_BUTTON_A) == eInputState::Pressed && mode_select_y == 0 && mode_select_x == 0 && mode_switch == 0)//スタートボタンが押された時
	{
		mode_switch = 1;
		PlaySoundMem(Push_A, DX_PLAYTYPE_BACK);
		

	}
	if (input.GetButtonState(XINPUT_BUTTON_A) == eInputState::Pressed && mode_select_y == 1 && mode_select_x == 0 && mode_switch == 0)//ヘルプボタンが押された時
	{
		mode_switch = 2;
		PlaySoundMem(Push_A, DX_PLAYTYPE_BACK);
		
	}
	if (input.GetButtonState(XINPUT_BUTTON_A) == eInputState::Pressed && mode_select_y == 2 && mode_select_x == 0 && mode_switch == 0)//終了ボタンが押された時
	{
		mode_switch = 3;
		PlaySoundMem(Push_A, DX_PLAYTYPE_BACK);
	
	}
	if (input.GetButtonState(XINPUT_BUTTON_A) == eInputState::Pressed && mode_select_y == 1 && mode_select_x == 1 && mode_switch == 0)//ランキングボタンが押された時
	{
		mode_switch = 4;
		PlaySoundMem(Push_A, DX_PLAYTYPE_BACK);
		
	}

	if (time >= time_rug && mode_switch != 0 && blend >= 0)
	{
		
		blend += -30 * delta_time;
	}

	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		return SceneType::ingame;

	}



	if (blend <= 0 && mode_switch == 1 && time >= blend_rug)
	{
		return SceneType::ingame;
	}
	if (blend <= 0 && mode_switch == 2 && time >= blend_rug)
	{
		return SceneType::help;
	}
	if (blend <= 0 && mode_switch == 3 && time >= blend_rug)
	{
		return SceneType::end;
	}
	if (blend <= 0 && mode_switch == 4 && time >= blend_rug)
	{
		return SceneType::ranking;
	}

	//ロゴの落下処理
	if (rogo_y < 190)
	{
		rogo_y += 300 * delta_time;
	}

	// 親クラスの更新
	return __super::Update(delta_time);
}

// 描画
void Title::Draw() const
{
	
	DrawGraph(0, 0, title, TRUE);//背景画像
	DrawRotaGraph(620, (int)rogo_y, 1.15, 0.0, ge_murogo, TRUE);//上から降ってくるロゴ

	if (mode_select_y == 0 && mode_select_x == 0)//スタートボタン
	{
		if (mode_switch == 1)
		{
			DrawRotaGraph(612, 440, 1.1, 0.0, start_on, TRUE);
		}
		else
		{
			DrawRotaGraph(612, 440, 1.1, 0.0, start_off, TRUE);
		}
	}
	else
	{
		DrawRotaGraph(612, 440, 0.8, 0.0, start_off, TRUE);
	}

	if (mode_select_y == 1 && mode_select_x == 0)//ヘルプボタン
	{
		if (mode_switch == 2)
		{
			DrawRotaGraph(610, 550, 1.1, 0.0, help_on, TRUE);
		}
		else
		{
			DrawRotaGraph(610, 550, 1.1, 0.0, help_off, TRUE);
		}
	}
	else
	{
		DrawRotaGraph(610, 550, 0.8, 0.0, help_off, TRUE);
	}

	if (mode_select_y == 2 && mode_select_x == 0)//終了ボタン
	{
		if (mode_switch == 3)
		{
			DrawRotaGraph(610, 660, 1.1, 0.0, end_on, TRUE);
		}
		else
		{
			DrawRotaGraph(610, 660, 1.1, 0.0, end_off, TRUE);
		}
	}
	else
	{
		DrawRotaGraph(610, 660, 0.8, 0.0, end_off, TRUE);
	}

	if (mode_select_y == 1 && mode_select_x == 1)//ランキングボタン
	{
		if (mode_switch == 4)
		{
			DrawRotaGraph(999, 510, 1.1, 0.0, ranking_on, TRUE);
		}
		else
		{
			DrawRotaGraph(999, 510, 1.1, 0.0, ranking_off, TRUE);
		}
	}
	else
	{
		DrawRotaGraph(999, 510, 0.8, 0.0, ranking_off, TRUE);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend);

	/*DrawGraph(0, 0, fade_out, TRUE);*/

	/*if (blend == 1)
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}*/
	
	
	//DrawFormatString(100, 100, GetColor(255, 255, 255), "%f",time);//タイマーチェック用
	//DrawFormatString(100, 200, GetColor(255, 255, 255), "%f",time_rug);//タイマーチェック用
	
	/*DrawString(1050 / 2, 720 / 2, "スタート", GetColor(255, 255, 255));
	DrawString(1050 / 2, 840 / 2, "ヘルプ", GetColor(255, 255, 255));
	DrawString(1050 / 2, 960 / 2, "終了", GetColor(255, 255, 255));*/
}

// 終了
void Title::Finalize()
{
	StopSoundMem(bgm);
}

// 現在のシーンタイプ取得
const SceneType Title::GetNowSceneType() const
{
	// タイトル
	return SceneType::title;
}