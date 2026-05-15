#include"Help.h"
#include"../../Utility/ResourceManager.h"

HelpScene::HelpScene()
{
	MissButton = 0;
	Animation = 0.0f;
	anim_time = 0;
	nextanim_flg = true;
	PlayTest = false;
	Back_flg = false;
	Succsess_flg = false;
}

void HelpScene::Initialize()
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	ResourceManager& RM = ResourceManager::GetInstance();

	Button_image[0] = RM.GetImageResource("InGame/botany_yazirusi_03.png")[0];
	Button_image[1] = RM.GetImageResource("InGame/botany_yazirusi_04.png")[0];
	Button_image[2] = RM.GetImageResource("InGame/botany_yazirusi_02.png")[0];
	Button_image[3] = RM.GetImageResource("InGame/botany_yazirusi_01.png")[0];
	Button_image[4] = RM.GetImageResource("InGame/botan_ABXY_01.png")[0];
	Button_image[5] = RM.GetImageResource("InGame/botan_ABXY_02.png")[0];
	Button_image[6] = RM.GetImageResource("InGame/botan_ABXY_03.png")[0];
	Button_image[7] = RM.GetImageResource("InGame/botan_ABXY_04.png")[0];
	Button_image[8] = RM.GetImageResource("InGame/botan_LR_01.png")[0];
	Button_image[9] = RM.GetImageResource("InGame/botan_LR_03.png")[0];

	Select_Button_image[0] = RM.GetImageResource("InGame/Selected/Selectbotany_yazirusi_03.png")[0];
	Select_Button_image[1] = RM.GetImageResource("InGame/Selected/Selectbotany_yazirusi_04.png")[0];
	Select_Button_image[2] = RM.GetImageResource("InGame/Selected/Selectbotany_yazirusi_02.png")[0];
	Select_Button_image[3] = RM.GetImageResource("InGame/Selected/Selectbotany_yazirusi_01.png")[0];
	Select_Button_image[4] = RM.GetImageResource("InGame/Selected/Selectbotan_ABXY_01.png")[0];
	Select_Button_image[5] = RM.GetImageResource("InGame/Selected/Selectbotan_ABXY_02.png")[0];
	Select_Button_image[6] = RM.GetImageResource("InGame/Selected/Selectbotan_ABXY_03.png")[0];
	Select_Button_image[7] = RM.GetImageResource("InGame/Selected/Selectbotan_ABXY_04.png")[0];
	Select_Button_image[8] = RM.GetImageResource("InGame/Selected/Selectbotan_LR_01.png")[0];
	Select_Button_image[9] = RM.GetImageResource("InGame/Selected/Selectbotan_RR_01.png")[0];

	Player[0]  = RM.GetImageResource("InGame/Charactor/Ningen_happy.png")[0];
	Player[1]  = RM.GetImageResource("InGame/Charactor/Ningen_happy_bossver.png")[0];
	Player[2]  = RM.GetImageResource("InGame/Charactor/Ningen_miss.png")[0];
	Player[3]  = RM.GetImageResource("InGame/Charactor/Ningen_miss_bossver.png")[0];
	Player[4]  = RM.GetImageResource("InGame/Charactor/Ningen_nomal_bossver.png")[0];
	Player[5]  = RM.GetImageResource("InGame/Charactor/Ningen_normal.png")[0];

	Paper = RM.GetImageResource("InGame/Paper/yousi.png")[0];
	Task_Paper = RM.GetImageResource("InGame/Paper/syoruitaba.png")[0];

	bg_img = RM.GetImageResource("InGame/BG/gamegamenn.png")[0];


	SE_Mail = RM.GetSoundResource("SE/SE_Mail.mp3");

	for (int t = 0; t < 25; t++)
	{
		Randomset(t);
	}
	NowButton = 0;
}

