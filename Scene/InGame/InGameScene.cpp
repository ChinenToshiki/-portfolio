#include "InGameScene.h"
#include "../../Utility/ResourceManager.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

#define Pealty_Time_Second 2

const char* button_name[] =
{
	"↑",
	"↓",
	"←",
	"→",
	"A",
	"B",
	"X",
	"Y",
	"LB",
	"RB",
};

InGameScene::InGameScene()
{
	Load_Ranking();
}

void InGameScene::Initialize()
{

	SetFontSize(64);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//ボタン画像読み込み
	ResourceManager& RM = ResourceManager::GetInstance();
	Button_image[0] = RM.GetImageResource("InGame/botany_yazirusi_03.png")[0]; //上↑
	Button_image[1] = RM.GetImageResource("InGame/botany_yazirusi_04.png")[0]; //下↓
	Button_image[2] = RM.GetImageResource("InGame/botany_yazirusi_02.png")[0]; //左←
	Button_image[3] = RM.GetImageResource("InGame/botany_yazirusi_01.png")[0]; //右→
	Button_image[4] = RM.GetImageResource("InGame/botan_ABXY_01.png")[0];      //Aボタン
	Button_image[5] = RM.GetImageResource("InGame/botan_ABXY_02.png")[0];      //Bボタン
	Button_image[6] = RM.GetImageResource("InGame/botan_ABXY_03.png")[0];      //Xボタン
	Button_image[7] = RM.GetImageResource("InGame/botan_ABXY_04.png")[0];      //Yボタン
	Button_image[8] = RM.GetImageResource("InGame/botan_LR_01.png")[0];        //LBボタン
	Button_image[9] = RM.GetImageResource("InGame/botan_LR_03.png")[0];        //RBボタン

	//押し込みボタン画像読み込み
	Select_Button_image[0] = RM.GetImageResource("InGame/Selected/Selectbotany_yazirusi_03.png")[0];  //上↑押されたとき
	Select_Button_image[1] = RM.GetImageResource("InGame/Selected/Selectbotany_yazirusi_04.png")[0];  //下↓押されたとき
	Select_Button_image[2] = RM.GetImageResource("InGame/Selected/Selectbotany_yazirusi_02.png")[0];  //左←押されたとき
	Select_Button_image[3] = RM.GetImageResource("InGame/Selected/Selectbotany_yazirusi_01.png")[0];  //右→押されたとき
	Select_Button_image[4] = RM.GetImageResource("InGame/Selected/Selectbotan_ABXY_01.png")[0];		  //Aボタン押されたとき
	Select_Button_image[5] = RM.GetImageResource("InGame/Selected/Selectbotan_ABXY_02.png")[0];		  //Bボタン押されたとき
	Select_Button_image[6] = RM.GetImageResource("InGame/Selected/Selectbotan_ABXY_03.png")[0];		  //Xボタン押されたとき
	Select_Button_image[7] = RM.GetImageResource("InGame/Selected/Selectbotan_ABXY_04.png")[0];		  //Yボタン押されたとき
	Select_Button_image[8] = RM.GetImageResource("InGame/Selected/Selectbotan_LR_01.png")[0];		  //LBボタン押されたとき
	Select_Button_image[9] = RM.GetImageResource("InGame/Selected/Selectbotan_RR_01.png")[0];		  //RBボタン押されたとき
	
	Player[Player_Type::normal]			= RM.GetImageResource("InGame/Charactor/Ningen_normal.png")[0];
	Player[Player_Type::happy]			= RM.GetImageResource("InGame/Charactor/Ningen_happy.png")[0];
	Player[Player_Type::miss]			= RM.GetImageResource("InGame/Charactor/Ningen_miss.png")[0];
	Player[Player_Type::normal_boss]	= RM.GetImageResource("InGame/Charactor/Ningen_nomal_bossver.png")[0];
	Player[Player_Type::happy_boss]		= RM.GetImageResource("InGame/Charactor/Ningen_happy_bossver.png")[0];
	Player[Player_Type::miss_boss]		= RM.GetImageResource("InGame/Charactor/Ningen_miss_bossver.png")[0];

	num_image = RM.GetImageResource("Result/numbers.png", 10, 5, 2, 160, 256);

	Enemy			= RM.GetImageResource("InGame/Charactor/oji.png")[0];

	Start_button[0] = RM.GetImageResource("InGame/start_finish/syuttsya_off.png")[0];
	Start_button[1] = RM.GetImageResource("InGame/start_finish/syuttsya_on.png")[0];
	End_button[0] = RM.GetImageResource("InGame/start_finish/taisya_off.png")[0];
	End_button[1] = RM.GetImageResource("InGame/start_finish/taisya_on.png")[0];

	Movie_2Sec		= RM.GetImageResource("InGame/Timer/timer_2tes.mp4")[0];
	Movie_5Sec		= RM.GetImageResource("InGame/Timer/timer_5tes.mp4")[0];
	Movie_7Sec		= RM.GetImageResource("InGame/Timer/timer_7tes.mp4")[0];
	
	Paper			= RM.GetImageResource("InGame/Paper/yousi.png")[0];
	Task_Paper		= RM.GetImageResource("InGame/Paper/syoruitaba.png")[0];

	bg_img			= RM.GetImageResource("InGame/BG/gamegamenn.png")[0];
	black_bg		= RM.GetImageResource("InGame/BG/black.png")[0];

	bgm = RM.GetSoundResource("BGM/BGM_InGame03.mp3");
	ChangeVolumeSoundMem(255 * 80 / 100, bgm);
	SE_success = RM.GetSoundResource("SE/SE_Typing.mp3");
	SE_miss= RM.GetSoundResource("SE/InGame_SE/InGame_miss.wav");
	SE_timer= RM.GetSoundResource("SE/InGame_SE/InGame_Penalty.wav");

	
	score = 0;
	gamedata = 0;
	std::srand(std::time(nullptr)); // シード設定
	time = 0.0f;
	time_count = 90;
	I = 0;
	now_page = 0;
	correct = 0;
	Penalty_time = Pealty_Time_Second;
	Final_time = 0;
	Player_Show = Player_Type::normal;
	Typing = false;

	for (int s = 0;s < 20;s++)
	{
		for (int t = 0;t < 25;t++)
		{
			Randomset(s,t);
		}
	}
	I = 0;
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);

	PauseMovieToGraph(Movie_2Sec, TRUE);
	PauseMovieToGraph(Movie_5Sec, TRUE);
	PauseMovieToGraph(Movie_7Sec, TRUE);

}

