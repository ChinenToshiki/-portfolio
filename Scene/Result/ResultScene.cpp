#include "ResultScene.h"
#include "../../Utility/InputManager.h"
#include "../../Object/ObjectManager.h"
#include "../../Object/GameObject.h"



std::vector<GameObject*> objects; // Eye や Mouth をまとめる

//ゲーム中にリザルトが呼ばれた回数
int ResultScene::count = 0;

// コンストラクタ
ResultScene::ResultScene()
{
	
}

// 初期化
void ResultScene::Initialize()
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	ResourceManager& RM = ResourceManager::GetInstance();
	
	bgm = RM.GetSoundResource("BGM/Result/Result.mp3");
	select = RM.GetSoundResource("SE/Result/select.wav");
	Push_A = RM.GetSoundResource("SE/Result/PushA.wav");
	draw = RM.GetSoundResource("SE/Result/draw.wav");
	perfect= RM.GetSoundResource("SE/Result/rank_se01.wav");
	great= RM.GetSoundResource("SE/Result/rank_se02.wav");
	good= RM.GetSoundResource("SE/Result/rank_se03.wav");
	bad= RM.GetSoundResource("SE/Result/rank_se04.wav");
	result = RM.GetImageResource("Result/result_off.png")[0];
	title_off = RM.GetImageResource("Result/title_off.png")[0];
	title_on= RM.GetImageResource("Result/title_on.png")[0];
	ranking_off= RM.GetImageResource("Result/ranking_off.png")[0];
	ranking_on = RM.GetImageResource("Result/ranking_on.png")[0];
	clear = RM.GetImageResource("Result/tasseisitatasuku.png")[0];
	lost = RM.GetImageResource("Result/nokoritasuku.png")[0];
	score = RM.GetImageResource("Result/sukoa.png")[0];
	numbers = RM.GetImageResource("Result/numbers.png", 10, 5, 2, 160, 256);
	task = RM.GetImageResource("Result/numbers.png", 10, 5, 2, 160, 256);
	rank = RM.GetImageResource("Result/hyouka.png", 6, 2, 3, 500, 266);
	rank_size = 0.0;
	hyouka = 0;
	task_loop = 0;
	alternative = 0;
	time = 0.0f;
	time_rug = 0.5f;
	blend = 255;
	blend_rug = 1.0f;
	mode_select = 0;
	mode_switch = 0;
	digit_count = 0;
	digit_number = 0;
	bgm_switch = 0;
	draw_one = 0;
	draw_two = 0;

	for (int x = 0; x < 6; x++)
	{
		digit[x] = 0;
	}

	for (int x = 0; x < 2; x++)
	{
		task_digit[x] = 0;
	}

	gamedata = GameData::GetInstance();

	LoadScore();

	if (totalScore < 10)
	{
		digit_count = 1;
	}
	else if (totalScore < 100)
	{
		digit_count = 2;
	}
	else if (totalScore < 1000)
	{
		digit_count = 3;
	}
	else if (totalScore < 10000)
	{
		digit_count = 4;
	}
	else
	{
		digit_count = 5;
	}

	task_count = totalScore / 25;

	if (task_count < 5)
	{
		hyouka = 1;
	}
	else if(task_count < 10)
	{
		hyouka = 2;
	}
	else if (task_count < 25)
	{
		hyouka = 3;
	}
	else
	{
		hyouka = 4;
	}

	dx = 850;
	if (hyouka == 1)
	{
		rank_size = 1.1;
		rx = 760;
	}
	else if (hyouka == 2 || hyouka == 3)
	{
		rank_size = 0.38;
		rx = 635;
	}
	else
	{
		rank_size = 0.45;
		rx = 625;
	}

	if (task_count < 10)
	{
		task_loop = 1;
	}
	else
	{
		task_loop = 2;
	}

	alternative_task = task_count;
	alternative = totalScore;

	for (int x = 0; x < digit_count; x++)
	{
		digit[x] = alternative % 10;
		alternative /= 10;
	}

	for (int x = 0; x < 2; x++)
	{
		task_digit[x] = alternative_task % 10;
		alternative_task /= 10;
	}

	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
	
}

