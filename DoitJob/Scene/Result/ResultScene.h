#pragma once
#include "../../Scene/SceneBase.h"
#include "../../Utility/GameData.h"
#include <vector>

constexpr float POSITION_EPS = 5.0f;
constexpr float ROTATION_EPS = 0.1f;


// 評価段階
enum class PointType
{
	poor,
	average,
	good,
	great,
	excellent
};


class ResultScene : public SceneBase
{
private:
	int bgm;
	int bgm_switch;
	int select;
	int Push_A;
	int draw;
	int draw_one;
	int draw_two;
	int perfect;
	int great;
	int good;
	int bad;
	float time;
	float time_rug;
	int blend;
	float blend_rug;
	int mode_select;
	int mode_switch;
	int result;
	int title_on;
	int title_off;
	int ranking_on;
	int ranking_off;
	bool isVorD;
	int bg_image;
	int scoreBgImage;
	int okame_image;
	int p1_image;
	int p2_image;
	int V_image;
	int D_image;
	int Tenn_image;
	static int count;
	int totalScore;	// スコア
	int clear;
	int lost;
	int score;
	std::vector<int>numbers;
	std::vector<int>task;
	std::vector<int>rank;
	double rank_size;
	int dx;
	int rx;
	int ry;
	int hyouka;
	int task_count;
	int task_digit[2];
	int task_loop;
	int digit[6];
	int digit_count;
	int digit_number;
	int alternative;
	int alternative_task;
	GameData* gamedata;


public:
	// コンストラクタ
	ResultScene();

	// デストラクタ
	virtual ~ResultScene() = default;

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
	void LoadScore();

};