// 更新処理
SceneType InGameScene::Update(float delta_time)
{
	InputManager& input = InputManager::GetInstance();


	switch (PlayFlg)
	{
	case true:
		if (!GameStart)
		{
			time += delta_time;
			if (time >= 1.0f)
			{
				StartTimeDown--;
				time = 0.0f;
				if (StartTimeDown == 0)
				{
					GameStart = true;
				}
			}
		}

		if (GameStart)
		{
			if (time_count <= 0)
			{
				Final_time = true;
			}

			time += delta_time;
			if (time >= 0.5f)
			{
				if (Typing = true)
				{
					Typing = false;
				}
			}


			if (time >= 1.0f)
			{
				//0秒から残り時間が変わらない
				time = 0.0f;
				if (time_count > 0)
				{
					time_count--;
				}
				if (miss_Penalty)
				{
					Penalty_time--;

					if (Penalty_time == 0)
					{
						Player_Show = Player_Type::normal;
						if (love < 3)
						{
							miss_Penalty = false;
							Penalty_time += Pealty_Time_Second;
						}
						else if (love < 8)
						{
							miss_Penalty = false;
							Penalty_time += Pealty_Time_Second + 1;
						}
						else
						{
							miss_Penalty = false;
							Penalty_time += Pealty_Time_Second + 3;
						}

					}
				}
			}

			if (miss_Penalty)
			{
				Check_Sound_Play(SE_timer);
			}
			else
			{
				if (CheckSoundMem(SE_timer))
				{
					StopSoundMem(SE_timer);
				}
			}


			if (Final_time)
			{
				StopSoundMem(SE_timer);
				// Aボタンが押されたらリザルトへ
				if (input.GetButtonState(XINPUT_BUTTON_A) == eInputState::Pressed)
				{
					Write_Score();
					Compare_Ranking(ranking, 5, correct);
					Sort_Ranking(ranking, 5);
					Write_Ranking(5);
					time_count = 0;
					return SceneType::result;
				}

				// 他の処理は止める
				return SceneType::ingame;
			}
			//ミスカウント判定
			for (int i = 0; i < 16; i++)
			{
				if (input.GetButtonState(i) == Pressed && !miss_Penalty)
				{
					if (i == QuestionTask[now_page][I])
					{
						tanaka[I] = true;
						I++; correct++;
						Typing = true;
						PlaySoundMem(SE_success, DX_PLAYTYPE_BACK);

					}
					else
					{
						love++; miss_Penalty = true;
						Player_Show = Player_Type::miss;

						PlaySoundMem(SE_miss, DX_PLAYTYPE_BACK);

						SeekMovieToGraph(Movie_2Sec, 0);
						SeekMovieToGraph(Movie_5Sec, 0);
						SeekMovieToGraph(Movie_7Sec, 0);

						PlayMovieToGraph(Movie_2Sec);
						PlayMovieToGraph(Movie_5Sec);
						PlayMovieToGraph(Movie_7Sec);

					}
				}
			}


			for (int i = 0; i < 25; i++)
			{
				if (tanaka[i])
				{
					Drawimage[now_page][i] = Select_Button_image[image_num[now_page][i]];
				}
			}


			if (I > 24)
			{
				if (now_page != 20)
				{
					now_page++;
					I = 0;
					for (int i = 0; i < 25; i++)
					{
						tanaka[i] = false;
					}
					Player_Show = Player_Type::happy;
				}
				else
				{
					Write_Score();
					Compare_Ranking(ranking, 5, correct);
					Sort_Ranking(ranking, 5);
					Write_Ranking(5);
					I = 0; // vectorの範囲外を対処しました(後々修正案出します。)
					return SceneType::result;
				}
				// 他の処理は止める
				return SceneType::ingame;
			}
		}

		break;
	case false:
		if (input.GetButtonState(XINPUT_BUTTON_A) == eInputState::Pressed || (CheckHitKey(KEY_INPUT_RETURN)))
		{
		PlayFlg = true;
		StartTimeDown = 3;
		TimeStart = true;
		}

	}
	// 親クラスの更新
	return __super::Update(delta_time);
}

