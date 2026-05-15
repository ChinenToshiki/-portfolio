#include "RankingScene.h"
#include "../../Utility/InputManager.h"
#include "../../Object/ObjectManager.h"
#include "../../Object/GameObject.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>


// コンストラクタ
RankingScene::RankingScene()
{
	now_score = 0;
	score_digit = 0;
	rank_score = 0;
	time = 0.0f;
	ranking_time = 0.0f;
	interval = 0.0f;
	match_num = 0;
	blend = 255;
	for (int i = 0; i < 5; i++)
	{
		score[i] = 0;
		font_handle[i] = CreateFontToHandle(NULL, (6 - i) * 15, 3);
		rank_location[i][0] = 1500.0f;
		rank_location[i][1] = 140.0f + 85.0f * i;
		draw_on[i] = true;
		rank_move[i] = true;
	}

	update = false;
	end_ranking = false;
	blink = false;
	rankin_judge = false;
	Load_Ranking();
}

// 初期化
void RankingScene::Initialize()
{
	gamedata = GameData::GetInstance();
	currentState = RankingScene::B_State::off;
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	
	ResourceManager& RM = ResourceManager::GetInstance();

	// 画像読み込み
	bg= RM.GetImageResource("Result/result.png")[0];
	to_title_on= RM.GetImageResource("Result/title_on.png")[0];
	to_title_off = RM.GetImageResource("Result/title_off.png")[0];
	rank[0] = RM.GetImageResource("Result/rank1.png")[0];
	rank[1] = RM.GetImageResource("Result/rank2.png")[0];
	rank[2] = RM.GetImageResource("Result/rank3.png")[0];
	character = RM.GetImageResource("InGame/Charactor/Ningen_happy.png")[0];
	lines = RM.GetImageResource("Result/lines01.png")[0];

	// 音源読み込み
	bgm = RM.GetSoundResource("BGM/Ranking/BGM_Ranking.mp3");
	ChangeVolumeSoundMem(255 * 90 / 100, bgm);
	se_rank_move= RM.GetSoundResource("SE/Ranking/SE_move.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, se_rank_move);
	se_ranked = RM.GetSoundResource("SE/Ranking/SE_ranked.wav");
	ChangeVolumeSoundMem(255 * 90 / 100, se_ranked);
	se_not_ranked = RM.GetSoundResource("SE/Ranking/SE_not_ranked.wav");
	ChangeVolumeSoundMem(255 * 90/ 100, se_not_ranked);
	se_to_title = RM.GetSoundResource("SE/Result/PushA.wav");
	ChangeVolumeSoundMem(255 * 100 / 100, se_to_title);
}

// 更新
SceneType RankingScene::Update(float delta_time)
{
	// 最初のフレームに一回だけ処理
	if (!update)
	{
		Confirm_From();
		Match_Score();
		Get_Score();
		PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
		update = true;
	}

	// ランキングシーンに入った時からの経過
	ranking_time += delta_time;

	// ランキングの文章の動き
	Ranking_Move(delta_time);

	// ランクインしたかの処理
	RankIn_Judge(rankin_judge, confirm, ranking_time);

	InputManager& input = InputManager::GetInstance();

	if (input.GetButtonState(XINPUT_BUTTON_A) == eInputState::Pressed)
	{
		PlaySoundMem(se_to_title, DX_PLAYTYPE_BACK);
		currentState = RankingScene::B_State::on;
		gamedata->InitializeScore();
		end_ranking = true;
	}
	
	if (input.GetButtonState(XINPUT_BUTTON_BACK) == eInputState::Pressed)
	{
		std::ofstream ofs("Ranking.csv", std::ios::trunc);
		ofs << "0,0,0,0,0,\n";
	}

	// フェードアウト処理
	FadeOut(delta_time, time, end_ranking, end_fadeout, blend);

	if (match)
	{
		Ranking_Blink(ranking_time, interval, match_num, draw_on);
	}
	
	// タイトルシーンへ遷移
	if (end_fadeout)
	{
		return SceneType::title;
	}
	
	// 親クラスの更新
	return __super::Update(delta_time);
}

// 描画
void RankingScene::Draw() const
{
	// 背景画像
	DrawGraph(0, 0, bg, FALSE);

	// タイトルボタン
	switch (currentState)
	{
	case RankingScene::B_State::on:
		DrawRotaGraph(200, 650, 0.8f, 0.0f, to_title_on, TRUE);
		break;
	case RankingScene::B_State::off:
		DrawRotaGraph(200, 650, 0.8f, 0.0f, to_title_off, TRUE);
		break;
	default:
		break;
	}
	
	// スコア（１位～５位まで）
	for (int i = 0; i < 5; i++)
	{
		if (draw_on[i])
		{
			DrawFormatStringToHandle(rank_location[i][0], rank_location[i][1], GetColor(0, 0, 0), font_handle[1], "%d位  %d", i + 1, score[i]);
			if (i < 3)
			{
				DrawRotaGraph(rank_location[i][0] - 50.0f, rank_location[i][1] + 25.0f, 0.8f, 0.0f, rank[i], TRUE);
			}
		}
	}

	// リザルトからの遷移でランキングの更新をしたか
	if (confirm == true)
	{
		DrawFormatStringToHandle(200, 170, GetColor(0, 0, 0), font_handle[4], "あなたのスコア");
		DrawFormatStringToHandle(280 - (score_digit-1) * 25, 250, GetColor(0, 0, 0), font_handle[0], "%d", now_score);

		// ランクイン・アウトの描画タイミング
		if (rankin_judge)
		{
			// イン
			if (match == true)
			{
				DrawFormatString(200, 500, GetColor(0, 255, 0), "ランキング更新!!");
			}
			// アウト
			else
			{
				DrawFormatString(180, 500, GetColor(0, 0, 255), "ランク外でした");
				DrawFormatString(170, 530, GetColor(0, 0, 255), "あと %d で5位!!", score[4] - now_score);
			}
		}
	}
	else
	{
		DrawRotaGraph(300, 450, 0.6f, 0.0f, character, TRUE);
		if (!rank_move[4])
		{
			DrawRotaGraph(300, 280, 0.8f, 0.0f, lines, TRUE);
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend);
}

// 終了
void RankingScene::Finalize()
{
	// タイトルに戻るときの処理
	ChangeScene_Process();
	for (int i = 0; i < 5; i++)
	{
		DeleteFontToHandle(font_handle[i]);
	}
}

// 現在のシーンタイプ取得
const SceneType RankingScene::GetNowSceneType() const
{
	// リザルト
	return SceneType::ranking;
}

// csvから値読み込みして配列に代入
void RankingScene::Load_Ranking()
{
	FILE* fp;
	errno_t err;
	err = fopen_s(&fp, "Ranking.csv", "r");
	int beside = 0;
	int digit = 0;

	while (err == 0)
	{
		rank_score = fgetc(fp);
		if (rank_score == EOF)
		{
			break;
		}
		else if (rank_score == '\n')
		{
			continue;
		}
		else if (rank_score == ',')
		{
			digit = 0;
			beside++;
			score[beside] = 0;
			continue;
		}
		else if (rank_score >='0' && rank_score <= '9')
		{
			
			switch (digit)
			{
			case 0:
				score[beside] = rank_score - '0';
				digit++;
				break;
			case 1:
			case 2:
			case 3:
				score[beside] = score[beside] * 10 + (rank_score - '0');
				digit++;
				break;
			default:
				break;
			}
		}
		else
		{
			continue;
		}
	}
	if (fp != NULL)
	{
		fclose(fp);
	}
}

// 現在のゲームのスコアを取得する
void RankingScene::Get_Score()
{
	int tmp;
	gamedata->LoadPlayData(tmp);
	now_score = tmp;
	score_digit= std::to_string(now_score).length();
}

// リザルトから来ているのかの確認
void RankingScene::Confirm_From()
{
	int tmp;
	gamedata->LoadPlayData(tmp);
	now_score = tmp;
	
	if (now_score >= 0)
	{
		confirm = true;
	}
}

// スコアが一致しているのかの確認
void RankingScene::Match_Score()
{
	for (int i = 0; i < 5; i++)
	{
		if (score[i] == now_score)
		{
			match_num = i;
			match = true;
			return;
		}
	}
}

// フェードアウト
void RankingScene::FadeOut(float delta_time, float& count_time, bool end_flag, bool& end_fadeout, int& blend)
{
	if (end_flag)
	{
		count_time += delta_time;
		if (count_time > 0.5f)
		{
			blend -= 30 * delta_time;
		}
		if (count_time > 1.0f)
		{
			end_fadeout = true;
		}
	}
}

// ランキングのアニメーション
void RankingScene::Ranking_Move(float delta_time)
{
	for (int i = 0; i < 5; i++)
	{
		if (rank_move[i])
		{
			if (i < 5 && rank_location[i][0] > 600.0f)
			{
				if (ranking_time > 0.5 * (i + 1))
				{
					rank_location[i][0] -= (delta_time * 3000.0f);
				}
			}
			if (rank_location[i][0] < 600.0f)
			{
				rank_location[i][0] = 600.0f;
				PlaySoundMem(se_rank_move, DX_PLAYTYPE_BACK);
				rank_move[i] = false;
			}
		}
	}
}

// ランキング更新時の点滅
void RankingScene::Ranking_Blink(float ranking_time, float& interval, int match_num, bool draw_flag[5])
{
	int time = (int)ranking_time;
	if (ranking_time > 3.0f)
	{
		if (blink)
		{
			if (ranking_time - interval > 2.0f)
			{
				interval = ranking_time;
				blink = false;
				draw_flag[match_num] = false;
			}
		}
		else
		{
			if (ranking_time - interval > 0.4f)
			{
				interval = ranking_time;
				blink = true;
				draw_flag[match_num] = true;
			}
		}
	}
}

// ランクインしたかの処理
void RankingScene::RankIn_Judge(bool& judge, bool confirm, float ranking_time)
{
	if (!judge)
	{
		if (confirm)
		{
			if (ranking_time > 4.0f)
			{
				if (match)
				{
					PlaySoundMem(se_ranked, DX_PLAYTYPE_BACK);
					judge = true;
				}
				else
				{
					PlaySoundMem(se_not_ranked, DX_PLAYTYPE_BACK);
					judge = true;
				}
			}
		}
	}
}

// シーンが変わる前にやる処理
void RankingScene::ChangeScene_Process()
{
	// BGMの再生ストップ
	StopSoundMem(bgm);
	StopSoundMem(se_ranked);
	StopSoundMem(se_not_ranked);
}