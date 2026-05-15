#include "GameData.h"
#include "DxLib.h"

GameData* GameData::instance = nullptr;

GameData::GameData()
{
    game_score = -1;
    for (int i = 0; i < 5; i++)
    {
        ranking[i] = 0;
    }
}

GameData* GameData::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new GameData();
    }
    return instance;
}

void GameData::DeleteInstance()
{
    if (instance)
    {
        delete instance;
        instance = nullptr;
    }
}

void GameData::SavePlayData(const int& score)
{
    game_score = score;
}

void GameData::LoadPlayData(int& score)
{
    score = game_score;
}

void GameData::InitializeScore()
{
    game_score = -1;
}

void GameData::SaveRankData(const int ranking[])
{
    for (int i = 0; i < 5; i++)
    {
        this->ranking[i] = ranking[i];
    }
}

void GameData::LoadRankData(int ranking[])
{
    for (int i = 0; i < 5; i++)
    {
        ranking[i] = this->ranking[i];
    }
}