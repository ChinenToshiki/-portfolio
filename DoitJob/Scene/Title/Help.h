#pragma once
#include "../SceneBase.h"

// タイトル
class HelpScene : public SceneBase
{
private:
	int NowButton;
	int MissButton;
	int QuestionTask[25];
	int Drawimage[25];
	bool SelectFlg[25] = { false };
	int Button_image[10];
	int Select_Button_image[10];
	int image_num[25];
	int anim_time;
	float Animation;
	bool nextanim_flg = false;
	bool PlayTest = false;
	bool Back_flg = false;
	bool Succsess_flg = false;
	int Player[6];
	int SE_Mail;
	int bg_img;
	int Paper;
	int Task_Paper;

public:
	// コンストラクタ
	HelpScene();

	// デストラクタ
	virtual ~HelpScene() = default;

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

	void Randomset(int t);

	void AnimationCount(float delta_second);

};