// 更新
SceneType HelpScene::Update(float delta_time)
{
	InputManager& input = InputManager::GetInstance();

	if (Succsess_flg == true && PlayTest == true && anim_time > 30)
	{
		PlayTest = false;
		anim_time = 0;
	}
	if (anim_time > 11 && Succsess_flg == true)
	{
		if (input.GetButtonState(XINPUT_BUTTON_B) == Pressed)
		{
			return SceneType::ingame;
		}

	}

	if (nextanim_flg)
	{
		AnimationCount(delta_time);
	}

	if (input.GetButtonState(XINPUT_BUTTON_BACK) == Pressed)
	{
		return SceneType::title;
	}

	if (input.GetButtonState(XINPUT_BUTTON_A) == Pressed)
	{
		anim_time++;
	}

	if (!Succsess_flg)
	{
		switch (anim_time)
		{
		case 0:
			nextanim_flg = true;
			break;
		case 1:
			break;
		case 2:
			PlaySoundMem(SE_Mail, DX_PLAYTYPE_BACK);
			break;
		case 17:
			PlaySoundMem(SE_Mail, DX_PLAYTYPE_BACK);
			break;
		case 27:case 28:
			nextanim_flg = false;
			if (input.GetButtonState(XINPUT_BUTTON_A) == Pressed)
			{
				nextanim_flg = true;
				anim_time = 29;
			}
			break;
		case 33:
			PlayTest = true;
			break;
		}
	}
	else
	{
		switch (anim_time)
		{
		case 0:case 1:case 2:case 3:case 4:
			nextanim_flg = true;
			break;
		case 5:
			PlaySoundMem(SE_Mail, DX_PLAYTYPE_BACK);
		default:
			break;
		}
	}

	if (PlayTest)
	{
		for (int i = 0; i < 16; i++)
		{
			if (input.GetButtonState(i) == Pressed)
			{
				if (i == QuestionTask[NowButton])
				{
					SelectFlg[NowButton] = true;
					NowButton++;
					if (NowButton == 25)
					{
						Succsess_flg = true;
					}
				}
				else
				{
					MissButton++;
				}
			}

			for (int i = 0; i < 25; i++)
			{
				if (SelectFlg[i])
				{
					Drawimage[i] = Select_Button_image[image_num[i]];
				}
			}
		}
	}
	// 親クラスの更新
	return __super::Update(delta_time);
}