// 描画処理
void InGameScene::Draw() const
{
	int k = 0;

	switch (PlayFlg)
	{
	case true:
		
		if (!GameStart)
		{
			DrawRotaGraph(640, 360, 0.21, 0.0, bg_img, TRUE);

			switch (StartTimeDown)
			{
			case 3:
				//DrawGraph(1280 / 2, 100, num_image[3], TRUE);
				DrawRotaGraph(640, 360, 1.0f, 0.0f, num_image[3], TRUE);
				break;
			case 2:
				//DrawGraph(1280 / 2, 100, num_image[2], TRUE);
				DrawRotaGraph(640, 360, 1.0f, 0.0f, num_image[2], TRUE);
				DrawExtendGraph(0, 310, 350, 730, Player[Player_Show], 1);

				break;
			case 1:
				DrawExtendGraph(0, 310, 350, 730, Player[Player_Show], 1);

				DrawExtendGraph(395, 375, 850, 750, Paper, 1);
				DrawExtendGraph(600, 300, 1500, 850, Task_Paper, 1);
				//5×5でボタン表示
				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						//DrawExtendGraph(420 + 100 * j, 400 + 60 * i, 500 + 100 * j, 470 + 60 * i, Drawimage[now_page][k], 1);  //ボタン表示
						DrawExtendGraph(420 + 80 * j, 400 + 60 * i, 500 + 80 * j, 470 + 60 * i, Drawimage[now_page][k], 1);  //ボタン表示

						k++;
					}
				}
				//DrawGraph(1280 / 2, 100, num_image[1], TRUE);
				DrawRotaGraph(640, 360, 1.0f, 0.0f, num_image[1], TRUE);

				break;
			default:
				break;
			}
		}
		else
		{
			DrawRotaGraph(640, 360, 0.21, 0.0, bg_img, TRUE);

			DrawRotaGraph(640, 75, 0.8f, 0.0f, black_bg, TRUE);
			DrawRotaGraph(600, 75, 0.6f, 0.0f, num_image[time_count / 10], TRUE);
			DrawRotaGraph(680, 75, 0.6f, 0.0f, num_image[time_count % 10], TRUE);

			if (Typing)
			{
				DrawExtendGraph(0, 300, 350, 720, Player[Player_Show], 1);
			}
			else
			{
				DrawExtendGraph(0, 310, 350, 730, Player[Player_Show], 1);
			}

			if (miss_Penalty)
			{
				if (love < 3)
				{
					DrawGraph(200, 310, Movie_2Sec, FALSE);
				}
				else if (love < 8)
				{
					DrawGraph(200, 310, Movie_5Sec, FALSE);
				}
				else
				{
					DrawGraph(200, 310, Movie_7Sec, FALSE);
				}
			}
			else
			{
				PauseMovieToGraph(Movie_2Sec, TRUE);
				PauseMovieToGraph(Movie_5Sec, TRUE);
				PauseMovieToGraph(Movie_7Sec, TRUE);
			}
			DrawExtendGraph(395, 375, 850, 750, Paper, 1);
			DrawExtendGraph(600, 300, 1500, 850, Task_Paper, 1);
			DrawFormatString(1000, 450, GetColor(0, 0, 0), "残り:%d枚", 20 - now_page); //タスク描画
			//5×5でボタン表示
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					DrawExtendGraph(420 + 80 * j, 400 + 60 * i, 500 + 80 * j, 470 + 60 * i, Drawimage[now_page][k], 1);  //ボタン表示

					k++;
				}
			}

			if (Final_time)
			{
				DrawBox(0, 0, 1280, 720, 0xffffff, true);
				DrawString(200, 200, "[勤怠システム]\nAボタンを押して承認してください。", 0x00ff00);
				DrawGraph(300, 400, End_button[0], FALSE);

			}
		}
			break;
	case false:
		DrawBox(0, 0, 1280, 720, 0xffffff, true);
		DrawString(200, 200, "[勤怠システム]\nAボタンを押して承認してください。", 0x00ff00);
		DrawGraph(300, 400, Start_button[0],FALSE);
		break;
		
	}
}

