#pragma once
#include "../SceneBase.h"


// タイトル
class Title : public SceneBase
{

private:
	int bgm;
	int select;
	int Push_A;
	float time;
	float time_rug;
	float blend_rug;
	int mode_switch;
	int y;
	float rogo_y;
	int mode_select_x;
	int mode_select_y;
	int title;
	int ge_murogo;
	int end_on;
	int end_off;
	int help_on;
	int help_off;
	int ranking_on;
	int ranking_off;
	int start_on;
	int start_off;
	int fade_out;
	int blend;

public:
	// コンストラクタ
	Title();

	// デストラクタ
	virtual ~Title() = default;

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
};