// 描画
void HelpScene::Draw() const
{
	DrawString(10, 10, "BACKボタン = タイトルに戻る", 0x00ff00);
	int k = 0;
	if (!Succsess_flg)
	{
		switch (anim_time)
		{
		case 0:case 1: case 2:
			DrawString(200, 200, "「ふぅ...今日の仕事は終わりっと...」", 0xffffff);
			DrawGraph(100, 300, Player[0], true);
			break;
		case 3:case 4:
			DrawString(200, 200, "「え？今メール？」", 0xffffff);
			DrawGraph(100, 300, Player[2], true);
			break;
		case 5:
			DrawString(200, 200, "「えーっと?」", 0xffffff);
			DrawGraph(100, 300, Player[5], true);
			break;
		case 6: case 7: case 8:
			DrawString(200, 200, "件名: [業務連絡] 追加の仕事\n送信元: 上司\nごっめーん。1つ仕事忘れてたわ\nそれだけやって\"から\"帰って。", 0x00ff00);
			break;

		case 9:break;

		case 10: case 11:
			DrawString(200, 200, "「え?」", 0xffffff);
			DrawGraph(100, 300, Player[2], true);
			break;
		case 12: case 13:
			DrawString(200, 200, "「今定時なんだけど......」", 0xffffff);
			DrawGraph(100, 300, Player[3], true);
			break;
		case 14:case 15:
			DrawString(200, 200, "「あ、ファイルも届いた...」", 0xffffff);
			DrawGraph(100, 300, Player[5], true);
			break;
		case 16: case 17:
			DrawString(200, 200, "「既読付けてないし。帰ろっと」", 0xffffff);
			DrawGraph(100, 300, Player[0], true);
			break;
		case 18: case 19:
			DrawString(200, 200, "件名: もしも\n送信元: 上司\n明日の朝までに終わって無かったら…\n.......覚えとけよ", 0x00ff00);
			break;

		case 20:break;

		case 21:case 22:
			DrawString(200, 200, "「やらないといけなくなっちゃった...」", 0xffffff);
			DrawGraph(100, 300, Player[1], true);
			break;
		case 23: case 24:
			DrawString(200, 200, "「えっと、やる仕事は？」", 0xffffff);
			DrawGraph(100, 300, Player[5], true);
			break;
		case 25: case 26:
			DrawString(200, 200, "「データ入力系だぁぁ」", 0xffffff);
			DrawGraph(100, 300, Player[4], true);
			break;
		case 27: case 28:
			DrawString(200, 200, "「やっていきましょう。まずはこれを押して...」", 0xffffff);
			DrawGraph(200, 300, Button_image[4], 1);
			break;
		case 29: case 30:
			DrawString(200, 200, "「これぐらいなら...」", 0xffffff);
			DrawGraph(200, 300, Select_Button_image[4], 1);
			break;
		case 31:case 32:
			DrawString(200, 200, "「え？これ全部？」", 0xffffff);
			DrawGraph(100, 300, Player[3], true);
			break;
		default:
			break;
		}
	}
	else
	{
		switch (anim_time)
		{
		case 0:case 1:case 2:
			DrawString(200, 200, "「ようやく終わったぁ」", 0xffffff);
			DrawGraph(100, 300, Player[0], true);

			break;
		case 3:case 4:
			DrawString(200, 200, "「送信して...終わりっと...」", 0xffffff);
			DrawGraph(100, 300, Player[0], true);

			break;
		case 5:break;
		case 6:case 7:
			DrawString(200, 200, "「ん？返信来た」", 0xffffff);
			DrawGraph(100, 300, Player[5], true);
				break;
		case 8:case 9:
			DrawString(200, 200, "件名: 確認しました。\n送信元: 上司\n確認しました。\nじゃ、明日からデータ入力よろしく！", 0x00ff00);
		case 10:break;
		case 11:
			DrawString(200, 200, "「え？」", 0xffffff);
			DrawGraph(100, 300, Player[3], true);
			break;
		default:
			DrawString(200, 200, "その後、本編へ...", 0xffffff);
			DrawString(200, 500, "Bボタンでプレイ", 0xf00fff);
			break;
		}
	}

	{
		//switch (anim_time)
		//{
		//case 4:
		//	DrawExtendGraph(420, 400, 500, 470, Button_image[4], 1);  //ボタン表示
		//case 3:
		//	DrawString(200, 250, "実際にボタンを押してみましょう！", 0x00ff00f);
		//case 0: case 1: case 2:
		//	DrawString(200, 200, "このゲームは、表示されているボタンを左上から押していきます。", 0x00ff00f);
		//	break;

		//case 8: case 9:
		//	DrawString(200, 250, "実際の画面では...", 0x00ff00f);
		//	DrawString(500, 250, "こうなります。", 0x00ff00);

		//case 5:	case 6:	case 7:
		//	DrawExtendGraph(420, 400, 500, 470, Select_Button_image[4], 1);  //ボタン表示
		//	DrawString(200, 200, "完璧です。", 0x00ff00);
		//	break;
		//}
	}

	if (PlayTest)
	{
		DrawRotaGraph(640, 360, 0.21, 0.0, bg_img, TRUE);
		DrawExtendGraph(395, 375, 850, 750, Paper, 1);
		DrawExtendGraph(600, 300, 1500, 850, Task_Paper, 1);
		DrawExtendGraph(0, 310, 350, 730, Player[5], 1);

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				DrawExtendGraph(420 + 80 * j, 400 + 60 * i, 500 + 80 * j, 470 + 60 * i, Drawimage[k], 1);  //ボタン表示
				k++;
			}
		}
	}
}

// 終了
void HelpScene::Finalize()
{

}

// 現在のシーンタイプ取得
const SceneType HelpScene::GetNowSceneType() const
{
	return SceneType::help;
}


void HelpScene::Randomset(int t)
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

	const int index_size = sizeof(button_index) / sizeof(int);
	int random = std::rand() % index_size;
	QuestionTask[t] = button_index[random];
	image_num[t] = random;
	Drawimage[t] = Button_image[image_num[t]];
	NowButton++;
}

void HelpScene::AnimationCount(float delta_second)
{

	Animation += delta_second;

	if (Animation  >= 1.5f)
	{
		anim_time += 1;
		Animation = 0.0f;
	}
}