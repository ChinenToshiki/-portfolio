#pragma once

class GameData
{
private:
    static GameData* instance;
    int game_score;
    int ranking[5];

public:
    GameData();
    ~GameData() = default;

public:
    //疑似的なコンストラクタ
    static GameData* GetInstance();
    //疑似的なコンストラクタ
    static void DeleteInstance();

public:
    // スコアを入れる
    void SavePlayData(const int&score);

    // スコアを読み込む
    void LoadPlayData(int& score);

    // スコア初期化
    void InitializeScore();

    // ランキング配列を入れる
    void SaveRankData(const int ranking[]);

    // ランキング配列を読み込む
    void LoadRankData(int ranking[]);
};