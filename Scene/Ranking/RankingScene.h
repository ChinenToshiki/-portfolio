#pragma once
#include "../../Scene/SceneBase.h"
#include "../../Utility/GameData.h"
#include "../../Utility/Vector2D.h"

#include <vector>

class RankingScene : public SceneBase
{
public:
	enum class B_State
	{
		on,	// オン
		off	// オフ
	};

private:
	GameData* gamedata;			// ゲームデータのインスタンス
	B_State currentState;		// 現在のボタンの状態
	float rank_location[5][2];	// ランキングのそれぞれの座標
	int score[5];				// ランキングを入れる配列
	int rank_score;				// csvから受け取る箱
	int now_score;				// 現在のゲームのスコア
	int score_digit;			// スコアの桁数
	int font_handle[5];			// フォントのハンドル
	int match_num;				// 一致した値
	int blend;					// 彩度
	int draw_Phase;				// 描画するタイミング
	float time;					// フェードアウトの時間
	float ranking_time;			// ランキング全体の時間
	float interval;				// 点滅の間隔
	bool update;				// スコアを更新したか
	bool confirm;				// リザルトから来たのか
	bool match;					// 一致した値があるのか
	bool rank_move[5];			// ランキングの動き
	bool end_ranking;			// ランキングシーン終了
	bool end_fadeout;			// フェードアウト終了
	bool draw_on[5];			// 描画オン
	bool blink;					// 点滅
	bool rankin_judge;			// ランクイン・アウトの描画

	// 画像
	int bg;						// 背景
	int to_title_on;			// タイトルへ（押したとき
	int to_title_off;			// タイトルへ（押す前	
	int rank[3];				// １位～３位のマーク
	int character;				// キャラクター
	int lines;					// セリフ

	// 音
	int bgm;					// ランキングシーンのBGM
	int se_ranked;				// ランキングに入った時
	int se_not_ranked;			// ランキング外の時
	int se_rank_move;			// ランキングの1位～5位の動き
	int se_to_title;			// タイトルに戻るボタンを押したとき

public:
	// コンストラクタ
	RankingScene();

	// デストラクタ
	virtual ~RankingScene() = default;

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
	// ランキングのcsvを読み込む
	void Load_Ranking();

	// 現在のゲームスコアを取得する
	void Get_Score();

	// リザルトから来ているのかの確認
	void Confirm_From();

	// スコアが一致しているのかの確認
	void Match_Score();

	/// <summary>
	/// フェードアウト
	/// </summary>
	/// <param name="delta_time">デルタ秒</param>
	/// <param name="count_time">フェードアウトが始まってからのカウント</param>
	/// <param name="end_flag">タイトルボタンを押したときにtrue</param>
	/// <param name="end_fadeout">フェードアウトが終わったらtrue</param>
	/// <param name="blend">画面の彩度の値</param>
	void FadeOut(float delta_time, float& count_time, bool end_flag, bool& end_fadeout, int& blend);

	// ランキングのアニメーション
	void Ranking_Move(float delta_time);

	// スコア更新時の点滅
	void Ranking_Blink(float ranking_time, float& interval, int match_num, bool draw_flag[5]);

	// シーンが変わる前にやる処理
	void ChangeScene_Process();

	// ランクインしたかの処理
	void RankIn_Judge(bool& judge, bool confirm, float ranking_time);
};