// 終了処理
void InGameScene::Finalize()
{
	ResourceManager UnloadImageResorceData();
	StopSoundMem(bgm); 
	StopSoundMem(SE_timer);
	SetFontSize(32);
	takoyaki.clear();
}

// 現在シーン情報を渡す処理
const SceneType InGameScene::GetNowSceneType() const
{
	return SceneType::ingame;
}

//制限時間
void InGameScene::Time_count()
{
	/*if (time_count > 400)
	{
		time++;
		time_count = 0;
	}*/
}

//ボタンをランダムセット
void InGameScene::Randomset(int s, int t)
{
	const int button_index[] = {
		XINPUT_BUTTON_DPAD_UP		 ,
		XINPUT_BUTTON_DPAD_DOWN		 ,
		XINPUT_BUTTON_DPAD_LEFT		 ,
		XINPUT_BUTTON_DPAD_RIGHT	 ,
		XINPUT_BUTTON_A ,
		XINPUT_BUTTON_B ,
		XINPUT_BUTTON_X ,
		XINPUT_BUTTON_Y ,
		//XINPUT_BUTTON_LEFT_SHOULDER ,
		//XINPUT_BUTTON_RIGHT_SHOULDER ,
	};


	// 乱数
	const int index_size = sizeof(button_index) / sizeof(int);
	int random = std::rand() % index_size;
	QuestionTask[s][t] = button_index[random];
	image_num[s][t] = random;
	Drawimage[s][t] = Button_image[image_num[s][t]];
	takoyaki.push_back(button_name[random]);
	I++;
}
void InGameScene::Write_Score()
{

	gamedata = GameData::GetInstance();
	gamedata->SavePlayData(correct);
}

