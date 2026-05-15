#pragma once
#include "../SceneBase.h"
#include "../../Utility/Vector2D.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/GameData.h"
#include<vector>

enum Player_Type
{
	normal,
	happy,
	miss,
	normal_boss,
	happy_boss,
	miss_boss
};

class InGameScene : public SceneBase
{
private:
	float time;
	int Count_image[3];
	std::vector<int> num_image;
	int time_count;  //制限時間
	int image;
	int score;    //スコア
	int ranking[5];
	int taskUI;   //タスクUI
	int timeUI;   //制限時間のUI
	int Q[5];
	int I = 0;
	int love = 0;
	std::vector<const char*> takoyaki;
	int Button_image[10];
	int Player[6];
	int Enemy;
	int bg_img;								// 背景画像
	int Select_Button_image[10];
	int image_num[20][25];
	int QuestionTask[20][25];
	int hatena_image;
	int Drawimage[20][25];
	bool tanaka[25] = { false };
	int now_page;
	int correct;
	bool miss_Penalty = false;
	int Penalty_time;
	bool Final_time = false;
	Player_Type Player_Show;
	int Paper;
	int Task_Paper;
	int black_bg;
	// se.bgm
	int bgm;
	int SE_success;
	int SE_miss;
	int SE_timer;

	int Start_button[2];
	int End_button[2];


	int anim_count;  //制限時間
	bool Typing;
	bool Animation;
	bool PlayFlg = false;
	bool TimeStart = false;
	bool GameStart = false;
	int StartTimeDown;

	int Movie_2Sec;
	int Movie_5Sec;
	int Movie_7Sec;

	GameData* gamedata;
	ResourceManager RM;

public:
	// コンストラクタ
	InGameScene();

	// デストラクタ
	virtual ~InGameScene() = default;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	/// <returns>現在のシーンタイプ</returns>
	virtual SceneType Update(float delta_time) override;

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() const override;

	/// <summary>
	/// 終了
	/// </summary>
	virtual void Finalize() override;

	/// <summary>
	/// 現在のシーンタイプを取得
	/// </summary>
	/// <returns>現在のシーンタイプ</returns>
	virtual const SceneType GetNowSceneType() const override;
private:
	void Time_count();
	void Randomset(int s,int t);
	void Write_Score();

	void Load_Ranking();
	void Sort_Ranking(int numbers[], int array_size);
	void Write_Ranking(int array_size);
	void Compare_Ranking(int numbers[], int array_size, int now_score);
	void Check_Sound_Play(int sound_handle);
};