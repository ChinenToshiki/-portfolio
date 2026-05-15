#pragma once
#include "SceneBase.h"

// 各シーンクラス
#include "Title/Title.h"
#include "Title/Help.h"
#include "InGame/InGameScene.h"
#include "Result/ResultScene.h"
#include "Ranking/RankingScene.h"
#include "End/EndScene.h"

// シーン生成用クラス
class SceneFactory
{
public:
	/// <summary>
	/// シーン生成処理
	/// </summary>
	/// <param name="nextType">次のシーンタイプ</param>
	/// <returns>生成したシーンのポインタ</returns>
	static SceneBase* CreateScene(SceneType nextType)
	{
		// 各シーンの生成
		switch (nextType)
		{
		case SceneType::title:
			return dynamic_cast<SceneBase*>(new Title());
		case SceneType::ingame:
			return dynamic_cast<SceneBase*>(new InGameScene());
			break;
		case SceneType::result:
			return dynamic_cast<SceneBase*>(new ResultScene());
			break;
		case SceneType::ranking:
			return dynamic_cast<SceneBase*>(new RankingScene());
			break;
		case SceneType::end:
			return dynamic_cast<SceneBase*>(new EndScene());
			break;
		case SceneType::help:
			return dynamic_cast<SceneBase*>(new HelpScene());
			break;
		default:
			break;
		}
	}
};