// 更新
SceneType ResultScene::Update(float delta_time)
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
	if (time >= 3.0f && bgm_switch == 0)
	{
		if (hyouka == 1)
		{
			PlaySoundMem(bad, DX_PLAYTYPE_BACK);
			bgm_switch = 1;
		}
		else if (hyouka == 2)
		{
			PlaySoundMem(good, DX_PLAYTYPE_BACK);
			bgm_switch = 1;
		}
		else if (hyouka == 3)
		{
			PlaySoundMem(great, DX_PLAYTYPE_BACK);
			bgm_switch = 1;
		}
		else
		{
			PlaySoundMem(perfect, DX_PLAYTYPE_BACK);
			bgm_switch = 1;
		}
	}
	if (time >= 1.0f && draw_one == 0)
	{
		PlaySoundMem(draw, DX_PLAYTYPE_BACK);
		draw_one = 1;
	}
	if (time >= 2.0f && draw_two == 0)
	{
		PlaySoundMem(draw, DX_PLAYTYPE_BACK);
		draw_two = 2;
	}
	/*LoadScore();

	for (int x = 0; x < digit_count; x++)
	{
		if (totalScore > 0)
		{
			digit[x] = totalScore % 10;
			totalScore /= 10;
		}
		else
		{
			digit[x] = NULL;
		}
	
	}*/

	InputManager& input = InputManager::GetInstance();

	if (input.GetButtonState(XINPUT_BUTTON_DPAD_RIGHT) == eInputState::Pressed && mode_switch == 0)
	{
		mode_select++;
		PlaySoundMem(select, DX_PLAYTYPE_BACK);

		if (mode_select > 1)
		{
			mode_select = 0;
		}
	}

	if (input.GetButtonState(XINPUT_BUTTON_DPAD_LEFT) == eInputState::Pressed && mode_switch == 0)
	{
		mode_select--;
		PlaySoundMem(select, DX_PLAYTYPE_BACK);

		if (mode_select < 0)
		{
			mode_select = 1;
		}
	}

	if (input.GetButtonState(XINPUT_BUTTON_A) == eInputState::Pressed && mode_select == 0 && mode_switch == 0)
	{
		mode_switch = 1;
		PlaySoundMem(Push_A, DX_PLAYTYPE_BACK);
		
	}
	if (input.GetButtonState(XINPUT_BUTTON_A) == eInputState::Pressed && mode_select == 1 && mode_switch == 0)
	{
		mode_switch = 2;
		PlaySoundMem(Push_A, DX_PLAYTYPE_BACK);
		
	}

	if (time >= time_rug && mode_switch != 0 && blend >= 0)
	{
		blend += -30 * delta_time;
	}

	if (time >= time_rug && mode_switch == 1 && time >= blend_rug)
	{
		gamedata->InitializeScore();

		return SceneType::title;
	}
	if (time >= time_rug && mode_switch == 2 && time >= blend_rug)
	{
		return SceneType::ranking;
	}

	// 親クラスの更新
	return __super::Update(delta_time);
}

// 描画
void ResultScene::Draw() const
{
	DrawGraph(0, 0, result, TRUE);

	DrawRotaGraph(430, 130, 0.8, 0.0, clear, TRUE);
	DrawRotaGraph(612, 260, 0.8, 0.0, score, TRUE);
	DrawRotaGraph(362, 400, 0.5, 0.0, rank[0], TRUE);

	if (time >= 1.0f)
	{
		for (int x = 0; x < task_loop; x++)
		{
			DrawRotaGraph(dx + 80 * (task_loop - x - 1), 125, 0.5, 0.0, task[task_digit[x]], TRUE);
		}
	}
	
	if (time >= 2.0f)
	{
		for (int x = 0; x < digit_count; x++)
		{
			DrawRotaGraph(dx + 80 * (digit_count - x - 1), 250, 0.5, 0.0, numbers[digit[x]], TRUE);
		}
	}

	if (time >= 3.0f)
	{
		DrawRotaGraph(rx, 400, rank_size, 0.0, rank[hyouka], TRUE);
		
	}
	/*DrawRotaGraph(dx, dy, 0.3, 0.0, numbers[0], TRUE);*/
	
	
	if (mode_select == 0)
	{
		if (mode_switch == 1)
		{
			DrawRotaGraph(250, 555, 1.15, 0.0, title_on, TRUE);
		}
		else
		{
			DrawRotaGraph(250, 555, 1.15, 0.0, title_off, TRUE);
		}
	}
	else
	{
		DrawRotaGraph(250, 555, 0.7, 0.0, title_off, TRUE);
	}

	if (mode_select == 1)
	{
		if (mode_switch == 2)
		{
			DrawRotaGraph(1100, 557, 1.15, 0.0, ranking_on, TRUE);
		}
		else
		{
			DrawRotaGraph(1100, 557, 1.15, 0.0, ranking_off, TRUE);
		}
	}
	else
	{
		DrawRotaGraph(1100, 557, 0.7, 0.0, ranking_off, TRUE);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend);
	
	/*DrawFormatString(100, 100, GetColor(255, 255, 0), "%dポイント", totalScore);*/
}

// 終了
void ResultScene::Finalize()
{
	StopSoundMem(bgm);
	StopSoundMem(perfect);
	StopSoundMem(great);
	StopSoundMem(good);
	StopSoundMem(bad);
	StopSoundMem(draw);
	numbers.clear();
}

// 現在のシーンタイプ取得
const SceneType ResultScene::GetNowSceneType() const
{
	// リザルト
	return SceneType::result;
}

void ResultScene::LoadScore()
{
	/*totalScore = 1800;*/
	gamedata->LoadPlayData(totalScore);
}