// csvから値読み込みして配列に代入
void InGameScene::Load_Ranking()
{
	FILE* fp;
	errno_t err;
	err = fopen_s(&fp, "Ranking.csv", "r");
	int beside = 0;
	int digit = 0;
	int rank_num = 0;

	while (err == 0)
	{
		rank_num = fgetc(fp);
		if (rank_num == EOF)
		{
			break;
		}
		else if (rank_num == '\n')
		{
			continue;
		}
		else if (rank_num == ',')
		{
			digit = 0;
			beside++;
			ranking[beside] = 0;
			continue;
		}
		else if (rank_num >= '0' && rank_num <= '9')
		{

			switch (digit)
			{
			case 0:
				ranking[beside] = rank_num - '0';
				digit++;
				break;
			case 1:
			case 2:
			case 3:
				ranking[beside] = ranking[beside] * 10 + (rank_num - '0');
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

// ランキングソート(バブルソート)
void InGameScene::Sort_Ranking(int numbers[], int array_size)
{
	//変数初期化
	int i, j, temp;

	for (i = 0; i < (array_size - 1); i++)
	{
		for (j = (array_size - 1); j > i; j--)
		{
			if (numbers[j - 1] < numbers[j])
			{
				//入れ替え
				temp = numbers[j - 1];
				numbers[j - 1] = numbers[j];
				numbers[j] = temp;
				//入れ替える度に配列出力
				for (int a = 0; a < 9; a++)
				{
					printf("%d ", numbers[a]);
				}
				printf("\n");
			}
		}
	}
}

// 現在のスコアをランキングと見比べて順番入れ替え
void InGameScene::Compare_Ranking(int numbers[], int array_size, int now_score)
{
	if (!(now_score == -1))
	{
		for (int i = 0; i < array_size; i++)
		{
			// スコアがi要素番目の数より大きい
			if (now_score >= numbers[i])
			{
				// スコアがi要素番目の数と等しい && 配列の最後の要素とiが等しくない
				if (/*now_score == numbers[i]) &&*/ !(array_size - 1 == i))
				{
					for (int j = (array_size - 2); j >= i; j--)
					{
						numbers[j + 1] = numbers[j];
					}

				}
				numbers[i] = now_score;
				break;
			}
		}
	}
}

// csvにランキング順に値を入れる
void InGameScene::Write_Ranking(int array_size)
{
	FILE* fp;
	errno_t err;
	err = fopen_s(&fp, "Ranking.csv", "w");
	int beside = 0;
	int digit = 0;

	if (err == 0)
	{
		for (int i = 0; i < array_size; i++)
		{
			fprintf(fp, "%d,", ranking[i]);
		}
	}

	if (fp != NULL)
	{
		fclose(fp);
	}
}

// 再生中かの確認
void InGameScene::Check_Sound_Play(int sound_handle)
{
	if (!(CheckSoundMem(sound_handle)))
	{
		PlaySoundMem(sound_handle, DX_PLAYTYPE_BACK);
	}
}